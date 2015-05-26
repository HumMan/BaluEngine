using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaluEditor
{
    public partial class WorldObjectEditor : UserControl
    {
        Editor.TWorldObjectEditor editor;
        Editor.TWorldDirector director;
        public WorldObjectEditor()
        {
            if (LicenseManager.UsageMode == LicenseUsageMode.Designtime)
                return;
            InitializeComponent();
            panel2.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseWheel);
        }
        public void EditorInitialize(Editor.TWorldDirector director)
        {
            this.director = director;
            editor = new Editor.TWorldObjectEditor(panel2.Handle, panel2.Width, panel2.Height, director);
            editor.OnToolsChange += OnToolsChange;
            timer1.Enabled = true;
        }
        public void EditorDeinitialize()
        {
            timer1.Enabled = false;
            editor.OnToolsChange -= OnToolsChange;
            editor.Destroy();
        }


        class TSelectToolNode
        {
            public int tool_index;
            public TSelectToolNode(int tool_index)
            {
                this.tool_index = tool_index;
            }
        }

        class TSelectToolModeNode
        {
            public int tool_index;
            public int mode_index;
            public TSelectToolModeNode(int tool_index, int mode_index)
            {
                this.tool_index = tool_index;
                this.mode_index = mode_index;
            }
        }

        private void OnToolsChange()
        {
            toolStrip1.Items.Clear();
            int tools_count = editor.GetToolsCount();
            if (tools_count > 0)
                toolStrip1.Visible = true;
            else
                toolStrip1.Visible = false;
            for(int i=0;i<tools_count;i++)
            {
                toolStrip1.Items.Add(editor.GetToolName(i));
                toolStrip1.Items[toolStrip1.Items.Count - 1].Tag = new TSelectToolNode(i);
            }
            RefreshToolStates();
        }
        private void RefreshToolStates()
        {
            if (editor.GetToolsCount() > 0)
            {
                int active_tool = editor.GetActiveTool();
                int states_count = editor.GetToolStatesCount(active_tool);
                toolStrip2.Items.Clear();
                if (states_count > 0)
                {
                    toolStrip2.Visible = true;
                    for (int i = 0; i < states_count; i++)
                    {
                        toolStrip2.Items.Add(editor.GetToolStateName(active_tool, i));
                        toolStrip2.Items[toolStrip2.Items.Count - 1].Tag = new TSelectToolModeNode(active_tool, i);

                    }
                }
                else
                    toolStrip2.Visible = false;
            }
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (editor != null)
                editor.Render();
        }

        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            if (editor != null)
                editor.MouseDown(e);
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {

            if (editor != null)
                editor.MouseMove(e);
        }

        private void panel2_MouseUp(object sender, MouseEventArgs e)
        {
            if (editor != null)
                editor.MouseUp(e);
        }

        private void panel2_Resize(object sender, EventArgs e)
        {
            if(editor!=null)
                editor.Resize(panel2.Width, panel2.Height);
        }
        private void panel2_MouseWheel(object sender, MouseEventArgs e)
        {
            if (editor != null)
                editor.MouseWheel(e);
        }

        private void panel2_MouseHover(object sender, EventArgs e)
        {
            panel2.Focus();
        }

        private void panel2_MouseEnter(object sender, EventArgs e)
        {
            panel2.Focus();
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if(e.ClickedItem.Tag is TSelectToolNode)
            {
                var t =e.ClickedItem.Tag as TSelectToolNode;
                editor.SetActiveTool(t.tool_index);
                RefreshToolStates();
            }
        }

        private void toolStrip2_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if (e.ClickedItem.Tag is TSelectToolModeNode)
            {
                var t = e.ClickedItem.Tag as TSelectToolModeNode;
                editor.SetActiveToolState(t.mode_index);
            }
        }
    }
}
