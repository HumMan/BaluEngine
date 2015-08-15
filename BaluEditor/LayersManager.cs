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
            editor.GUI_Notify_LayersChange += editor_GUI_Notify_LayersChange;
        }

        void editor_GUI_Notify_LayersChange(Editor.TLayersChangeType type, int layer_id, int after_id)
        {
            switch (type)
            {
                case Editor.TLayersChangeType.Add:
                    listBox1.Items.Insert(layer_id, editor.GetLayer(layer_id).name);
                    break;
                case Editor.TLayersChangeType.Change:
                    {
                        var new_name = editor.GetLayer(layer_id).name;
                        if ((string)listBox1.Items[layer_id] != new_name)
                            listBox1.Items[layer_id] = new_name;
                    }
                    break;
                case Editor.TLayersChangeType.Remove:
                    listBox1.Items.RemoveAt(layer_id);
                    break;
                case Editor.TLayersChangeType.Reorder:
                    break;
                default:
                    break;
            }
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

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (enable_events)
            {
                if (listBox1.SelectedIndex != -1)
                {
                    var layer = editor.GetLayer(listBox1.SelectedIndex);
                    layer.name = textBox1.Text;
                    editor.SetLayer(listBox1.SelectedIndex, layer);
                }
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (enable_events)
            {
                if (listBox1.SelectedIndex != -1)
                {
                    var layer = editor.GetLayer(listBox1.SelectedIndex);
                    layer.alpha = trackBar1.Value/(float)trackBar1.Maximum;
                    editor.SetLayer(listBox1.SelectedIndex, layer);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (enable_events)
            {
                if (listBox1.SelectedIndex != -1)
                {
                    var layer = editor.GetLayer(listBox1.SelectedIndex);
                    layer.locked = checkBox2.Checked;
                    editor.SetLayer(listBox1.SelectedIndex, layer);
                }
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (enable_events)
            {
                if (listBox1.SelectedIndex != -1)
                {
                    var layer = editor.GetLayer(listBox1.SelectedIndex);
                    layer.visible_in_editor = checkBox3.Checked;
                    editor.SetLayer(listBox1.SelectedIndex, layer);
                }
            }
        }
    }
}
