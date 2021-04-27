namespace segmentVolumeDevice
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.volLvl = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.usbToolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.displayUpdate = new System.Windows.Forms.Timer(this.components);
            this.dBBar = new System.Windows.Forms.ProgressBar();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // volLvl
            // 
            this.volLvl.AutoSize = true;
            this.volLvl.Font = new System.Drawing.Font("Graphie", 60F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.volLvl.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(1)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.volLvl.Location = new System.Drawing.Point(-4, 9);
            this.volLvl.Name = "volLvl";
            this.volLvl.Size = new System.Drawing.Size(257, 96);
            this.volLvl.TabIndex = 1;
            this.volLvl.Text = "100%";
            // 
            // statusStrip1
            // 
            this.statusStrip1.AllowMerge = false;
            this.statusStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.usbToolStripStatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 128);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(249, 22);
            this.statusStrip1.SizingGrip = false;
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "Unknown";
            // 
            // usbToolStripStatusLabel
            // 
            this.usbToolStripStatusLabel.BackColor = System.Drawing.SystemColors.ControlLight;
            this.usbToolStripStatusLabel.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.usbToolStripStatusLabel.Name = "usbToolStripStatusLabel";
            this.usbToolStripStatusLabel.Size = new System.Drawing.Size(58, 17);
            this.usbToolStripStatusLabel.Text = "usbStatus";
            // 
            // displayUpdate
            // 
            this.displayUpdate.Enabled = true;
            this.displayUpdate.Tick += new System.EventHandler(this.displayUpdate_tick);
            // 
            // dBBar
            // 
            this.dBBar.Cursor = System.Windows.Forms.Cursors.Default;
            this.dBBar.ForeColor = System.Drawing.Color.Lime;
            this.dBBar.Location = new System.Drawing.Point(12, 101);
            this.dBBar.Name = "dBBar";
            this.dBBar.Size = new System.Drawing.Size(225, 20);
            this.dBBar.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.EnablePreventFocusChange;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(249, 150);
            this.Controls.Add(this.dBBar);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.volLvl);
            this.Font = new System.Drawing.Font("MS Reference Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Flutter v1.0";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label volLvl;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Timer displayUpdate;
        private System.Windows.Forms.ToolStripStatusLabel usbToolStripStatusLabel;
        private System.Windows.Forms.ProgressBar dBBar;
    }
}

