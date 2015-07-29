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
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            File.Delete("editorcs.log");
            File.AppendAllText("editorcs.log", "Application start\n");
            string assets_dir = Path.Combine(Directory.GetCurrentDirectory(), "assets");
            File.AppendAllText("editorcs.log", "Assets dir = " + assets_dir +"\n");
            if(args.Length>0)
            {
                if(args.Length==2)
                {
                    if(args[0]=="-rel")
                        assets_dir = Path.Combine(Directory.GetCurrentDirectory(), args[1]);
                    else if(args[0]=="-abs")
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
                File.AppendAllText("editorcs.log", "Before app run\n");
                Application.Run(new MainWindow(assets_dir));
                File.AppendAllText("editorcs.log", "After app run\n");
            }
            else
                Console.WriteLine("Assets directory not found!");           
        }
    }
}
