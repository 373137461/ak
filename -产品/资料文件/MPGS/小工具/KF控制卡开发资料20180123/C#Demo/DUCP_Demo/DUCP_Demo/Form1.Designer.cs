namespace DUCP_Demo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.DISTEXT = new System.Windows.Forms.Button();
            this.TextBox = new System.Windows.Forms.TextBox();
            this.PLAYVOICE = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.TextBox_WID = new System.Windows.Forms.TextBox();
            this.BUTTON_DEMO1 = new System.Windows.Forms.Button();
            this.BUTTON_DEMO2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // DISTEXT
            // 
            this.DISTEXT.Location = new System.Drawing.Point(43, 128);
            this.DISTEXT.Name = "DISTEXT";
            this.DISTEXT.Size = new System.Drawing.Size(61, 31);
            this.DISTEXT.TabIndex = 0;
            this.DISTEXT.Text = "显示文字";
            this.DISTEXT.UseVisualStyleBackColor = true;
            this.DISTEXT.Click += new System.EventHandler(this.DISTEXT_Click);
            // 
            // TextBox
            // 
            this.TextBox.Location = new System.Drawing.Point(43, 78);
            this.TextBox.Name = "TextBox";
            this.TextBox.Size = new System.Drawing.Size(178, 21);
            this.TextBox.TabIndex = 1;
            // 
            // PLAYVOICE
            // 
            this.PLAYVOICE.Location = new System.Drawing.Point(133, 129);
            this.PLAYVOICE.Name = "PLAYVOICE";
            this.PLAYVOICE.Size = new System.Drawing.Size(64, 30);
            this.PLAYVOICE.TabIndex = 2;
            this.PLAYVOICE.Text = "播放声音";
            this.PLAYVOICE.UseVisualStyleBackColor = true;
            this.PLAYVOICE.Click += new System.EventHandler(this.播放语音_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 81);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "文本";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "窗口";
            // 
            // TextBox_WID
            // 
            this.TextBox_WID.Location = new System.Drawing.Point(43, 47);
            this.TextBox_WID.Name = "TextBox_WID";
            this.TextBox_WID.Size = new System.Drawing.Size(42, 21);
            this.TextBox_WID.TabIndex = 5;
            // 
            // BUTTON_DEMO1
            // 
            this.BUTTON_DEMO1.Location = new System.Drawing.Point(43, 181);
            this.BUTTON_DEMO1.Name = "BUTTON_DEMO1";
            this.BUTTON_DEMO1.Size = new System.Drawing.Size(62, 28);
            this.BUTTON_DEMO1.TabIndex = 6;
            this.BUTTON_DEMO1.Text = "模板1";
            this.BUTTON_DEMO1.UseVisualStyleBackColor = true;
            this.BUTTON_DEMO1.Click += new System.EventHandler(this.BUTTON_DEMO1_Click);
            // 
            // BUTTON_DEMO2
            // 
            this.BUTTON_DEMO2.Location = new System.Drawing.Point(133, 181);
            this.BUTTON_DEMO2.Name = "BUTTON_DEMO2";
            this.BUTTON_DEMO2.Size = new System.Drawing.Size(62, 28);
            this.BUTTON_DEMO2.TabIndex = 7;
            this.BUTTON_DEMO2.Text = "模板2";
            this.BUTTON_DEMO2.UseVisualStyleBackColor = true;
            this.BUTTON_DEMO2.Click += new System.EventHandler(this.BUTTON_DEMO2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(223, 162);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(62, 28);
            this.button1.TabIndex = 8;
            this.button1.Text = "IO1  ON";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(223, 196);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(62, 28);
            this.button2.TabIndex = 9;
            this.button2.Text = "IO1  OFF";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 278);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.BUTTON_DEMO2);
            this.Controls.Add(this.BUTTON_DEMO1);
            this.Controls.Add(this.TextBox_WID);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PLAYVOICE);
            this.Controls.Add(this.TextBox);
            this.Controls.Add(this.DISTEXT);
            this.Name = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button DISTEXT;
        private System.Windows.Forms.TextBox TextBox;
        private System.Windows.Forms.Button PLAYVOICE;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TextBox_WID;
        private System.Windows.Forms.Button BUTTON_DEMO1;
        private System.Windows.Forms.Button BUTTON_DEMO2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

