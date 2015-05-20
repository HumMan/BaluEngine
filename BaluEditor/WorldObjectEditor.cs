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
            InitializeComponent();
        }
        public void EditorInitialize(Editor.TWorldDirector director)
        {
        }
        public void EditorDeinitialize()
        {
            editor.AfterWorldLoad -= editor_on_after_world_load;
            editor.ObjectCreate -= editor_ObjectCreate;
            editor.ObjectRemove -= editor_ObjectRemove;

            editor.Destroy();
        }
    }
}
