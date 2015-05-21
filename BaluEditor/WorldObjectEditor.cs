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
            timer1.Enabled = true;
        }
        public void EditorDeinitialize()
        {
            timer1.Enabled = false;
            //editor.AfterWorldLoad -= editor_on_after_world_load;
            //editor.ObjectCreate -= editor_ObjectCreate;
            //editor.ObjectRemove -= editor_ObjectRemove;

            editor.Destroy();
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
    }
}
