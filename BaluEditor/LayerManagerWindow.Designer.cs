namespace BaluEditor
{
    partial class LayerManagerWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.layersManager1 = new BaluEditor.LayersManager();
            this.SuspendLayout();
            // 
            // layersManager1
            // 
            this.layersManager1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.layersManager1.Location = new System.Drawing.Point(12, 12);
            this.layersManager1.Name = "layersManager1";
            this.layersManager1.Size = new System.Drawing.Size(502, 444);
            this.layersManager1.TabIndex = 0;
            // 
            // LayerManagerWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(526, 468);
            this.Controls.Add(this.layersManager1);
            this.Name = "LayerManagerWindow";
            this.Text = "LayerManagerWindow";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LayerManagerWindow_FormClosing);
            this.ResumeLayout(false);

        }

        #endregion

        private LayersManager layersManager1;
    }
}