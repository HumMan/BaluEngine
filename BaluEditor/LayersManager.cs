using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BaluEditor
{
    public partial class LayersManager : UserControl
    {
        Editor.TLayersManager editor;
        Editor.TWorldDirector director;
        public LayersManager()
        {
            InitializeComponent();
        }

         
        public void EditorInitialize(Editor.TWorldDirector director)
        {
            this.director = director;
            editor = new Editor.TLayersManager(director);
            editor.GUI_Notify_LayersManagerSceneChange += editor_LayersManagerSceneChange;
            //editor_LayersManagerSceneChange(null);
        }

        void editor_LayersManagerSceneChange(Editor.TEditor sender, bool active)
        {
            listBox1.Items.Clear();
            if (active)
            {
                listBox1.Enabled = true;
                int count = editor.GetLayersCount();
                for (int i = 0; i < count; i++)
                {
                    Editor.TLayerDesc l = editor.GetLayer(i);
                    listBox1.Items.Add(l.name);
                }
            }
            else
                listBox1.Enabled = false;
        }
        public void EditorDeinitialize()
        {
            editor.GUI_Notify_LayersManagerSceneChange += editor_LayersManagerSceneChange;
            editor.Destroy();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            editor.AddLayer();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            editor.RemoveLayer(0);
        }

        bool enable_events = true;

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex!=-1)
            {
                enable_events = false;
                var layer = editor.GetLayer(listBox1.SelectedIndex);
                checkBox1.Checked = layer.visible;
                checkBox2.Checked = layer.locked;
                checkBox3.Checked = layer.visible_in_editor;
                textBox1.Text = layer.name;
                trackBar1.Value = (int)(layer.alpha*10);
                enable_events = true;
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (enable_events)
            {
                if (listBox1.SelectedIndex != -1)
                {
                    var layer = editor.GetLayer(listBox1.SelectedIndex);
                    layer.visible = checkBox1.Checked;
                    editor.SetLayer(listBox1.SelectedIndex, layer);
                }
            }
        }
    }
}
