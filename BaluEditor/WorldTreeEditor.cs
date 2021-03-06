﻿using System;
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
    public partial class WorldTreeEditor : UserControl
    {
        Editor.TWorldTreeEditor editor;
        Editor.TWorldDirector director;

        NewObjectNameInput new_name_dialog;

        public WorldTreeEditor()
        {
            InitializeComponent();
            new_name_dialog = new NewObjectNameInput();
        }
        public void EditorInitialize(Editor.TWorldDirector director)
        {
            CreateContextItems();
            this.director = director;
            editor = new Editor.TWorldTreeEditor(director);
            editor.GUI_Notify_AfterWorldLoaded += editor_on_after_world_load;
            editor.GUI_Notify_ObjectCreate += editor_ObjectCreate;
            editor.GUI_Notify_ObjectDestroy += editor_ObjectRemove;
        }

        void editor_ObjectRemove(Editor.TEditor sender, int type, string name)
        {
            var nodes = treeView1.Nodes[0].Nodes[type].Nodes;
            for(int i=0;i<nodes.Count;i++)
            {
                if ((nodes[i].Tag as TWorldObjectNode).name == name)
                    nodes.RemoveAt(i);
            }
        }

        void editor_ObjectCreate(Editor.TEditor sender, int type, string name)
        {
            var nodes = treeView1.Nodes[0].Nodes[type].Nodes;
            nodes.Insert(0, CreateTreeNode(type, name));
        }

        class TCreateWorldObjectNode
        {
            public int type;
            public TCreateWorldObjectNode(int type)
            {
                this.type = type;
            }
        }

        void CreateContextItems()
        {
            for (int i = 0; i < Editor.TWorldTreeEditor.GetWorldObjectTypesCount(); i++)
            {
                var Item = new ToolStripMenuItem();
                Item.Name = "createToolStripMenuItem" + i;
                Item.Size = new System.Drawing.Size(152, 22);
                Item.Text = Editor.TWorldTreeEditor.GetObjectTypeName(i);

                Item.Tag = new TCreateWorldObjectNode(i);

                createToolStripMenuItem.DropDownItems.Add(Item);
            }
        }

        public void EditorDeinitialize()
        {
            editor.GUI_Notify_AfterWorldLoaded -= editor_on_after_world_load;
            editor.GUI_Notify_ObjectCreate -= editor_ObjectCreate;
            editor.GUI_Notify_ObjectDestroy -= editor_ObjectRemove;

            editor.Destroy();
        }

        void editor_on_after_world_load()
        {
            ReloadAllTree();
        }

        class TWorldObjectNode
        {
            public int type;
            //public int index;
            public string name;
            public TWorldObjectNode(int type, string name)
            {
                this.type = type;
                this.name = name;
            }
        }

        private void ReloadAllTree()
        {
            treeView1.Nodes.Clear();
            var world_node = new TreeNode("World");
            treeView1.Nodes.Add(world_node);
            for (int obj_type_id = 0; obj_type_id < Editor.TWorldTreeEditor.GetWorldObjectTypesCount(); obj_type_id++)
            {
                var obj_type_node = new TreeNode(Editor.TWorldTreeEditor.GetObjectTypeName(obj_type_id));
                world_node.Nodes.Add(obj_type_node);
                int obj_count = editor.GetObjectsCount(obj_type_id);
                for (int i = 0; i < obj_count; i++)
                {
                    var obj_node = CreateTreeNode(obj_type_id, editor.GetObjectName(obj_type_id, i));
                    obj_type_node.Nodes.Add(obj_node);
                }
            }
        }

        private TreeNode CreateTreeNode(int obj_type_id, string name)
        {
            var obj_node = new TreeNode(name);
            obj_node.Tag = new TWorldObjectNode(obj_type_id, name);
            return obj_node;
        }

        private void contextMenuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if(e.ClickedItem.Tag is TCreateWorldObjectNode)
            {
                var tag = e.ClickedItem.Tag as TCreateWorldObjectNode;

                if (new_name_dialog.GetName(editor, tag.type))
                {
                    editor.CreateObject(tag.type, new_name_dialog.Result);
                    //int id = editor.GetObjectIndex(tag.type, new_name_dialog.Result);
                    //director.OnObjectCreate(editor, tag.type, id);
                }
            }
        }

        private void removeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(treeView1.SelectedNode.Tag is TWorldObjectNode)
            {
                var node =treeView1.SelectedNode.Tag as TWorldObjectNode;
                editor.DestroyObject(node.type, node.name);
                //director.OnObjectDestroy(editor, node.type, node.index);
            }
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            if(treeView1.SelectedNode !=null)
            {
                removeToolStripMenuItem.Enabled = (treeView1.SelectedNode.Tag is TWorldObjectNode);
            }
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            
        }

        private void treeView1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (treeView1.SelectedNode!=null && treeView1.SelectedNode.Tag is TWorldObjectNode)
            {
                var node = treeView1.SelectedNode.Tag as TWorldObjectNode;
                editor.SetEditedObject(node.type, node.name);
            }
        }
    }
}
