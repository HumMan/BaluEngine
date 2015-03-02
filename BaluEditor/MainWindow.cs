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

        Editor.BaluEditorOpenglWindow opengl;
        public MainWindow()
        {
            InitializeComponent();

            opengl = new Editor.BaluEditorOpenglWindow(panel2.Handle);
            baluEditorControl1 = new Editor.BaluEditorControl();

            this.baluEditorControl1.EditorToolsBar = this.toolStrip1;
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

            i = n.DropDown.Items.Add("PhysBody");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.PhysBody);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreatePhysBody(); };

            i = n.DropDown.Items.Add("Class");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Class);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateClass(); };

            i = n.DropDown.Items.Add("Scene");
            i.Tag = new Editor.TWolrdTreeNodeTag(Editor.TNodeType.Scene);
            i.Click += (object sender, EventArgs e) => { baluEditorControl1.CreateScene(); };
        }

        void i_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        bool times_is_work = false;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (times_is_work) return;
            times_is_work = true;
           
            opengl.BeginFrame();
            baluEditorControl1.Render();
            opengl.EndFrame();

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

        private void baluEditorControl1_MouseEnter(object sender, EventArgs e)
        {
            //baluEditorControl1.Focus();
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

        private void baluEditorControl1_MouseHover(object sender, EventArgs e)
        {
            
        }

        private void baluEditorControl1_MouseEnter_1(object sender, EventArgs e)
        {
            //baluEditorControl1.Focus();
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

        private void openGLControl1_OpenGLRender(object sender, EventArgs e)
        {
            baluEditorControl1.Render();
        }

        private void openGLControl1_OpenGLInit(object sender, EventArgs e)
        {
           
           
        }
    }
}
