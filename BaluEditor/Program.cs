using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaluEditor
{
    static class Program
    {

        static string log_file;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            try
            {
                log_file = "logs\\" + DateTime.Now + " CSEditor.log";
                log_file = log_file.Replace(':', '-');
                if (!Directory.Exists("logs"))
                    Directory.CreateDirectory("logs");
                File.AppendAllText(log_file, "Application start\n");
                string assets_dir = Path.Combine(Directory.GetCurrentDirectory(), "assets");
                File.AppendAllText(log_file, "Assets dir = " + assets_dir + "\n");
                if (args.Length > 0)
                {
                    if (args.Length == 2)
                    {
                        if (args[0] == "-rel")
                            assets_dir = Path.Combine(Directory.GetCurrentDirectory(), args[1]);
                        else if (args[0] == "-abs")
                            assets_dir = args[1];
                        else
                            Console.WriteLine("Invalid arguments!");
                    }
                    else
                    {
                        Console.WriteLine("Invalid arguments!");
                    }
                }

                if (Directory.Exists(assets_dir))
                {
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    File.AppendAllText(log_file, "Before app run\n");
                    Application.Run(new MainWindow(assets_dir, log_file));
                    File.AppendAllText(log_file, "After app run\n");
                }
                else
                    Console.WriteLine("Assets directory not found!");
            }catch(Exception ex)
            {
                File.AppendAllText(log_file, "Some went wrong = " + ex.Message + "\n" + ex.StackTrace + "\n");
            }
        }
    }
}
