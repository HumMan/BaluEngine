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
            //editor = new Editor.TWorldObjectsList(director);
            //editor.SelectObjectsTypeChange += SelectObjectsTypeChange;
        }
        public void EditorDeinitialize()
        {
            //editor.SelectObjectsTypeChange -= SelectObjectsTypeChange;
            editor.Destroy();
        }
    }
}
