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
    public partial class WorldObjectsList : UserControl
    {
        Editor.TWorldObjectsList editor;
        Editor.TWorldDirector director;
        public WorldObjectsList()
        {
            InitializeComponent();
        }
        public void EditorInitialize(Editor.TWorldDirector director)
        {
            this.director = director;
            editor = new Editor.TWorldObjectsList(director);
            editor.SelectObjectsTypeChange += SelectObjectsTypeChange;
        }
        public void SelectObjectsTypeChange(Editor.TEditor sender, int type)
        {
            listBox1.Items.Clear();
            int count = editor.GetObjectsCount();
            for(int i=0;i<count;i++)
            {
                listBox1.Items.Add(editor.GetObjectName(i));
            }
        }
        public void EditorDeinitialize()
        {
            editor.SelectObjectsTypeChange -= SelectObjectsTypeChange;
            editor.Destroy();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            editor.SetSelectedObject(listBox1.SelectedIndex);
        }
    }
}
