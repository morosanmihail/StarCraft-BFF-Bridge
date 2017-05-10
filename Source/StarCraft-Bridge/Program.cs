using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using StarCraft_Bridge.StarCraftConnectivity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

            //do
            //{
            //On error, try to reconnect to server. Wait 5 seconds between reconnect attempts
            Console.WriteLine("Connecting to host " + HostName);
            try
            {
                using (var connection = factory.CreateConnection())
                using (var channel = connection.CreateModel())
                {
                    channel.QueueDeclare(queue: "rpc_queue_torcs",
                                         durable: false,
                                         exclusive: false,
                                         autoDelete: false,
                                         arguments: null);
                    channel.BasicQos(0, 1, false);
                    var consumer = new EventingBasicConsumer(channel); //[TODO change to eventing]
                    channel.BasicConsume(queue: "rpc_queue_torcs",
                                         noAck: false,
                                         consumer: consumer);
                    Console.WriteLine(" [x] Awaiting RPC requests");

                    consumer.Received += (model, ea) =>
                    {
                        string response = null;
                        //var ea = (BasicDeliverEventArgs)consumer.Queue.Dequeue();

                        var body = ea.Body;
                        var props = ea.BasicProperties;
                        var replyProps = channel.CreateBasicProperties();
                        replyProps.CorrelationId = props.CorrelationId;

                        try
                        {
                            var message = Encoding.UTF8.GetString(body);

                            Console.WriteLine(" [.] RunGame()");

                            dynamic JResults = JsonConvert.DeserializeObject(message);

                            /*
                                CreateMapFromData(result);
                                ReplaceBWAPIINI(result);
                                ClearPreviousRun();*/
                                StarCraftRunGames.RunGame(SCLocation, CLLocation);
                                //response = GetRunResults();
                                

                            foreach (var Param in JResults["parameters"])
                            {
                                if ((bool)Param["enabled"] == true)
                                {
                                    //Params[(int)Param.custom.index] += (double)Param.value;
                                    //Find appropriate xml file in Torcs and apply changes 
                                    //XMLIntegration.ChangeValueInTorcsXML(TORCSInstallDirectory, (string)Param["name"], (double)Param["value"]);
                                }
                            }

                            //Run TORCS [TODO change number of games to custom value]
                            //var PathToResultsFile = RunHeadless.RunTorcs(TORCSInstallDirectory, TORCSResultsDirectory, 1, 1, (string)JResults["custom"]["RaceConfig"]);

                            Dictionary<string, object> collection = new Dictionary<string, object>()
                            {
                            };

                            //Collect results
                            foreach (var Metric in JResults["metrics"])
                            {
                                //var Value = XMLIntegration.GetJSONOfResultsFromXMLResults(PathToResultsFile, (string)Metric["name"]);
                                //collection.Add((string)Metric["name"], Value);
                            }

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
                        }

                        Console.WriteLine(" [x] Awaiting RPC requests");
                    };


                    Console.WriteLine(" Press [enter] to exit.");
                    Console.ReadLine();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("ERROR: " + e.Message);
            }
        }
    }
}
