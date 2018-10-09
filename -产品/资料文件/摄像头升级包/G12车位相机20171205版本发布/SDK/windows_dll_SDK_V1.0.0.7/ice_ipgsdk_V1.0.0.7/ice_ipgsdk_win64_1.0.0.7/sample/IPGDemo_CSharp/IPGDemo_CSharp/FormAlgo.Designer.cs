namespace IPGDemo_CSharp
{
    partial class FormAlgo
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
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox_spaceCode = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_leftx = new System.Windows.Forms.TextBox();
            this.textBox_lefty = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_rightx = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_righty = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancle = new System.Windows.Forms.Button();
            this.checkBox_selfDefine = new System.Windows.Forms.CheckBox();
            this.comboBox_settingPPI = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "设置分辨率：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 77);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "车位编号：";
            // 
            // comboBox_spaceCode
            // 
            this.comboBox_spaceCode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_spaceCode.FormattingEnabled = true;
            this.comboBox_spaceCode.Location = new System.Drawing.Point(102, 74);
            this.comboBox_spaceCode.Name = "comboBox_spaceCode";
            this.comboBox_spaceCode.Size = new System.Drawing.Size(147, 20);
            this.comboBox_spaceCode.TabIndex = 5;
            this.comboBox_spaceCode.SelectedIndexChanged += new System.EventHandler(this.comboBox_spaceCode_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 106);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "左x坐标：";
            // 
            // textBox_leftx
            // 
            this.textBox_leftx.Location = new System.Drawing.Point(102, 103);
            this.textBox_leftx.MaxLength = 4;
            this.textBox_leftx.Name = "textBox_leftx";
            this.textBox_leftx.Size = new System.Drawing.Size(147, 21);
            this.textBox_leftx.TabIndex = 7;
            this.textBox_leftx.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_leftx_KeyPress);
            this.textBox_leftx.Leave += new System.EventHandler(this.textBox_leftx_Leave);
            // 
            // textBox_lefty
            // 
            this.textBox_lefty.Location = new System.Drawing.Point(102, 203);
            this.textBox_lefty.MaxLength = 4;
            this.textBox_lefty.Name = "textBox_lefty";
            this.textBox_lefty.Size = new System.Drawing.Size(147, 21);
            this.textBox_lefty.TabIndex = 9;
            this.textBox_lefty.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_lefty_KeyPress);
            this.textBox_lefty.Leave += new System.EventHandler(this.textBox_lefty_Leave);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 206);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "下y坐标：";
            // 
            // textBox_rightx
            // 
            this.textBox_rightx.Location = new System.Drawing.Point(102, 167);
            this.textBox_rightx.MaxLength = 4;
            this.textBox_rightx.Name = "textBox_rightx";
            this.textBox_rightx.Size = new System.Drawing.Size(147, 21);
            this.textBox_rightx.TabIndex = 11;
            this.textBox_rightx.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_rightx_KeyPress);
            this.textBox_rightx.Leave += new System.EventHandler(this.textBox_rightx_Leave);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 170);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "右x坐标：";
            // 
            // textBox_righty
            // 
            this.textBox_righty.Location = new System.Drawing.Point(102, 135);
            this.textBox_righty.MaxLength = 4;
            this.textBox_righty.Name = "textBox_righty";
            this.textBox_righty.Size = new System.Drawing.Size(147, 21);
            this.textBox_righty.TabIndex = 13;
            this.textBox_righty.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_righty_KeyPress);
            this.textBox_righty.Leave += new System.EventHandler(this.textBox_righty_Leave);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 138);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 12;
            this.label7.Text = "上y坐标：";
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(21, 259);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 14;
            this.buttonOK.Text = "确定";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancle
            // 
            this.buttonCancle.Location = new System.Drawing.Point(174, 259);
            this.buttonCancle.Name = "buttonCancle";
            this.buttonCancle.Size = new System.Drawing.Size(75, 23);
            this.buttonCancle.TabIndex = 15;
            this.buttonCancle.Text = "取消";
            this.buttonCancle.UseVisualStyleBackColor = true;
            this.buttonCancle.Click += new System.EventHandler(this.buttonCancle_Click);
            // 
            // checkBox_selfDefine
            // 
            this.checkBox_selfDefine.AutoSize = true;
            this.checkBox_selfDefine.Location = new System.Drawing.Point(25, 9);
            this.checkBox_selfDefine.Name = "checkBox_selfDefine";
            this.checkBox_selfDefine.Size = new System.Drawing.Size(108, 16);
            this.checkBox_selfDefine.TabIndex = 16;
            this.checkBox_selfDefine.Text = "自定义识别区域";
            this.checkBox_selfDefine.UseVisualStyleBackColor = true;
            // 
            // comboBox_settingPPI
            // 
            this.comboBox_settingPPI.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_settingPPI.FormattingEnabled = true;
            this.comboBox_settingPPI.Location = new System.Drawing.Point(102, 43);
            this.comboBox_settingPPI.Name = "comboBox_settingPPI";
            this.comboBox_settingPPI.Size = new System.Drawing.Size(147, 20);
            this.comboBox_settingPPI.TabIndex = 17;
            this.comboBox_settingPPI.SelectedIndexChanged += new System.EventHandler(this.comboBox_settingPPI_SelectedIndexChanged);
            // 
            // FormAlgo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 313);
            this.Controls.Add(this.comboBox_settingPPI);
            this.Controls.Add(this.checkBox_selfDefine);
            this.Controls.Add(this.buttonCancle);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.textBox_righty);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox_rightx);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBox_lefty);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox_leftx);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.comboBox_spaceCode);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Name = "FormAlgo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "算法参数";
            this.Load += new System.EventHandler(this.FormAlgo_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox_spaceCode;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_leftx;
        private System.Windows.Forms.TextBox textBox_lefty;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_rightx;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBox_righty;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancle;
        private System.Windows.Forms.CheckBox checkBox_selfDefine;
        private System.Windows.Forms.ComboBox comboBox_settingPPI;
    }
}