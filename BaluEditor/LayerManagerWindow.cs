using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BaluEditor
{
    public partial class LayerManagerWindow : Form
    {
        public LayerManagerWindow()
        {
            InitializeComponent();
            
        }
        public LayersManager GetLayersManager()
        {
            return layersManager1;
        }

        private void LayerManagerWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Visible = false;
        }
    }
}
