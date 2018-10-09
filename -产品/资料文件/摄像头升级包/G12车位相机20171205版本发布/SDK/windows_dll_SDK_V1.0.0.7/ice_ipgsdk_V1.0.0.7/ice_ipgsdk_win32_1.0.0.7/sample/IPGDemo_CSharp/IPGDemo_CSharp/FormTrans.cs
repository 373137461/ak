using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace IPGDemo_CSharp
{
    public partial class FormTrans : Form
    {
        public IntPtr m_hSDK;
        public int m_type;

        private byte[] m_trans_buf = new byte[4096];
        private uint m_trans_len = 0;

        public FormTrans()
        {
            InitializeComponent();
        }

        [DllImport("user32.dll")]
        public static extern int MessageBeep(uint uType);

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            char code = (char)e.KeyCode;

            if (Char.IsNumber(code) ||
                ((code >= 'a') && (code <= 'f')) ||
                ((code >= 'A') && (code <= 'F')) || Char.IsWhiteSpace(code) ||
                (0x08 == code) || (0x2E == code) ||
                (0x11 == code) || (0x1B == code) ||
                (0x25 == code) || (0x26 == code) ||
                (0x27 == code) || (0x28 == code) ||
                (e.Control && (('C' == code) || ('V' == code))))
                e.SuppressKeyPress = false;
            else
            {
                MessageBeep(0x00000030);
                e.SuppressKeyPress = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int len = textBox1.Text.Length, count = 0;
            for (int i = 0; i < len; i++)
            {
                char data = textBox1.Text[i];
                if (Char.IsWhiteSpace(data))
                    continue;

                int value = 0;
                if (Char.IsNumber(data))
                    value = data - '0';
                else
                    value = 10 + data - 'A';

                if ((len - 1 == i) && (0 != ((count + 1) % 2)))
                {
                    m_trans_buf[m_trans_len] = (byte)value;
                    m_trans_len++;
                }
                else
                {
                    if (0 == (count++ % 2))
                    {
                        m_trans_buf[m_trans_len] = (byte)(value << 4);
                    }
                    else
                    {
                        m_trans_buf[m_trans_len] += (byte)value;
                        m_trans_len++;
                    }
                }
            }

            if (0 == m_type)
                ipgsdk.ICE_IPCSDK_TransSerialPort(m_hSDK, m_trans_buf, m_trans_len);
            else
                ipgsdk.ICE_IPCSDK_TransSerialPort_RS232(m_hSDK, m_trans_buf, m_trans_len);

            m_trans_len = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
