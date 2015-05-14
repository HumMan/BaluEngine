using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaluEditor
{
    public partial class EventsEditor : Form
    {
        Editor.TEventsEditor event_editor;
        public EventsEditor()
        {
            InitializeComponent();
        }

        public void RefreshAllData(Editor.TEventsEditor event_editor)
        {
            treeView1.Nodes.Clear();
            this.event_editor = event_editor;
            event_editor.Initialize();

            for(int curr_event_type = 0; curr_event_type<event_editor.GetEventTypesCount();curr_event_type++)
            {
                var curr_type_node = treeView1.Nodes.Add(event_editor.GetEventTypeName(curr_event_type));

                for (int i = 0; i < event_editor.GetEventsCount(curr_event_type); i++)
                {
                    var event_node = curr_type_node.Nodes.Add(i.ToString());
                }
            }
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {

        }
        bool seek_text_changed = false;

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            int id;
            if(int.TryParse(e.Node.Text, out id))
            {
                var event_type_string = e.Node.Parent.Text;
                int type_id = event_editor.EventTypeFromName(event_type_string);
                var source = event_editor.GetEventScript(type_id, id);
                source = source.Replace("\n", Environment.NewLine);
                seek_text_changed = false;
                textBox2.Text = source;
                seek_text_changed = true;

                Compile();
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (!seek_text_changed) return;
            var source = textBox2.Text.Replace(Environment.NewLine, "\n");
            var event_type_string = treeView1.SelectedNode.Parent.Text;
            int type_id = event_editor.EventTypeFromName(event_type_string);
            int id = int.Parse(treeView1.SelectedNode.Text);
            event_editor.SetEventScript(type_id, id, source);

            Compile();
        }

        private void Compile()
        {
            string[] errors_list = new string[0];
            event_editor.CompileScripts(ref errors_list);

            textBox3.Text = string.Join(Environment.NewLine, errors_list);
        }
    }
}
