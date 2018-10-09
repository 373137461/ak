namespace IPGDemo_CSharp
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.textBox_IP = new System.Windows.Forms.TextBox();
            this.button_login = new System.Windows.Forms.Button();
            this.listView_devInfo = new System.Windows.Forms.ListView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_lightCtl = new System.Windows.Forms.Button();
            this.button_uartSend_485 = new System.Windows.Forms.Button();
            this.button_uartSend_232 = new System.Windows.Forms.Button();
            this.button_allState = new System.Windows.Forms.Button();
            this.comboBox_spaceId = new System.Windows.Forms.ComboBox();
            this.button_singleState = new System.Windows.Forms.Button();
            this.button_algoParam = new System.Windows.Forms.Button();
            this.button_uartParam = new System.Windows.Forms.Button();
            this.button_systemParam = new System.Windows.Forms.Button();
            this.button_logout = new System.Windows.Forms.Button();
            this.listView_spaceInfo = new System.Windows.Forms.ListView();
            this.listBoxInfo = new System.Windows.Forms.ListBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.选项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SettingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DevSearchToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.button_getDevTime = new System.Windows.Forms.Button();
            this.button_syncTime = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(24, 32);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(395, 218);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox2.Location = new System.Drawing.Point(429, 32);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(395, 218);
            this.pictureBox2.TabIndex = 1;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox3.Location = new System.Drawing.Point(24, 258);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(395, 218);
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox4
            // 
            this.pictureBox4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox4.Location = new System.Drawing.Point(429, 256);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(395, 218);
            this.pictureBox4.TabIndex = 3;
            this.pictureBox4.TabStop = false;
            // 
            // textBox_IP
            // 
            this.textBox_IP.Location = new System.Drawing.Point(841, 34);
            this.textBox_IP.Name = "textBox_IP";
            this.textBox_IP.Size = new System.Drawing.Size(123, 21);
            this.textBox_IP.TabIndex = 4;
            this.textBox_IP.Text = "192.168.55.100";
            // 
            // button_login
            // 
            this.button_login.Location = new System.Drawing.Point(970, 33);
            this.button_login.Name = "button_login";
            this.button_login.Size = new System.Drawing.Size(65, 23);
            this.button_login.TabIndex = 5;
            this.button_login.Text = "登录";
            this.button_login.UseVisualStyleBackColor = true;
            this.button_login.Click += new System.EventHandler(this.button_login_Click);
            // 
            // listView_devInfo
            // 
            this.listView_devInfo.FullRowSelect = true;
            this.listView_devInfo.GridLines = true;
            this.listView_devInfo.HideSelection = false;
            this.listView_devInfo.Location = new System.Drawing.Point(843, 68);
            this.listView_devInfo.Name = "listView_devInfo";
            this.listView_devInfo.Size = new System.Drawing.Size(192, 111);
            this.listView_devInfo.TabIndex = 7;
            this.listView_devInfo.UseCompatibleStateImageBehavior = false;
            this.listView_devInfo.View = System.Windows.Forms.View.Details;
            this.listView_devInfo.Click += new System.EventHandler(this.listView_devInfo_Click);
            this.listView_devInfo.MouseUp += new System.Windows.Forms.MouseEventHandler(this.listView_devInfo_MouseUp);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_syncTime);
            this.groupBox1.Controls.Add(this.button_getDevTime);
            this.groupBox1.Controls.Add(this.button_lightCtl);
            this.groupBox1.Controls.Add(this.button_uartSend_485);
            this.groupBox1.Controls.Add(this.button_uartSend_232);
            this.groupBox1.Controls.Add(this.button_allState);
            this.groupBox1.Controls.Add(this.comboBox_spaceId);
            this.groupBox1.Controls.Add(this.button_singleState);
            this.groupBox1.Controls.Add(this.button_algoParam);
            this.groupBox1.Controls.Add(this.button_uartParam);
            this.groupBox1.Controls.Add(this.button_systemParam);
            this.groupBox1.Controls.Add(this.button_logout);
            this.groupBox1.Location = new System.Drawing.Point(841, 187);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(251, 139);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "操作";
            // 
            // button_lightCtl
            // 
            this.button_lightCtl.Enabled = false;
            this.button_lightCtl.Location = new System.Drawing.Point(180, 49);
            this.button_lightCtl.Name = "button_lightCtl";
            this.button_lightCtl.Size = new System.Drawing.Size(65, 23);
            this.button_lightCtl.TabIndex = 9;
            this.button_lightCtl.Text = "强制控灯";
            this.button_lightCtl.UseVisualStyleBackColor = true;
            this.button_lightCtl.Click += new System.EventHandler(this.button_lightCtl_Click);
            // 
            // button_uartSend_485
            // 
            this.button_uartSend_485.Enabled = false;
            this.button_uartSend_485.Location = new System.Drawing.Point(89, 78);
            this.button_uartSend_485.Name = "button_uartSend_485";
            this.button_uartSend_485.Size = new System.Drawing.Size(85, 23);
            this.button_uartSend_485.TabIndex = 8;
            this.button_uartSend_485.Text = "485串口发送";
            this.button_uartSend_485.UseVisualStyleBackColor = true;
            this.button_uartSend_485.Click += new System.EventHandler(this.button_uartSend_485_Click);
            // 
            // button_uartSend_232
            // 
            this.button_uartSend_232.Enabled = false;
            this.button_uartSend_232.Location = new System.Drawing.Point(89, 107);
            this.button_uartSend_232.Name = "button_uartSend_232";
            this.button_uartSend_232.Size = new System.Drawing.Size(85, 23);
            this.button_uartSend_232.TabIndex = 7;
            this.button_uartSend_232.Text = "232串口发送";
            this.button_uartSend_232.UseVisualStyleBackColor = true;
            this.button_uartSend_232.Click += new System.EventHandler(this.button_uartSend_232_Click);
            // 
            // button_allState
            // 
            this.button_allState.Enabled = false;
            this.button_allState.Location = new System.Drawing.Point(89, 49);
            this.button_allState.Name = "button_allState";
            this.button_allState.Size = new System.Drawing.Size(85, 23);
            this.button_allState.TabIndex = 6;
            this.button_allState.Text = "所有车位状态";
            this.button_allState.UseVisualStyleBackColor = true;
            this.button_allState.Click += new System.EventHandler(this.button_allState_Click);
            // 
            // comboBox_spaceId
            // 
            this.comboBox_spaceId.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_spaceId.FormattingEnabled = true;
            this.comboBox_spaceId.Location = new System.Drawing.Point(180, 20);
            this.comboBox_spaceId.Name = "comboBox_spaceId";
            this.comboBox_spaceId.Size = new System.Drawing.Size(65, 20);
            this.comboBox_spaceId.TabIndex = 5;
            // 
            // button_singleState
            // 
            this.button_singleState.Enabled = false;
            this.button_singleState.Location = new System.Drawing.Point(89, 20);
            this.button_singleState.Name = "button_singleState";
            this.button_singleState.Size = new System.Drawing.Size(85, 23);
            this.button_singleState.TabIndex = 4;
            this.button_singleState.Text = "单个车位状态";
            this.button_singleState.UseVisualStyleBackColor = true;
            this.button_singleState.Click += new System.EventHandler(this.button_singleState_Click);
            // 
            // button_algoParam
            // 
            this.button_algoParam.Enabled = false;
            this.button_algoParam.Location = new System.Drawing.Point(6, 107);
            this.button_algoParam.Name = "button_algoParam";
            this.button_algoParam.Size = new System.Drawing.Size(75, 23);
            this.button_algoParam.TabIndex = 3;
            this.button_algoParam.Text = "算法参数";
            this.button_algoParam.UseVisualStyleBackColor = true;
            this.button_algoParam.Click += new System.EventHandler(this.button_algoParam_Click);
            // 
            // button_uartParam
            // 
            this.button_uartParam.Enabled = false;
            this.button_uartParam.Location = new System.Drawing.Point(6, 78);
            this.button_uartParam.Name = "button_uartParam";
            this.button_uartParam.Size = new System.Drawing.Size(75, 23);
            this.button_uartParam.TabIndex = 2;
            this.button_uartParam.Text = "外设参数";
            this.button_uartParam.UseVisualStyleBackColor = true;
            this.button_uartParam.Click += new System.EventHandler(this.button_uartParam_Click);
            // 
            // button_systemParam
            // 
            this.button_systemParam.Enabled = false;
            this.button_systemParam.Location = new System.Drawing.Point(6, 49);
            this.button_systemParam.Name = "button_systemParam";
            this.button_systemParam.Size = new System.Drawing.Size(75, 23);
            this.button_systemParam.TabIndex = 1;
            this.button_systemParam.Text = "系统参数";
            this.button_systemParam.UseVisualStyleBackColor = true;
            this.button_systemParam.Click += new System.EventHandler(this.button_systemParam_Click);
            // 
            // button_logout
            // 
            this.button_logout.Enabled = false;
            this.button_logout.Location = new System.Drawing.Point(6, 20);
            this.button_logout.Name = "button_logout";
            this.button_logout.Size = new System.Drawing.Size(74, 23);
            this.button_logout.TabIndex = 0;
            this.button_logout.Text = "退出";
            this.button_logout.UseVisualStyleBackColor = true;
            this.button_logout.Click += new System.EventHandler(this.button_logout_Click);
            // 
            // listView_spaceInfo
            // 
            this.listView_spaceInfo.FullRowSelect = true;
            this.listView_spaceInfo.GridLines = true;
            this.listView_spaceInfo.Location = new System.Drawing.Point(24, 485);
            this.listView_spaceInfo.Name = "listView_spaceInfo";
            this.listView_spaceInfo.Size = new System.Drawing.Size(800, 196);
            this.listView_spaceInfo.TabIndex = 10;
            this.listView_spaceInfo.UseCompatibleStateImageBehavior = false;
            this.listView_spaceInfo.View = System.Windows.Forms.View.Details;
            // 
            // listBoxInfo
            // 
            this.listBoxInfo.FormattingEnabled = true;
            this.listBoxInfo.ItemHeight = 12;
            this.listBoxInfo.Location = new System.Drawing.Point(843, 341);
            this.listBoxInfo.Name = "listBoxInfo";
            this.listBoxInfo.Size = new System.Drawing.Size(249, 340);
            this.listBoxInfo.TabIndex = 11;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.选项ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1104, 25);
            this.menuStrip1.TabIndex = 12;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 选项ToolStripMenuItem
            // 
            this.选项ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.SettingToolStripMenuItem,
            this.DevSearchToolStripMenuItem});
            this.选项ToolStripMenuItem.Name = "选项ToolStripMenuItem";
            this.选项ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.选项ToolStripMenuItem.Text = "选项";
            // 
            // SettingToolStripMenuItem
            // 
            this.SettingToolStripMenuItem.Name = "SettingToolStripMenuItem";
            this.SettingToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.SettingToolStripMenuItem.Text = "设置";
            this.SettingToolStripMenuItem.Click += new System.EventHandler(this.SettingToolStripMenuItem_Click);
            // 
            // DevSearchToolStripMenuItem
            // 
            this.DevSearchToolStripMenuItem.Name = "DevSearchToolStripMenuItem";
            this.DevSearchToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.DevSearchToolStripMenuItem.Text = "设备搜索";
            this.DevSearchToolStripMenuItem.Click += new System.EventHandler(this.DevSearchToolStripMenuItem_Click);
            // 
            // button_getDevTime
            // 
            this.button_getDevTime.Enabled = false;
            this.button_getDevTime.Location = new System.Drawing.Point(180, 78);
            this.button_getDevTime.Name = "button_getDevTime";
            this.button_getDevTime.Size = new System.Drawing.Size(65, 23);
            this.button_getDevTime.TabIndex = 10;
            this.button_getDevTime.Text = "获取时间";
            this.button_getDevTime.UseVisualStyleBackColor = true;
            this.button_getDevTime.Click += new System.EventHandler(this.button_getDevTime_Click);
            // 
            // button_syncTime
            // 
            this.button_syncTime.Enabled = false;
            this.button_syncTime.Location = new System.Drawing.Point(180, 107);
            this.button_syncTime.Name = "button_syncTime";
            this.button_syncTime.Size = new System.Drawing.Size(65, 23);
            this.button_syncTime.TabIndex = 11;
            this.button_syncTime.Text = "时间同步";
            this.button_syncTime.UseVisualStyleBackColor = true;
            this.button_syncTime.Click += new System.EventHandler(this.button_syncTime_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1104, 693);
            this.Controls.Add(this.listBoxInfo);
            this.Controls.Add(this.listView_spaceInfo);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listView_devInfo);
            this.Controls.Add(this.button_login);
            this.Controls.Add(this.textBox_IP);
            this.Controls.Add(this.pictureBox4);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IPGSDK_Demo";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.TextBox textBox_IP;
        private System.Windows.Forms.Button button_login;
        private System.Windows.Forms.ListView listView_devInfo;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button_logout;
        private System.Windows.Forms.Button button_allState;
        private System.Windows.Forms.ComboBox comboBox_spaceId;
        private System.Windows.Forms.Button button_singleState;
        private System.Windows.Forms.Button button_algoParam;
        private System.Windows.Forms.Button button_uartParam;
        private System.Windows.Forms.Button button_systemParam;
        private System.Windows.Forms.ListView listView_spaceInfo;
        private System.Windows.Forms.Button button_uartSend_232;
        private System.Windows.Forms.ListBox listBoxInfo;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 选项ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SettingToolStripMenuItem;
        private System.Windows.Forms.Button button_uartSend_485;
        private System.Windows.Forms.ToolStripMenuItem DevSearchToolStripMenuItem;
        private System.Windows.Forms.Button button_lightCtl;
        private System.Windows.Forms.Button button_syncTime;
        private System.Windows.Forms.Button button_getDevTime;
    }
}

