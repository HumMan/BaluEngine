using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaluEditor
{
    public partial class MainWindow : Form
    {
        private Editor.TWorldDirector director;
        private EventsEditor events_editor;
        string _active_project;
        string active_project
        {
            get
            {
                return _active_project;
            }
            set
            {
                _active_project = value;
                Text = _active_project;
            }
        }
        string assets_dir;
        public MainWindow(string assets_dir)
        {
            File.Delete("editor.log");
            File.AppendAllText("editor.log", "Editor init start\n");
            Editor.TWorldDirector.DetectMemLeaks();
            File.AppendAllText("editor.log", "mem leaks on\n");
            this.assets_dir = assets_dir;
            InitializeComponent();
            File.AppendAllText("editor.log", "form initialized\n");
            director = new Editor.TWorldDirector(assets_dir);
            File.AppendAllText("editor.log", "director created\n");
            worldTreeEditor1.EditorInitialize(director);
            File.AppendAllText("editor.log", "world tree editor initialized\n");
            events_editor = new EventsEditor();
            File.AppendAllText("editor.log", "events editor created\n");
            worldObjectEditor1.EditorInitialize(director);
            File.AppendAllText("editor.log", "object editor initialized\n");
            worldObjectsList1.EditorInitialize(director);
            File.AppendAllText("editor.log", "world object selection list initialized\n");
            File.AppendAllText("editor.log", "Editor init end\n");
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveAs();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Open();
        }

        private void SaveAs()
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "BaluWorld files (*.bew)|*.bew";
            saveFileDialog1.FilterIndex = 1;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                director.SaveWorldTo(saveFileDialog1.FileName);
                active_project = saveFileDialog1.FileName;
            }
        }

        private void Open()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "BaluWorld files (*.bew)|*.bew";
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                director.LoadWorldFrom(openFileDialog.FileName);
                active_project = openFileDialog.FileName;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
           director.SaveWorldTo(active_project);
        }

        private void loadDemoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            director.LoadDemoWorld();
        }

        private void eventsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            events_editor.EditorInitialize(director);
            events_editor.ShowDialog();
            events_editor.EditorDeinitialize();
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            //director.Destroy();
        }

        private void runToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(active_project==null)
            {
                SaveAs();
            }else
                director.SaveWorldTo(active_project);

            Process myProcess = new Process();
            myProcess.StartInfo.UseShellExecute = false;
            myProcess.StartInfo.FileName = "launcher.exe";
            myProcess.StartInfo.Arguments = System.IO.Path.GetFullPath(assets_dir) + " " + active_project;
            myProcess.StartInfo.CreateNoWindow = true;
            myProcess.Start();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            director.LoadNewWorld();
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            director.Destroy();
            director = null;
            e.Cancel = false;
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            director.LoadNewWorld();
        }
    }
}
