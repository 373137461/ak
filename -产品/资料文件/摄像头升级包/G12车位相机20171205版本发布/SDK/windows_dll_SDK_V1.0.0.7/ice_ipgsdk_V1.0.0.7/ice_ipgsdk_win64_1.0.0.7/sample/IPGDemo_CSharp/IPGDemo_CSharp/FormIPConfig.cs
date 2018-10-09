using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace IPGDemo_CSharp
{
    public partial class FormIPConfig : Form
    {
        public FormIPConfig()
        {
            InitializeComponent();
        }

        public string strIP;
        public string strMask;
        public string strGateway;

        private void button_ok_Click(object sender, EventArgs e)
        {
            strIP = textBox_IP.Text;
            strMask = textBox_mask.Text;
            strGateway = textBox_gateway.Text;
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void button_cancle_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void FormIPConfig_Load(object sender, EventArgs e)
        {
            textBox_IP.Text = strIP;
            textBox_gateway.Text = strIP.Substring(0, strIP.LastIndexOf(".")+1) + "1";
        }
    }
}
