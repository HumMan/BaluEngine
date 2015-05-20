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
    public partial class NewObjectNameInput : Form
    {
        public NewObjectNameInput()
        {
            InitializeComponent();
        }
        Editor.TWorldTreeEditor editor;
        int new_obj_type;

        public string Result;

        public bool GetName(Editor.TWorldTreeEditor editor, int new_obj_type)
        {
            this.editor = editor;
            this.new_obj_type = new_obj_type;

            this.Text = "Create new " + Editor.TWorldTreeEditor.GetObjectTypeName(new_obj_type);

            ValidateName();

            if (this.ShowDialog() == DialogResult.OK)
            {
                Result = textBox1.Text;
                return true;
            }
            else
                return false;
        }

        private void textBox1_Validating(object sender, CancelEventArgs e)
        {
            e.Cancel = !ValidateName();
        }

        private bool ValidateName()
        {
            if (String.IsNullOrWhiteSpace(textBox1.Text) || !editor.CanCreateObject(new_obj_type, textBox1.Text))
            {
                errorProvider1.SetError(textBox1, "Name allready exists");
                button1.Enabled = false;
                return false;
            }
            else
            {
                errorProvider1.SetError(textBox1, "");
                button1.Enabled = true;
                return true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            Validate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
            DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
