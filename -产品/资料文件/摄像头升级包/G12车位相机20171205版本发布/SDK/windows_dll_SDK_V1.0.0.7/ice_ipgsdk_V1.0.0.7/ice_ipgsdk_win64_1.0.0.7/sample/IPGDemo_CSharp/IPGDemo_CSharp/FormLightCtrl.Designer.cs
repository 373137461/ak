namespace IPGDemo_CSharp
{
    partial class FormLightCtrl
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox_style = new System.Windows.Forms.ComboBox();
            this.comboBox_color = new System.Windows.Forms.ComboBox();
            this.button_OK = new System.Windows.Forms.Button();
            this.button_cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(34, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "亮灯方式：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(34, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "灯光颜色：";
            // 
            // comboBox_style
            // 
            this.comboBox_style.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_style.FormattingEnabled = true;
            this.comboBox_style.Items.AddRange(new object[] {
            "关闭sdk控灯",
            "灭",
            "亮",
            "闪烁"});
            this.comboBox_style.Location = new System.Drawing.Point(117, 28);
            this.comboBox_style.Name = "comboBox_style";
            this.comboBox_style.Size = new System.Drawing.Size(121, 20);
            this.comboBox_style.TabIndex = 2;
            // 
            // comboBox_color
            // 
            this.comboBox_color.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_color.FormattingEnabled = true;
            this.comboBox_color.Items.AddRange(new object[] {
            "红色",
            "绿色",
            "黄色",
            "蓝色"});
            this.comboBox_color.Location = new System.Drawing.Point(117, 77);
            this.comboBox_color.Name = "comboBox_color";
            this.comboBox_color.Size = new System.Drawing.Size(121, 20);
            this.comboBox_color.TabIndex = 3;
            // 
            // button_OK
            // 
            this.button_OK.Location = new System.Drawing.Point(36, 145);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(75, 23);
            this.button_OK.TabIndex = 4;
            this.button_OK.Text = "确定";
            this.button_OK.UseVisualStyleBackColor = true;
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);
            // 
            // button_cancel
            // 
            this.button_cancel.Location = new System.Drawing.Point(163, 145);
            this.button_cancel.Name = "button_cancel";
            this.button_cancel.Size = new System.Drawing.Size(75, 23);
            this.button_cancel.TabIndex = 5;
            this.button_cancel.Text = "取消";
            this.button_cancel.UseVisualStyleBackColor = true;
            this.button_cancel.Click += new System.EventHandler(this.button_cancel_Click);
            // 
            // FormLightCtrl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(293, 213);
            this.Controls.Add(this.button_cancel);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.comboBox_color);
            this.Controls.Add(this.comboBox_style);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "FormLightCtrl";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "FormLightCtrl";
            this.Load += new System.EventHandler(this.FormLightCtrl_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox_style;
        private System.Windows.Forms.ComboBox comboBox_color;
        private System.Windows.Forms.Button button_OK;
        private System.Windows.Forms.Button button_cancel;
    }
}