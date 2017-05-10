using StarCraft_Bridge.Util;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StarCraft_Bridge.StarCraftConnectivity
{
    public class StarCraftDataFiles
    {
        public static void ReplaceBWAPIINI(string SCLocation, string MapName, string EnemyRace)
        {
            var BWAPIINI = new IniFile(SCLocation + "bwapi-data\\bwapi.ini");
            BWAPIINI.Write("map", MapName, "auto_menu");
            BWAPIINI.Write("enemy_race", EnemyRace, "auto_menu");
        }

        //TODO
        public static void CreateMapFromData(int Instance, string SCLocation, string MapName, string EnemyRace, dynamic data)
        {
            Directory.CreateDirectory("Temp");
            System.IO.StreamWriter file = new System.IO.StreamWriter("Temp\\Instance" + Instance + ".txt");
            
            //TODO change this to allow other params as well

            file.WriteLine(data.ImportantUnits.Split(' ').Count());
            file.WriteLine(data.ImportantUnits);
            file.WriteLine(data.ImportantWeapons);

            foreach (var X in data.MapData.AttackValues)
            {
                file.Write(X);
                file.Write(" ");
            }
            //file.WriteLine();

            foreach (var X in data.MapData.HPValues)
            {
                file.Write(X);
                file.Write(" ");
            }

            file.Close();

            ProcessStartInfo startInfo = new ProcessStartInfo();
            //startInfo.FileName = SCLocation + "GP\\SCMapParameterChanger.exe";
            startInfo.FileName = "GenerateSCMap.exe";
            startInfo.Arguments = Instance.ToString() + " " + '"' + "Maps/(2)Astral Balance.scx." + EnemyRace + '"' + " " + '"' + SCLocation + MapName + '"';
            //startInfo.WorkingDirectory = SCLocation + "GP";

            using (Process exeProcess = Process.Start(startInfo))
            {
                exeProcess.WaitForExit();
            }
        } 

        public static void ClearPreviousRun(string SCLocation)
        {
            //Clear wins.txt
            File.Delete(SCLocation + "wins.txt");
        }
    }
}
