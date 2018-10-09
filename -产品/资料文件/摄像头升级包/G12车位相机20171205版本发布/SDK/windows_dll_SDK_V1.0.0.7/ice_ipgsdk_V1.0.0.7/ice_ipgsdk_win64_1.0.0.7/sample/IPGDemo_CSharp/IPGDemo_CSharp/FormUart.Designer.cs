namespace IPGDemo_CSharp
{
    partial class FormUart
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
            this.checkBox_enableUart = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBox_baudrate = new System.Windows.Forms.ComboBox();
            this.comboBox_databits = new System.Windows.Forms.ComboBox();
            this.comboBox_parity = new System.Windows.Forms.ComboBox();
            this.comboBox_stopbits = new System.Windows.Forms.ComboBox();
            this.comboBox_flowctrl = new System.Windows.Forms.ComboBox();
            this.button_cancle = new System.Windows.Forms.Button();
            this.button2_ok = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBox_flowctrl2 = new System.Windows.Forms.ComboBox();
            this.comboBox_stopbits2 = new System.Windows.Forms.ComboBox();
            this.comboBox_parity2 = new System.Windows.Forms.ComboBox();
            this.comboBox_databits2 = new System.Windows.Forms.ComboBox();
            this.comboBox_baudrate2 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.checkBox_enableUart2 = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // checkBox_enableUart
            // 
            this.checkBox_enableUart.AutoSize = true;
            this.checkBox_enableUart.Location = new System.Drawing.Point(360, 50);
            this.checkBox_enableUart.Name = "checkBox_enableUart";
            this.checkBox_enableUart.Size = new System.Drawing.Size(72, 16);
            this.checkBox_enableUart.TabIndex = 0;
            this.checkBox_enableUart.Text = "串口使能";
            this.checkBox_enableUart.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(380, 83);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "波特率:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(380, 113);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "数据位:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(380, 143);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "校验位:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(380, 173);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 5;
            this.label5.Text = "停止位:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(380, 203);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 12);
            this.label6.TabIndex = 6;
            this.label6.Text = "流控模式:";
            // 
            // comboBox_baudrate
            // 
            this.comboBox_baudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_baudrate.FormattingEnabled = true;
            this.comboBox_baudrate.Location = new System.Drawing.Point(460, 80);
            this.comboBox_baudrate.Name = "comboBox_baudrate";
            this.comboBox_baudrate.Size = new System.Drawing.Size(120, 20);
            this.comboBox_baudrate.TabIndex = 7;
            // 
            // comboBox_databits
            // 
            this.comboBox_databits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_databits.Enabled = false;
            this.comboBox_databits.FormattingEnabled = true;
            this.comboBox_databits.Location = new System.Drawing.Point(460, 110);
            this.comboBox_databits.Name = "comboBox_databits";
            this.comboBox_databits.Size = new System.Drawing.Size(120, 20);
            this.comboBox_databits.TabIndex = 8;
            // 
            // comboBox_parity
            // 
            this.comboBox_parity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_parity.FormattingEnabled = true;
            this.comboBox_parity.Location = new System.Drawing.Point(460, 140);
            this.comboBox_parity.Name = "comboBox_parity";
            this.comboBox_parity.Size = new System.Drawing.Size(120, 20);
            this.comboBox_parity.TabIndex = 9;
            // 
            // comboBox_stopbits
            // 
            this.comboBox_stopbits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_stopbits.FormattingEnabled = true;
            this.comboBox_stopbits.Location = new System.Drawing.Point(460, 170);
            this.comboBox_stopbits.Name = "comboBox_stopbits";
            this.comboBox_stopbits.Size = new System.Drawing.Size(120, 20);
            this.comboBox_stopbits.TabIndex = 10;
            // 
            // comboBox_flowctrl
            // 
            this.comboBox_flowctrl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_flowctrl.FormattingEnabled = true;
            this.comboBox_flowctrl.Location = new System.Drawing.Point(460, 200);
            this.comboBox_flowctrl.Name = "comboBox_flowctrl";
            this.comboBox_flowctrl.Size = new System.Drawing.Size(120, 20);
            this.comboBox_flowctrl.TabIndex = 11;
            // 
            // button_cancle
            // 
            this.button_cancle.Location = new System.Drawing.Point(545, 275);
            this.button_cancle.Name = "button_cancle";
            this.button_cancle.Size = new System.Drawing.Size(75, 23);
            this.button_cancle.TabIndex = 12;
            this.button_cancle.Text = "取消";
            this.button_cancle.UseVisualStyleBackColor = true;
            this.button_cancle.Click += new System.EventHandler(this.button_cancle_Click);
            // 
            // button2_ok
            // 
            this.button2_ok.Location = new System.Drawing.Point(455, 275);
            this.button2_ok.Name = "button2_ok";
            this.button2_ok.Size = new System.Drawing.Size(75, 23);
            this.button2_ok.TabIndex = 13;
            this.button2_ok.Text = "确定";
            this.button2_ok.UseVisualStyleBackColor = true;
            this.button2_ok.Click += new System.EventHandler(this.button2_ok_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(340, 20);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(280, 240);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "RS232";
            // 
            // comboBox_flowctrl2
            // 
            this.comboBox_flowctrl2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_flowctrl2.FormattingEnabled = true;
            this.comboBox_flowctrl2.Location = new System.Drawing.Point(150, 200);
            this.comboBox_flowctrl2.Name = "comboBox_flowctrl2";
            this.comboBox_flowctrl2.Size = new System.Drawing.Size(120, 20);
            this.comboBox_flowctrl2.TabIndex = 25;
            // 
            // comboBox_stopbits2
            // 
            this.comboBox_stopbits2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_stopbits2.FormattingEnabled = true;
            this.comboBox_stopbits2.Location = new System.Drawing.Point(150, 170);
            this.comboBox_stopbits2.Name = "comboBox_stopbits2";
            this.comboBox_stopbits2.Size = new System.Drawing.Size(120, 20);
            this.comboBox_stopbits2.TabIndex = 24;
            // 
            // comboBox_parity2
            // 
            this.comboBox_parity2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_parity2.FormattingEnabled = true;
            this.comboBox_parity2.Location = new System.Drawing.Point(150, 140);
            this.comboBox_parity2.Name = "comboBox_parity2";
            this.comboBox_parity2.Size = new System.Drawing.Size(120, 20);
            this.comboBox_parity2.TabIndex = 23;
            // 
            // comboBox_databits2
            // 
            this.comboBox_databits2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_databits2.Enabled = false;
            this.comboBox_databits2.FormattingEnabled = true;
            this.comboBox_databits2.Location = new System.Drawing.Point(150, 110);
            this.comboBox_databits2.Name = "comboBox_databits2";
            this.comboBox_databits2.Size = new System.Drawing.Size(120, 20);
            this.comboBox_databits2.TabIndex = 22;
            // 
            // comboBox_baudrate2
            // 
            this.comboBox_baudrate2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_baudrate2.FormattingEnabled = true;
            this.comboBox_baudrate2.Location = new System.Drawing.Point(150, 80);
            this.comboBox_baudrate2.Name = "comboBox_baudrate2";
            this.comboBox_baudrate2.Size = new System.Drawing.Size(120, 20);
            this.comboBox_baudrate2.TabIndex = 21;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(70, 203);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 20;
            this.label1.Text = "流控模式:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(70, 173);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 12);
            this.label7.TabIndex = 19;
            this.label7.Text = "停止位:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(70, 143);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 18;
            this.label8.Text = "校验位:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(70, 113);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 17;
            this.label9.Text = "数据位:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(70, 83);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 16;
            this.label10.Text = "波特率:";
            // 
            // checkBox_enableUart2
            // 
            this.checkBox_enableUart2.AutoSize = true;
            this.checkBox_enableUart2.Location = new System.Drawing.Point(50, 50);
            this.checkBox_enableUart2.Name = "checkBox_enableUart2";
            this.checkBox_enableUart2.Size = new System.Drawing.Size(72, 16);
            this.checkBox_enableUart2.TabIndex = 15;
            this.checkBox_enableUart2.Text = "串口使能";
            this.checkBox_enableUart2.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(30, 20);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(280, 240);
            this.groupBox2.TabIndex = 26;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "RS485";
            // 
            // FormUart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(654, 311);
            this.Controls.Add(this.comboBox_flowctrl2);
            this.Controls.Add(this.comboBox_stopbits2);
            this.Controls.Add(this.comboBox_parity2);
            this.Controls.Add(this.comboBox_databits2);
            this.Controls.Add(this.comboBox_baudrate2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.checkBox_enableUart2);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.button2_ok);
            this.Controls.Add(this.button_cancle);
            this.Controls.Add(this.comboBox_flowctrl);
            this.Controls.Add(this.comboBox_stopbits);
            this.Controls.Add(this.comboBox_parity);
            this.Controls.Add(this.comboBox_databits);
            this.Controls.Add(this.comboBox_baudrate);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.checkBox_enableUart);
            this.Controls.Add(this.groupBox1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormUart";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "外设参数";
            this.Load += new System.EventHandler(this.FormUart_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBox_enableUart;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBox_baudrate;
        private System.Windows.Forms.ComboBox comboBox_databits;
        private System.Windows.Forms.ComboBox comboBox_parity;
        private System.Windows.Forms.ComboBox comboBox_stopbits;
        private System.Windows.Forms.ComboBox comboBox_flowctrl;
        private System.Windows.Forms.Button button_cancle;
        private System.Windows.Forms.Button button2_ok;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBox_flowctrl2;
        private System.Windows.Forms.ComboBox comboBox_stopbits2;
        private System.Windows.Forms.ComboBox comboBox_parity2;
        private System.Windows.Forms.ComboBox comboBox_databits2;
        private System.Windows.Forms.ComboBox comboBox_baudrate2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox checkBox_enableUart2;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}