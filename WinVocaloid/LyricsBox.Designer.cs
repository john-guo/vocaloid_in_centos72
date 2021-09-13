
namespace WinVocaloid
{
    partial class LyricsBox
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.pinyinChoice = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SuspendLayout();
            // 
            // pinyinChoice
            // 
            this.pinyinChoice.Name = "pinyinChoice";
            this.pinyinChoice.Size = new System.Drawing.Size(181, 26);
            this.pinyinChoice.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.pinyinChoice_ItemClicked);
            // 
            // LyricsBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Name = "LyricsBox";
            this.Size = new System.Drawing.Size(395, 348);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.LyricsBox_MouseDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip pinyinChoice;
    }
}
