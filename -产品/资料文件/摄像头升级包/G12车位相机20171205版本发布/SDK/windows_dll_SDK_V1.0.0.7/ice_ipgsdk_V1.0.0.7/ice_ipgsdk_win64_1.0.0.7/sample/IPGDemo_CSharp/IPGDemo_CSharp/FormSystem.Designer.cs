namespace IPGDemo_CSharp
{
    partial class FormSystem
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
            this.groupBox_spaceEn = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.radioButton_tmp = new System.Windows.Forms.RadioButton();
            this.radioButton_reserve = new System.Windows.Forms.RadioButton();
            this.radioButton_fix = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.radioButton_disable = new System.Windows.Forms.RadioButton();
            this.radioButton_enable = new System.Windows.Forms.RadioButton();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox_spaceCode = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBox_controlIp = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.checkBox_control = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_remoteIp = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.checkBox_remoteEn = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button_cancle = new System.Windows.Forms.Button();
            this.button_apply = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBox_httpEnable = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox_httpAddr = new System.Windows.Forms.TextBox();
            this.checkBox_smallPic = new System.Windows.Forms.CheckBox();
            this.checkBox_bigPic = new System.Windows.Forms.CheckBox();
            this.checkBox_uploadEnable = new System.Windows.Forms.CheckBox();
            this.checkBox_heartbeatEnbale = new System.Windows.Forms.CheckBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_uploadInterval = new System.Windows.Forms.TextBox();
            this.textBox_heartbeatInterval = new System.Windows.Forms.TextBox();
            this.groupBox_spaceEn.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox_spaceEn
            // 
            this.groupBox_spaceEn.Controls.Add(this.panel2);
            this.groupBox_spaceEn.Controls.Add(this.panel1);
            this.groupBox_spaceEn.Controls.Add(this.label3);
            this.groupBox_spaceEn.Controls.Add(this.label2);
            this.groupBox_spaceEn.Controls.Add(this.comboBox_spaceCode);
            this.groupBox_spaceEn.Controls.Add(this.label1);
            this.groupBox_spaceEn.Location = new System.Drawing.Point(17, 23);
            this.groupBox_spaceEn.Name = "groupBox_spaceEn";
            this.groupBox_spaceEn.Size = new System.Drawing.Size(309, 161);
            this.groupBox_spaceEn.TabIndex = 0;
            this.groupBox_spaceEn.TabStop = false;
            this.groupBox_spaceEn.Text = "车位参数";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.radioButton_tmp);
            this.panel2.Controls.Add(this.radioButton_reserve);
            this.panel2.Controls.Add(this.radioButton_fix);
            this.panel2.Location = new System.Drawing.Point(80, 104);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(210, 38);
            this.panel2.TabIndex = 7;
            // 
            // radioButton_tmp
            // 
            this.radioButton_tmp.AutoSize = true;
            this.radioButton_tmp.Location = new System.Drawing.Point(7, 11);
            this.radioButton_tmp.Name = "radioButton_tmp";
            this.radioButton_tmp.Size = new System.Drawing.Size(47, 16);
            this.radioButton_tmp.TabIndex = 2;
            this.radioButton_tmp.TabStop = true;
            this.radioButton_tmp.Text = "临时";
            this.radioButton_tmp.UseVisualStyleBackColor = true;
            this.radioButton_tmp.Click += new System.EventHandler(this.radioButton_tmp_Click);
            // 
            // radioButton_reserve
            // 
            this.radioButton_reserve.AutoSize = true;
            this.radioButton_reserve.Location = new System.Drawing.Point(84, 11);
            this.radioButton_reserve.Name = "radioButton_reserve";
            this.radioButton_reserve.Size = new System.Drawing.Size(47, 16);
            this.radioButton_reserve.TabIndex = 3;
            this.radioButton_reserve.TabStop = true;
            this.radioButton_reserve.Text = "预定";
            this.radioButton_reserve.UseVisualStyleBackColor = true;
            this.radioButton_reserve.Click += new System.EventHandler(this.radioButton_reserve_Click);
            // 
            // radioButton_fix
            // 
            this.radioButton_fix.AutoSize = true;
            this.radioButton_fix.Location = new System.Drawing.Point(152, 11);
            this.radioButton_fix.Name = "radioButton_fix";
            this.radioButton_fix.Size = new System.Drawing.Size(47, 16);
            this.radioButton_fix.TabIndex = 4;
            this.radioButton_fix.TabStop = true;
            this.radioButton_fix.Text = "固定";
            this.radioButton_fix.UseVisualStyleBackColor = true;
            this.radioButton_fix.Click += new System.EventHandler(this.radioButton_fix_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.radioButton_disable);
            this.panel1.Controls.Add(this.radioButton_enable);
            this.panel1.Location = new System.Drawing.Point(80, 58);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(210, 31);
            this.panel1.TabIndex = 6;
            // 
            // radioButton_disable
            // 
            this.radioButton_disable.AutoSize = true;
            this.radioButton_disable.Location = new System.Drawing.Point(7, 9);
            this.radioButton_disable.Name = "radioButton_disable";
            this.radioButton_disable.Size = new System.Drawing.Size(47, 16);
            this.radioButton_disable.TabIndex = 0;
            this.radioButton_disable.TabStop = true;
            this.radioButton_disable.Text = "禁用";
            this.radioButton_disable.UseVisualStyleBackColor = true;
            this.radioButton_disable.Click += new System.EventHandler(this.radioButton_disable_Click);
            // 
            // radioButton_enable
            // 
            this.radioButton_enable.AutoSize = true;
            this.radioButton_enable.Location = new System.Drawing.Point(84, 9);
            this.radioButton_enable.Name = "radioButton_enable";
            this.radioButton_enable.Size = new System.Drawing.Size(47, 16);
            this.radioButton_enable.TabIndex = 1;
            this.radioButton_enable.TabStop = true;
            this.radioButton_enable.Text = "使能";
            this.radioButton_enable.UseVisualStyleBackColor = true;
            this.radioButton_enable.Click += new System.EventHandler(this.radioButton_enable_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 115);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "车位类型：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "使能车位:";
            // 
            // comboBox_spaceCode
            // 
            this.comboBox_spaceCode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_spaceCode.FormattingEnabled = true;
            this.comboBox_spaceCode.Location = new System.Drawing.Point(87, 23);
            this.comboBox_spaceCode.Name = "comboBox_spaceCode";
            this.comboBox_spaceCode.Size = new System.Drawing.Size(73, 20);
            this.comboBox_spaceCode.TabIndex = 2;
            this.comboBox_spaceCode.SelectedIndexChanged += new System.EventHandler(this.comboBox_spaceCode_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "车位编号:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textBox_controlIp);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.checkBox_control);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.textBox_remoteIp);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.checkBox_remoteEn);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(19, 204);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(307, 187);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "控灯参数";
            // 
            // textBox_controlIp
            // 
            this.textBox_controlIp.Location = new System.Drawing.Point(151, 144);
            this.textBox_controlIp.Name = "textBox_controlIp";
            this.textBox_controlIp.Size = new System.Drawing.Size(126, 21);
            this.textBox_controlIp.TabIndex = 7;
            this.textBox_controlIp.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_controlIp_KeyPress);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(26, 147);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(119, 12);
            this.label6.TabIndex = 6;
            this.label6.Text = "受控于远程相机的IP:";
            // 
            // checkBox_control
            // 
            this.checkBox_control.AutoSize = true;
            this.checkBox_control.Location = new System.Drawing.Point(28, 123);
            this.checkBox_control.Name = "checkBox_control";
            this.checkBox_control.Size = new System.Drawing.Size(108, 16);
            this.checkBox_control.TabIndex = 5;
            this.checkBox_control.Text = "受控于远程相机";
            this.checkBox_control.UseVisualStyleBackColor = true;
            this.checkBox_control.Click += new System.EventHandler(this.checkBox_control_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 102);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(77, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "受控灯参数：";
            // 
            // textBox_remoteIp
            // 
            this.textBox_remoteIp.Location = new System.Drawing.Point(151, 67);
            this.textBox_remoteIp.Name = "textBox_remoteIp";
            this.textBox_remoteIp.Size = new System.Drawing.Size(126, 21);
            this.textBox_remoteIp.TabIndex = 3;
            this.textBox_remoteIp.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_remoteIp_KeyPress);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(26, 70);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(119, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "远程控制其他相机IP:";
            // 
            // checkBox_remoteEn
            // 
            this.checkBox_remoteEn.AutoSize = true;
            this.checkBox_remoteEn.Location = new System.Drawing.Point(28, 46);
            this.checkBox_remoteEn.Name = "checkBox_remoteEn";
            this.checkBox_remoteEn.Size = new System.Drawing.Size(120, 16);
            this.checkBox_remoteEn.TabIndex = 1;
            this.checkBox_remoteEn.Text = "远程控制其他相机";
            this.checkBox_remoteEn.UseVisualStyleBackColor = true;
            this.checkBox_remoteEn.Click += new System.EventHandler(this.checkBox_remoteEn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "远程控灯参数：";
            // 
            // button_cancle
            // 
            this.button_cancle.Location = new System.Drawing.Point(449, 414);
            this.button_cancle.Name = "button_cancle";
            this.button_cancle.Size = new System.Drawing.Size(75, 23);
            this.button_cancle.TabIndex = 2;
            this.button_cancle.Text = "取消";
            this.button_cancle.UseVisualStyleBackColor = true;
            this.button_cancle.Click += new System.EventHandler(this.button_cancle_Click);
            // 
            // button_apply
            // 
            this.button_apply.Location = new System.Drawing.Point(211, 414);
            this.button_apply.Name = "button_apply";
            this.button_apply.Size = new System.Drawing.Size(75, 23);
            this.button_apply.TabIndex = 3;
            this.button_apply.Text = "确定";
            this.button_apply.UseVisualStyleBackColor = true;
            this.button_apply.Click += new System.EventHandler(this.button_apply_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox_heartbeatInterval);
            this.groupBox1.Controls.Add(this.textBox_uploadInterval);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.checkBox_heartbeatEnbale);
            this.groupBox1.Controls.Add(this.checkBox_uploadEnable);
            this.groupBox1.Controls.Add(this.checkBox_bigPic);
            this.groupBox1.Controls.Add(this.checkBox_smallPic);
            this.groupBox1.Controls.Add(this.textBox_httpAddr);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.checkBox_httpEnable);
            this.groupBox1.Location = new System.Drawing.Point(345, 23);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(377, 179);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "http推送参数";
            // 
            // checkBox_httpEnable
            // 
            this.checkBox_httpEnable.AutoSize = true;
            this.checkBox_httpEnable.Location = new System.Drawing.Point(15, 25);
            this.checkBox_httpEnable.Name = "checkBox_httpEnable";
            this.checkBox_httpEnable.Size = new System.Drawing.Size(96, 16);
            this.checkBox_httpEnable.TabIndex = 0;
            this.checkBox_httpEnable.Text = "启动http推送";
            this.checkBox_httpEnable.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(39, 50);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(89, 12);
            this.label8.TabIndex = 1;
            this.label8.Text = "http推送地址：";
            // 
            // textBox_httpAddr
            // 
            this.textBox_httpAddr.Location = new System.Drawing.Point(134, 41);
            this.textBox_httpAddr.Name = "textBox_httpAddr";
            this.textBox_httpAddr.Size = new System.Drawing.Size(226, 21);
            this.textBox_httpAddr.TabIndex = 2;
            // 
            // checkBox_smallPic
            // 
            this.checkBox_smallPic.AutoSize = true;
            this.checkBox_smallPic.Location = new System.Drawing.Point(41, 82);
            this.checkBox_smallPic.Name = "checkBox_smallPic";
            this.checkBox_smallPic.Size = new System.Drawing.Size(60, 16);
            this.checkBox_smallPic.TabIndex = 3;
            this.checkBox_smallPic.Text = "小图片";
            this.checkBox_smallPic.UseVisualStyleBackColor = true;
            // 
            // checkBox_bigPic
            // 
            this.checkBox_bigPic.AutoSize = true;
            this.checkBox_bigPic.Location = new System.Drawing.Point(149, 82);
            this.checkBox_bigPic.Name = "checkBox_bigPic";
            this.checkBox_bigPic.Size = new System.Drawing.Size(60, 16);
            this.checkBox_bigPic.TabIndex = 4;
            this.checkBox_bigPic.Text = "大图片";
            this.checkBox_bigPic.UseVisualStyleBackColor = true;
            // 
            // checkBox_uploadEnable
            // 
            this.checkBox_uploadEnable.AutoSize = true;
            this.checkBox_uploadEnable.Location = new System.Drawing.Point(41, 112);
            this.checkBox_uploadEnable.Name = "checkBox_uploadEnable";
            this.checkBox_uploadEnable.Size = new System.Drawing.Size(96, 16);
            this.checkBox_uploadEnable.TabIndex = 5;
            this.checkBox_uploadEnable.Text = "启动定时上传";
            this.checkBox_uploadEnable.UseVisualStyleBackColor = true;
            // 
            // checkBox_heartbeatEnbale
            // 
            this.checkBox_heartbeatEnbale.AutoSize = true;
            this.checkBox_heartbeatEnbale.Location = new System.Drawing.Point(41, 145);
            this.checkBox_heartbeatEnbale.Name = "checkBox_heartbeatEnbale";
            this.checkBox_heartbeatEnbale.Size = new System.Drawing.Size(96, 16);
            this.checkBox_heartbeatEnbale.TabIndex = 6;
            this.checkBox_heartbeatEnbale.Text = "启动心跳功能";
            this.checkBox_heartbeatEnbale.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(147, 113);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(137, 12);
            this.label9.TabIndex = 7;
            this.label9.Text = "定时上传时间（分钟）：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(147, 145);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(137, 12);
            this.label10.TabIndex = 8;
            this.label10.Text = "心跳上传时间（分钟）：";
            // 
            // textBox_uploadInterval
            // 
            this.textBox_uploadInterval.Location = new System.Drawing.Point(290, 104);
            this.textBox_uploadInterval.Name = "textBox_uploadInterval";
            this.textBox_uploadInterval.Size = new System.Drawing.Size(70, 21);
            this.textBox_uploadInterval.TabIndex = 9;
            this.textBox_uploadInterval.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_uploadInterval_KeyPress);
            this.textBox_uploadInterval.Leave += new System.EventHandler(this.textBox_uploadInterval_Leave);
            // 
            // textBox_heartbeatInterval
            // 
            this.textBox_heartbeatInterval.Location = new System.Drawing.Point(290, 140);
            this.textBox_heartbeatInterval.Name = "textBox_heartbeatInterval";
            this.textBox_heartbeatInterval.Size = new System.Drawing.Size(70, 21);
            this.textBox_heartbeatInterval.TabIndex = 10;
            this.textBox_heartbeatInterval.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_heartbeatInterval_KeyPress);
            this.textBox_heartbeatInterval.Leave += new System.EventHandler(this.textBox_heartbeatInterval_Leave);
            // 
            // FormSystem
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(734, 466);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button_apply);
            this.Controls.Add(this.button_cancle);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox_spaceEn);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormSystem";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "系统参数";
            this.Load += new System.EventHandler(this.FormSystem_Load);
            this.groupBox_spaceEn.ResumeLayout(false);
            this.groupBox_spaceEn.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox_spaceEn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RadioButton radioButton_enable;
        private System.Windows.Forms.RadioButton radioButton_disable;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox_spaceCode;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBox_controlIp;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox checkBox_control;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_remoteIp;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox checkBox_remoteEn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button_cancle;
        private System.Windows.Forms.Button button_apply;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.RadioButton radioButton_tmp;
        private System.Windows.Forms.RadioButton radioButton_reserve;
        private System.Windows.Forms.RadioButton radioButton_fix;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox_heartbeatInterval;
        private System.Windows.Forms.TextBox textBox_uploadInterval;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox checkBox_heartbeatEnbale;
        private System.Windows.Forms.CheckBox checkBox_uploadEnable;
        private System.Windows.Forms.CheckBox checkBox_bigPic;
        private System.Windows.Forms.CheckBox checkBox_smallPic;
        private System.Windows.Forms.TextBox textBox_httpAddr;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox checkBox_httpEnable;
    }
}