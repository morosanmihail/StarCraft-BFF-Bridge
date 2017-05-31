using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using StarCraft_Bridge.StarCraftConnectivity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace StarCraft_Bridge
{
    class Program
    {
        public static string SCLocation = "E:\\Games\\Starcrafts\\1\\";
        public static string CLLocation = "E:\\Games\\ChaosLaunchers\\1\\";
        public static int InstanceNumber = 1;
        public static string HostName = "";

        public static void LoadParameters(string[] args)
        {
            if (args.Length > 0)
            {
                Console.WriteLine(string.Join(" ", args));
                HostName = args[0];
                SCLocation = args[1];
                CLLocation = args[2];
                InstanceNumber = int.Parse(args[3]);
            }
            else
            {
                Console.Write("Host Name: ");

                HostName = Console.ReadLine();
            }
        }

        static void Main(string[] args)
        {
            LoadParameters(args);

            var factory = new ConnectionFactory()
            {
                HostName = HostName
            };

            do
            {
                //On error, try to reconnect to server. Wait 5 seconds between reconnect attempts
                Console.WriteLine("Connecting to host " + HostName);
                try
                {
                    using (var connection = factory.CreateConnection())
                    using (var channel = connection.CreateModel())
                    {
                        channel.QueueDeclare(queue: "rpc_queue_sc",
                                             durable: false,
                                             exclusive: false,
                                             autoDelete: false,
                                             arguments: null);
                        channel.BasicQos(0, 1, false);
                        //var consumer = new EventingBasicConsumer(channel); //[TODO change to eventing]
                        var consumer = new QueueingBasicConsumer(channel);
                        channel.BasicConsume(queue: "rpc_queue_sc",
                                             noAck: false,
                                             consumer: consumer);

                        while(true)
                        //consumer.Received += (model, ea) =>
                        {
                            string response = null;

                            Console.WriteLine(" [x] Awaiting RPC requests");
                            var ea = (BasicDeliverEventArgs)consumer.Queue.Dequeue();

                            var body = ea.Body;
                            var props = ea.BasicProperties;
                            var replyProps = channel.CreateBasicProperties();
                            replyProps.CorrelationId = props.CorrelationId;

                            Console.WriteLine(" [<-] Received request");

                            try
                            {
                                var message = Encoding.UTF8.GetString(body);

                                Console.WriteLine(" [.] RunGame()");

                                dynamic JResults = JsonConvert.DeserializeObject(message);

                                StarCraftDataFiles.CreateMapFromData(InstanceNumber, SCLocation, (string)JResults.custom.MapName, (string)JResults.custom.EnemyRace, JResults);
                                StarCraftDataFiles.ReplaceBWAPIINI(SCLocation, (string)JResults.custom.MapName, (string)JResults.custom.EnemyRace);
                                StarCraftDataFiles.ClearPreviousRun(SCLocation);

                                for (int i = 0; i < (int)JResults.custom.NumberOfGames; i++)
                                {
                                    StarCraftRunGames.RunGame(SCLocation, CLLocation);
                                }
                                String Results = StarCraftRunGames.GetRunResults(SCLocation, CLLocation);

                                Dictionary<string, object> collection = new Dictionary<string, object>()
                                {
                                };

                                int Wins = 0;
                                int Total = 0;
                                float AverageTime = 0;

                                var lines = Results.Split('\n');
                                foreach (var line in lines)
                                {
                                    if (line.Length > 1)
                                    {
                                        var result = line.Split(',');
                                        int win = int.Parse(result[0]);
                                        float time = float.Parse(result[1]);
                                        Wins += win;
                                        Total++;
                                        AverageTime += time;
                                    }
                                }

                                collection.Add("WinRate", (double)Wins / Total);

                                JObject Result = new JObject(
                                    new JProperty("metrics",
                                        JObject.FromObject(collection)
                                    )
                                );

                                response = Result.ToString(); //Send them here
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(" [.] " + e.Message);
                                response = "";
                            }
                            finally
                            {
                                var responseBytes = Encoding.UTF8.GetBytes(response);
                                channel.BasicPublish(exchange: "",
                                                     routingKey: props.ReplyTo,
                                                     basicProperties: replyProps,
                                                     body: responseBytes);
                                channel.BasicAck(deliveryTag: ea.DeliveryTag,
                                                 multiple: false);
                                Console.WriteLine(" [->] Sent response to server");
                            }
                        }


                        //Console.WriteLine(" Press [enter] to exit.");
                        //Console.ReadLine();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("ERROR: " + e.Message);
                }
                Thread.Sleep(5000);
            } while (true);
        }
    }
}
