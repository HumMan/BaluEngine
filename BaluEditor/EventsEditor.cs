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

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            int id;
            if(int.TryParse(e.Node.Text, out id))
            {
                var event_type_string = e.Node.Parent.Text;
                int type_id = event_editor.EventTypeFromName(event_type_string);
                var source = event_editor.GetEventScript(type_id, id);
                source = source.Replace("\n", Environment.NewLine);
                textBox2.Text = source;
            }
        }
    }
}
