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
    public partial class MainWindow : Form
    {
        private Editor.BaluEditorControl baluEditorControl1;
        public MainWindow()
        {
            InitializeComponent();

            panel2.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel2_MouseWheel);

            baluEditorControl1 = new Editor.BaluEditorControl(panel2.Handle);

            baluEditorControl1.SetViewport(panel2.Width, panel2.Height);

            this.baluEditorControl1.EditorToolsBar = this.toolStrip1;
            this.baluEditorControl1.ToolStateToolsBar = this.toolStrip2;
            this.baluEditorControl1.SelectedObjectProperty = this.propertyGrid1;
            this.baluEditorControl1.ToolObjectSelect = this.listBox1;
            this.baluEditorControl1.WorldTreeView = this.treeView1;

            baluEditorControl1.InitializeEngine();

            InitializeCreateNodeContextMenu();
            
            timer1.Enabled = true;
        }

        void InitializeCreateNodeContextMenu()
        {
            var n = WorldContextMenu.Items.Add("Create") as ToolStripMenuItem;

            var i = n.DropDown.Items.Add("Material");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Material);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateMaterial(); };

            i = n.DropDown.Items.Add("Sprite");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Sprite);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateSprite(); };

            i = n.DropDown.Items.Add("Class");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Class);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateClass(); };

            i = n.DropDown.Items.Add("Scene");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Scene);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateScene(); };
        }

        bool times_is_work = false;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (times_is_work) return;
            times_is_work = true;

            baluEditorControl1.BeginFrame();
            baluEditorControl1.Render();
            baluEditorControl1.EndFrame();

            times_is_work = false;
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            var n = e.Node.Tag as Editor.TWolrdTreeNodeTag;
            if(n!=null)
            {
                if(!n.IsSpecialNode)
                {
                    baluEditorControl1.SetSelectedWorldNode(n);
                }
            }
        }

        private void treeView1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            var n = e.Node.Tag as Editor.TWolrdTreeNodeTag;
            if (n != null)
            {
                if (!n.IsSpecialNode)
                {
                    baluEditorControl1.SetEditedWorldNode(n);
                }
            }
        }

        private void EditorContextMenu_Opening(object sender, CancelEventArgs e)
        {
            EditorContextMenu.Items[0].Enabled = baluEditorControl1.CanSetSelectedAsWork();
            EditorContextMenu.Items[1].Enabled = baluEditorControl1.CanEndSelectedAsWork();
        }

        private void EditorContextMenu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if (e.ClickedItem == toolStripMenuItem1)
            {
                baluEditorControl1.SetSelectedAsWork();
            }
            if (e.ClickedItem == toolStripMenuItem2)
            {
                baluEditorControl1.EndSelectedAsWork();
            }
        }

        private void listBox1_SelectedValueChanged(object sender, EventArgs e)
        {
            baluEditorControl1.SetToolSelectedObject(listBox1.SelectedItem as string);
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "BaluWorld files (*.bew)|*.bew";
            saveFileDialog1.FilterIndex = 1;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                baluEditorControl1.SaveWorldTo(saveFileDialog1.FileName);
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "BaluWorld files (*.bew)|*.bew";
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                baluEditorControl1.LoadWorldFrom(openFileDialog.FileName);
            }
        }

        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            baluEditorControl1.MouseMove(e);
        }

        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            baluEditorControl1.MouseDown(e);
        }

        private void panel2_MouseUp(object sender, MouseEventArgs e)
        {
            baluEditorControl1.MouseUp(e);
        }

        private void panel2_MouseWheel(object sender, MouseEventArgs e)
        {
            baluEditorControl1.MouseWheel(e);
        }

        private void panel2_Resize(object sender, EventArgs e)
        {
            baluEditorControl1.Resize(panel2.Width, panel2.Height);
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void loadDemoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            baluEditorControl1.LoadDemoWorld();
        }

        private void panel2_MouseHover(object sender, EventArgs e)
        {
            panel2.Focus();
        }

        private void panel2_MouseEnter(object sender, EventArgs e)
        {
            panel2.Focus();
        }
    }
}
