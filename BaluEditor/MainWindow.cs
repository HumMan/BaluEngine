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
        public MainWindow()
        {
            InitializeComponent();
        }
        bool times_is_work = false;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (times_is_work) return;
            times_is_work = true;
            baluEditorControl1.Render();
            times_is_work = false;
        }
    }
}
