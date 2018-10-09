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
    public partial class FormAlgo : Form
    {
        public FormAlgo()
        {
            InitializeComponent();
        }
        public const int MAX_SPACE_NUM = 8;
        public uint nSpaceNum = 0;//车位总数
        public int nSpaceCode = 0;
        public uint nWidth = 0;
        public uint nHeight = 0;
        public Boolean bChange = false;
        public Boolean bSpecial = false;
        private string[] strPPI = new string[5]{"1080P(1920 x 1080)", "900P(1600 x 900)", 
                                      "720P(1280 x 720)", "540P(960 x 540)", "D1(704 x 396)"};

        public short[] nLeftx = new short[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0 };
        public short[] nLefty = new short[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0 };
        public short[] nRightx = new short[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0 };
        public short[] nRighty = new short[MAX_SPACE_NUM] { 0, 0, 0, 0, 0, 0, 0, 0 };


        private void FormAlgo_Load(object sender, EventArgs e)
        {
            int i = 0;
            for (i = 1; i <= nSpaceNum; i++)
                comboBox_spaceCode.Items.Add(i.ToString());
            for (i = 0; i < 5; i++)
                comboBox_settingPPI.Items.Add(strPPI[i]);
   
            comboBox_spaceCode.SelectedIndex = nSpaceCode;
            comboBox_settingPPI.SelectedIndex = getIndex();
            textBox_leftx.Text = nLeftx[nSpaceCode].ToString();
            textBox_lefty.Text = nLefty[nSpaceCode].ToString();
            textBox_rightx.Text = nRightx[nSpaceCode].ToString();
            textBox_righty.Text = nRighty[nSpaceCode].ToString();
            checkBox_selfDefine.Checked = bSpecial; 
        }

        private int getIndex()
        {
            int nIndex = 0;
            if ((nWidth == 1920) && (nHeight == 1080))
                nIndex = 0;
            else if ((nWidth == 1600) && (nHeight == 900))
                nIndex = 1;
            else if ((nWidth == 1280) && (nHeight == 720))
                nIndex = 2;
            else if ((nWidth == 960) && (nHeight == 540))
                nIndex = 3;
            else if ((nWidth == 704) && (nHeight == 396))
                nIndex = 4;

            return nIndex;
        }

        private void getPPI(int nIndex)
        {
            if (nIndex < 0)
                return;
            switch (nIndex)
            {
                case 0:
                    nWidth = 1920;
                    nHeight = 1080;
                    break;
                case 1:
                    nWidth = 1600;
                    nHeight = 900;
                    break;
                case 2:
                    nWidth = 1280;
                    nHeight = 720;
                    break;
                case 3:
                    nWidth = 960;
                    nHeight = 540;
                    break;
                case 4:
                    nWidth = 704;
                    nHeight = 396;
                    break;
            }
        }

        private void updateLoopParam()
        {
            nSpaceCode = comboBox_spaceCode.SelectedIndex;
            if (textBox_leftx.Text != "")
                nLeftx[nSpaceCode] = Convert.ToInt16(textBox_leftx.Text);
            if (textBox_lefty.Text != "")
                nLefty[nSpaceCode] = Convert.ToInt16(textBox_lefty.Text);
            if (textBox_rightx.Text != "")
                nRightx[nSpaceCode] = Convert.ToInt16(textBox_rightx.Text);
            if (textBox_righty.Text != "")
                nRighty[nSpaceCode] = Convert.ToInt16(textBox_righty.Text);
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (checkBox_selfDefine.Checked)
                bSpecial = true;
            else
                bSpecial = false;
            updateLoopParam();

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void buttonCancle_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void textBox_leftx_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_lefty_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_rightx_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_righty_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void comboBox_spaceCode_SelectedIndexChanged(object sender, EventArgs e)
        {
            nSpaceCode = comboBox_spaceCode.SelectedIndex;
            textBox_leftx.Text = nLeftx[nSpaceCode].ToString();
            textBox_lefty.Text = nLefty[nSpaceCode].ToString();
            textBox_rightx.Text = nRightx[nSpaceCode].ToString();
            textBox_righty.Text = nRighty[nSpaceCode].ToString();
        }

        private void textBox_leftx_Leave(object sender, EventArgs e)
        {
            if ((textBox_leftx.Text != "") && (Convert.ToInt32(textBox_leftx.Text) > nWidth))
                textBox_leftx.Text = (nWidth - 10).ToString();
            updateLoopParam();
        }

        private void textBox_lefty_Leave(object sender, EventArgs e)
        {
            if ((textBox_lefty.Text != "") && (Convert.ToInt32(textBox_lefty.Text) > nHeight))
                textBox_lefty.Text = (nHeight - 10).ToString();
            updateLoopParam();
        }

        private void textBox_rightx_Leave(object sender, EventArgs e)
        {
            if ((textBox_rightx.Text != "") && (Convert.ToInt32(textBox_rightx.Text) > nWidth))
                textBox_rightx.Text = (nWidth - 10).ToString();
            updateLoopParam();
        }

        private void textBox_righty_Leave(object sender, EventArgs e)
        {
            if ((textBox_righty.Text != "") && (Convert.ToInt32(textBox_righty.Text) > nHeight))
                textBox_righty.Text = (nHeight - 10).ToString();
            updateLoopParam();
        }

        private void textBox_width_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void textBox_height_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex r = new Regex("^[0-9]{1,}$");
            if (e.KeyChar != (char)8 && (!r.IsMatch(e.KeyChar.ToString())))
            {
                e.Handled = true;
            }
        }

        private void comboBox_settingPPI_SelectedIndexChanged(object sender, EventArgs e)
        {
            uint width = nWidth;
            uint height = nHeight;
            getPPI(comboBox_settingPPI.SelectedIndex);
            float rx = (float)nWidth / width;
            float ry = (float)nHeight / height;

            for (int i = 0; i < nSpaceNum; i++ )
            {
                nLeftx[i] = (short)(nLeftx[i] * rx);
                nLefty[i] = (short)(nLefty[i] * ry);
                nRightx[i] = (short)(nRightx[i] * rx);
                nRighty[i] = (short)(nRighty[i] * rx);
            }

            nSpaceCode = comboBox_spaceCode.SelectedIndex;
            textBox_leftx.Text = nLeftx[nSpaceCode].ToString();
            textBox_lefty.Text = nLefty[nSpaceCode].ToString();
            textBox_rightx.Text = nRightx[nSpaceCode].ToString();
            textBox_righty.Text = nRighty[nSpaceCode].ToString();
        }
    }
}
