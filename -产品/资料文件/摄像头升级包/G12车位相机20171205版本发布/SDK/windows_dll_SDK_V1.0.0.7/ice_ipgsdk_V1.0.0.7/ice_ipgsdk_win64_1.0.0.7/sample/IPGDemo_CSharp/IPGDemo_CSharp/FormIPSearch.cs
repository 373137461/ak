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
    public partial class FormIPSearch : Form
    {
        public FormIPSearch()
        {
            InitializeComponent();
        }

        private void FormIPSearch_Load(object sender, EventArgs e)
        {
            //界面初始化
            this.listViewInfo.Columns.Add("id", 60, HorizontalAlignment.Center);
            this.listViewInfo.Columns.Add("mac", 130, HorizontalAlignment.Center);
            this.listViewInfo.Columns.Add("ip", 110, HorizontalAlignment.Center);
            this.listViewInfo.Columns.Add("ver", 520, HorizontalAlignment.Center);
            this.listViewInfo.Columns.Add("hwInfo", 160, HorizontalAlignment.Center);
            //this.listViewInfo.Columns.Add("", 0, HorizontalAlignment.Center);
            //this.listViewInfo.Columns.Add("", 0, HorizontalAlignment.Center);
        }

        private void button_search_Click(object sender, EventArgs e)
        {
            this.listViewInfo.Items.Clear();
            StringBuilder strResult = new StringBuilder(4096);
            ipgsdk.ICE_IPCSDK_SearchDev(strResult);//设备搜索
            int i = 0, j = 0;
            int nId = 0;

            string strDevInfo = strResult.ToString();
            string[] strSubInfo = strDevInfo.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            for (i = 0; i < strSubInfo.Length; i++)
            {
                nId = this.listViewInfo.Items.Count + 1;
                ListViewItem lvItem = new ListViewItem();
                lvItem.Text = nId.ToString();

                string[] subStr = strSubInfo[i].Split('\t');
                for (j = 0; j < subStr.Length; j++)
                {
                    lvItem.SubItems.Add(subStr[j]);
                }
                this.listViewInfo.Items.Add(lvItem);
            }

            strResult = null;
        }

        private void button_ModIp_Click(object sender, EventArgs e)
        {
            if (this.listViewInfo.SelectedItems.Count == 0)
                return;

            FormIPConfig form = new FormIPConfig();
            form.strIP = this.listViewInfo.SelectedItems[0].SubItems[2].Text;

            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            ipgsdk.ICE_IPCSDK_ModifyDevIP(this.listViewInfo.SelectedItems[0].SubItems[1].Text, 
                form.strIP, form.strMask, form.strGateway);
        }
    }
}
