using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace IPGDemo_CSharp
{
    public partial class FormLocalSetting : Form
    {
        public FormLocalSetting()
        {
            InitializeComponent();
        }

        public string strStorePath = "";

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folderBrowserDlg = new FolderBrowserDialog();
            folderBrowserDlg.Description = "请选择保存输出图片的文件夹";
            folderBrowserDlg.ShowNewFolderButton = true;
            folderBrowserDlg.RootFolder = Environment.SpecialFolder.MyComputer;
            DialogResult result = folderBrowserDlg.ShowDialog();
            if (result == DialogResult.OK)
            {
                string folderName = folderBrowserDlg.SelectedPath;
                if (folderName != "")
                    textBoxPath.Text = folderName;
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            strStorePath = textBoxPath.Text;

            try
            {
                //读取设置
                FileStream fs = new FileStream("param.dat", FileMode.Create, FileAccess.Write);
                if (fs != null)
                {
                    BinaryWriter bw = new BinaryWriter(fs);
                    if (bw != null)
                    {
                        bw.Write(strStorePath.ToCharArray(0, strStorePath.Length));

                        bw.Close();
                    }
                    fs.Close();
                  }
            }
            catch (System.Exception ex)
            {

            }
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void buttonCancle_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void FormLocalSetting_Load(object sender, EventArgs e)
        {
            textBoxPath.Text = strStorePath;
        }
    }
}
