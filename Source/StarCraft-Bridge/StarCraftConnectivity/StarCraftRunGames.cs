using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace StarCraft_Bridge.StarCraftConnectivity
{
    class StarCraftRunGames
    {
        public static void RunGame(string SCLocation, string CLLocation)
        {
            bool MultiplayerAIGame = false;

            bool FileExists = File.Exists(CLLocation + "Chaoslauncher.exe");

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = CLLocation + "Chaoslauncher.exe";
            startInfo.WorkingDirectory = CLLocation;

            ProcessStartInfo startInfoPlayer2 = new ProcessStartInfo();
            startInfoPlayer2.FileName = CLLocation + "Chaoslauncher.exe";
            startInfoPlayer2.WorkingDirectory = CLLocation;

            var LockFile = File.Create(SCLocation + "LOCKFILE");
            LockFile.Close();

            try
            {
                using (Process exeProcess = Process.Start(startInfo))
                {
                    Process exeProcess2 = null;
                    if (MultiplayerAIGame)
                    {
                        Thread.Sleep(3000);
                        exeProcess2 = Process.Start(startInfoPlayer2);

                        //Thread.Sleep(55000);
                    }
                    else
                    {
                        //Thread.Sleep(20000);
                    }

                    bool Minimised = false;

                    while (CheckLockFileExists(SCLocation))
                    {
                        Thread.Sleep(1000);
                        if (!Minimised)
                        {
                            try
                            {
                                var Procs2 = Process.GetProcessesByName("StarCraft");
                                foreach (var process in Procs2)
                                {
                                    if (GetExecutablePathAboveVista(process.Id).Equals(NormalizePath(SCLocation + "StarCraft.exe")))
                                    //if (process.MainModule.FileName.Equals(SCLocation + "StarCraft.exe"))
                                    {
                                        ShowWindow(process.MainWindowHandle, 2);
                                        Minimised = true;
                                    }
                                }
                            }
                            catch(Exception e)
                            {

                            }
                        }
                    }

                    var Procs = Process.GetProcessesByName("StarCraft");
                    foreach (var process in Procs)
                    {
                        if(GetExecutablePathAboveVista(process.Id).Equals(NormalizePath(SCLocation + "StarCraft.exe")))
                        //if (process.MainModule.FileName.Equals(SCLocation + "StarCraft.exe"))
                        {
                            process.Kill();
                        }
                    }

                    exeProcess.Kill();
                    if (MultiplayerAIGame)
                    {
                        exeProcess2.Kill();
                    }
                }
            }
            catch (Exception e)
            {
                // Log error.
                Console.WriteLine("Error happened. " + e.Message);
            }
        }

        public static string GetRunResults(string SCLocation, string CLLocation)
        {
            var Procs = Process.GetProcessesByName("StarCraft");
            foreach (var process in Procs)
            {
                try
                {
                    if (process.MainModule.FileName.Equals(SCLocation + "StarCraft.exe"))
                        process.Kill();
                }
                catch (Exception e) { }

            }

            Procs = Process.GetProcessesByName("Chaoslauncher");
            foreach (var process in Procs)
            {
                try
                {
                    if (process.MainModule.FileName.Equals(CLLocation + "Chaoslauncher.exe"))
                        process.Kill();
                }
                catch { }

            }

            string Results = "";

            int numTries = 0;
            while (Results.Length < 1)
            {
                numTries++;
                try
                {
                    Results = File.ReadAllText(SCLocation + "wins.txt");
                }
                catch (IOException)
                {
                    if (numTries > 10)
                    {
                        Results = "1,250";
                    }
                    else
                    {
                        Thread.Sleep(50);
                    }

                }
            }

            return Results;
        }

        private static string GetExecutablePathAboveVista(int dwProcessId)
        {
            StringBuilder buffer = new StringBuilder(1024);
            IntPtr hprocess = OpenProcess(ProcessAccessFlags.QueryInformation, false, dwProcessId);
            if (hprocess != IntPtr.Zero)
            {
                try
                {
                    int size = buffer.Capacity;
                    if (QueryFullProcessImageName(hprocess, 0, buffer, out size))
                    {
                        return NormalizePath(buffer.ToString());
                    }
                }
                finally
                {
                    CloseHandle(hprocess);
                }
            }
            return string.Empty;
        }

        [Flags]
        enum ProcessAccessFlags : uint
        {
            All = 0x001F0FFF,
            Terminate = 0x00000001,
            CreateThread = 0x00000002,
            VMOperation = 0x00000008,
            VMRead = 0x00000010,
            VMWrite = 0x00000020,
            DupHandle = 0x00000040,
            SetInformation = 0x00000200,
            QueryInformation = 0x00000400,
            Synchronize = 0x00100000,
            ReadControl = 0x00020000
        }

        [DllImport("kernel32.dll")]
        private static extern bool QueryFullProcessImageName(IntPtr hprocess, int dwFlags,
               StringBuilder lpExeName, out int size);
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(ProcessAccessFlags dwDesiredAccess,
                       bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool CloseHandle(IntPtr hHandle);

        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        public static bool CheckLockFileExists(string SCLocation)
        {
            bool res = File.Exists(SCLocation + "LOCKFILE");
            return res;
        }

        public static string NormalizePath(string path)
        {
            return Path.GetFullPath(new Uri(path).LocalPath)
                       .TrimEnd(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar)
                       .ToUpperInvariant();
        }
    }
}
