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
    public partial class FormLightCtrl : Form
    {
        public FormLightCtrl()
        {
            InitializeComponent();
        }

        public int nStyle = 0;
        public int nColor = 0;

        private void button_OK_Click(object sender, EventArgs e)
        {
            nStyle = comboBox_style.SelectedIndex;
            nColor = comboBox_color.SelectedIndex + 1;

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void FormLightCtrl_Load(object sender, EventArgs e)
        {
            if (nStyle >= 0)
                comboBox_style.SelectedIndex = nStyle;
            if (nColor > 0)
                comboBox_color.SelectedIndex = nColor - 1;
            else
                comboBox_color.SelectedIndex = 0;
        }
    }
}
