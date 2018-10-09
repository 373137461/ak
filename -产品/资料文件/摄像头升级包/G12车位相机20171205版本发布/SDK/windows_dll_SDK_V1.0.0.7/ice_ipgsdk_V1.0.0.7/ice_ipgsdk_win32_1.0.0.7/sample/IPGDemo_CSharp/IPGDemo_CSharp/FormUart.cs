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
    public partial class FormUart : Form
    {
        public FormUart()
        {
            InitializeComponent();
        }

        public int baudrate = 0;
        public int databits = 0;
        public int parity = 0;
        public int stopbits = 0;
        public int flowctrl = 0;
        public int uartEn = 0;

        public int baudrate2 = 0;
        public int databits2 = 0;
        public int parity2 = 0;
        public int stopbits2 = 0;
        public int flowctrl2 = 0;
        public int uartEn2 = 0;

        private void FormUart_Load(object sender, EventArgs e)
        {
            int nBaudrate = 1200;
            for (; nBaudrate <= 38400; nBaudrate *= 2)
            {
                comboBox_baudrate.Items.Add(nBaudrate.ToString());
                comboBox_baudrate2.Items.Add(nBaudrate.ToString());
            }
            comboBox_baudrate.Items.Add("115200");
            comboBox_baudrate2.Items.Add("115200");

            for (int nDataBits = 5; nDataBits <= 8; nDataBits++)
            {
                comboBox_databits.Items.Add(nDataBits.ToString());
                comboBox_databits2.Items.Add(nDataBits.ToString());
            }

            comboBox_parity.Items.Add("无");
            comboBox_parity.Items.Add("奇校验");
            comboBox_parity.Items.Add("偶校验");
            comboBox_parity.Items.Add("标记");
            comboBox_parity.Items.Add("空格");

            comboBox_parity2.Items.Add("无");
            comboBox_parity2.Items.Add("奇校验");
            comboBox_parity2.Items.Add("偶校验");
            comboBox_parity2.Items.Add("标记");
            comboBox_parity2.Items.Add("空格");

            comboBox_stopbits.Items.Add("1");
            comboBox_stopbits.Items.Add("2");

            comboBox_stopbits2.Items.Add("1");
            comboBox_stopbits2.Items.Add("2");

            comboBox_flowctrl.Items.Add("无");
            comboBox_flowctrl.Items.Add("硬件");
            comboBox_flowctrl.Items.Add("Xon");
            comboBox_flowctrl.Items.Add("Xoff");

            comboBox_flowctrl2.Items.Add("无");
            comboBox_flowctrl2.Items.Add("硬件");
            comboBox_flowctrl2.Items.Add("Xon");
            comboBox_flowctrl2.Items.Add("Xoff");

            comboBox_baudrate.SelectedIndex = baudrate;
            comboBox_databits.SelectedIndex = databits;
            comboBox_parity.SelectedIndex   = parity;
            comboBox_stopbits.SelectedIndex = stopbits;
            comboBox_flowctrl.SelectedIndex = flowctrl;
            checkBox_enableUart.Checked = Convert.ToBoolean(uartEn);

            comboBox_baudrate2.SelectedIndex = baudrate2;
            comboBox_databits2.SelectedIndex = databits2;
            comboBox_parity2.SelectedIndex = parity2;
            comboBox_stopbits2.SelectedIndex = stopbits2;
            comboBox_flowctrl2.SelectedIndex = flowctrl2;
            checkBox_enableUart2.Checked = Convert.ToBoolean(uartEn2);
        }

        private void button2_ok_Click(object sender, EventArgs e)
        {
            baudrate = comboBox_baudrate.SelectedIndex;
            databits = comboBox_databits.SelectedIndex;
            parity   = comboBox_parity.SelectedIndex;
            stopbits = comboBox_stopbits.SelectedIndex;
            flowctrl = comboBox_flowctrl.SelectedIndex;
            uartEn = Convert.ToInt32(checkBox_enableUart.Checked);

            baudrate2 = comboBox_baudrate2.SelectedIndex;
            databits2 = comboBox_databits2.SelectedIndex;
            parity2 = comboBox_parity2.SelectedIndex;
            stopbits2 = comboBox_stopbits2.SelectedIndex;
            flowctrl2 = comboBox_flowctrl2.SelectedIndex;
            uartEn2 = Convert.ToInt32(checkBox_enableUart2.Checked);

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void button_cancle_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
