using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace IPGDemo_CSharp
{
    public partial class FormSystem : Form
    {
        public FormSystem()
        {
            InitializeComponent();
        }
        public const int MAX_SPACE_NUM = 8;
        public uint nSpaceNum = 0;//车位总数
        public int nSpaceCode = 0;
        public uint[] nSpaceEn = new uint[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0};
        public uint[] nSpaceType = new uint[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0 };

        public uint nRemoteEn = 0;
        public string strRemoteIp = "";
        public uint nControlEn = 0;
        public string strControlIp = "";

        public Boolean bSpaceChange = false;
        public Boolean bControlChange = false;

        public http_conf_t httpParam = new http_conf_t();

        private void FormSystem_Load(object sender, EventArgs e)
        {
            for (int i = 1; i <= nSpaceNum; i++ )
                comboBox_spaceCode.Items.Add(i.ToString());
            comboBox_spaceCode.SelectedIndex = nSpaceCode;
            if (0 == nSpaceEn[nSpaceCode])
                radioButton_disable.Checked = true;
            else
                radioButton_enable.Checked = true;

            if (0 == nSpaceType[nSpaceCode])
                radioButton_tmp.Checked = true;
            else if (1 == nSpaceType[nSpaceCode])
                radioButton_reserve.Checked = true;
            else if (2 == nSpaceType[nSpaceCode])
                radioButton_fix.Checked = true;

            checkBox_remoteEn.Checked = Convert.ToBoolean(nRemoteEn);
            textBox_remoteIp.Text = strRemoteIp;
            checkBox_control.Checked = Convert.ToBoolean(nControlEn);
            textBox_controlIp.Text = strControlIp;

            checkBox_httpEnable.Checked = Convert.ToBoolean(httpParam.http_enable);
            textBox_httpAddr.Text = httpParam.http_addr;
            checkBox_smallPic.Checked = Convert.ToBoolean(httpParam.small_pic);
            checkBox_bigPic.Checked = Convert.ToBoolean(httpParam.big_pic);
            checkBox_uploadEnable.Checked = Convert.ToBoolean(httpParam.upload_enable);
            checkBox_heartbeatEnbale.Checked = Convert.ToBoolean(httpParam.heartbeat_enable);
            textBox_heartbeatInterval.Text = httpParam.heartbeat_interval.ToString();
            textBox_uploadInterval.Text = httpParam.upload_interval.ToString();
        }

        private void button_cancle_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void button_apply_Click(object sender, EventArgs e)
        {
            if (bControlChange)
            {
                nRemoteEn = Convert.ToUInt32(checkBox_remoteEn.Checked);
                strRemoteIp = textBox_remoteIp.Text;
                nControlEn = Convert.ToUInt32(checkBox_control.Checked);
                strControlIp = textBox_controlIp.Text;
            }

            httpParam.http_enable = Convert.ToInt32(checkBox_httpEnable.Checked);
            httpParam.http_addr = textBox_httpAddr.Text;
            httpParam.small_pic = Convert.ToInt32(checkBox_smallPic.Checked);
            httpParam.big_pic = Convert.ToInt32(checkBox_bigPic.Checked);
            httpParam.upload_enable = Convert.ToInt32(checkBox_uploadEnable.Checked);
            httpParam.heartbeat_enable = Convert.ToInt32(checkBox_heartbeatEnbale.Checked);

            if ((textBox_uploadInterval.Text == "") || (textBox_heartbeatInterval.Text == ""))
            {
                MessageBox.Show("请输入一个整数");
                return;
            }

            httpParam.upload_interval = Convert.ToInt32(textBox_uploadInterval.Text);
            httpParam.heartbeat_interval = Convert.ToInt32(textBox_heartbeatInterval.Text);

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void updateSpaceParam()
        {
            nSpaceCode = comboBox_spaceCode.SelectedIndex;
            if (radioButton_disable.Checked == true)
                nSpaceEn[nSpaceCode] = 0;
            else
                nSpaceEn[nSpaceCode] = 1;

            if (radioButton_tmp.Checked == true)
                nSpaceType[nSpaceCode] = 0;
            else if (radioButton_reserve.Checked == true)
                nSpaceType[nSpaceCode] = 1;
            else if (radioButton_fix.Checked == true)
                nSpaceType[nSpaceCode] = 2;
        }

        private void comboBox_spaceCode_SelectedIndexChanged(object sender, EventArgs e)
        {
            nSpaceCode = comboBox_spaceCode.SelectedIndex;
            if (0 == nSpaceEn[nSpaceCode])
                radioButton_disable.Checked = true;
            else
                radioButton_enable.Checked = true;

            if (0 == nSpaceType[nSpaceCode])
                radioButton_tmp.Checked = true;
            else if (1 == nSpaceType[nSpaceCode])
                radioButton_reserve.Checked = true;
            else if (2 == nSpaceType[nSpaceCode])
                radioButton_fix.Checked = true;

            bSpaceChange = true;
        }

        private void radioButton_disable_Click(object sender, EventArgs e)
        {
            bSpaceChange = true;
            updateSpaceParam();
        }

        private void radioButton_enable_Click(object sender, EventArgs e)
        {
            bSpaceChange = true;
            updateSpaceParam();
        }

        private void radioButton_tmp_Click(object sender, EventArgs e)
        {
            bSpaceChange = true;
            updateSpaceParam();
        }

        private void radioButton_reserve_Click(object sender, EventArgs e)
        {
            bSpaceChange = true;
            updateSpaceParam();
        }

        private void radioButton_fix_Click(object sender, EventArgs e)
        {
            bSpaceChange = true;
            updateSpaceParam();
        }

        private void checkBox_remoteEn_Click(object sender, EventArgs e)
        {
            bControlChange = true;
        }

        private void checkBox_control_Click(object sender, EventArgs e)
        {
            bControlChange = true;
        }

        private void textBox_remoteIp_KeyPress(object sender, KeyPressEventArgs e)
        {
            bControlChange = true;
        }

        private void textBox_controlIp_KeyPress(object sender, KeyPressEventArgs e)
        {
            bControlChange = true;
        }

        private void textBox_uploadInterval_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_heartbeatInterval_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_heartbeatInterval_Leave(object sender, EventArgs e)
        {
            if (textBox_heartbeatInterval.Text != "")
            {
                if (Convert.ToInt32(textBox_heartbeatInterval.Text) > 60)
                    textBox_heartbeatInterval.Text = "60";
                else if (Convert.ToInt32(textBox_heartbeatInterval.Text) < 1)
                    textBox_heartbeatInterval.Text = "1";
            }
        }

        private void textBox_uploadInterval_Leave(object sender, EventArgs e)
        {
            if (textBox_uploadInterval.Text != "")
            {
                if (Convert.ToInt32(textBox_uploadInterval.Text) > 60)
                    textBox_uploadInterval.Text = "60";
                else if (Convert.ToInt32(textBox_uploadInterval.Text) < 1)
                    textBox_uploadInterval.Text = "1";
            }
        }
    }
}
