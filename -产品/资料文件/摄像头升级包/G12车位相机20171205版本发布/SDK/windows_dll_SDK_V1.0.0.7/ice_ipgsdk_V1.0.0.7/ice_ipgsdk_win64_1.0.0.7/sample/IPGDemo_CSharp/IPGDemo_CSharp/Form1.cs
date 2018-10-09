using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace IPGDemo_CSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private const int MAX_CONNECT_NUM = 4;
        private IntPtr[] pUid = new IntPtr[MAX_CONNECT_NUM] { IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero };
        private uint nTotalNum = 0;
        private string strStorePath = "";
        private uint nDeviceEventCount = 0;
        private uint[] nRecvPortCount_RS485 = new uint[MAX_CONNECT_NUM] { 0, 0, 0, 0 };
        private uint[] nRecvPortCount_RS232 = new uint[MAX_CONNECT_NUM] { 0, 0, 0, 0 };
        //private string[] strSpaceStatus = new string[] {"无", "车位有车", "空车位", "单车占多车位", "车位禁用"};
        private string[] strPlateColor = new string[] { "未知", "蓝色", "黄色", "白色", "黑色", "绿色", "绿色" };
        private string[] strCarType = new string[] {"临时", "预定", "固定"};
        private string[] strEventType = new string[] {"无变化", "入车", "出车"};
        private uint[] nTotalSpaceNum = new uint[MAX_CONNECT_NUM] { 0, 0, 0, 0};
        private ipgsdk.ICE_IPCSDK_OnDeviceEvent onDeviceEvent;
        private ipgsdk.ICE_IPCSDK_OnParkingSpaceInfo onParkingSpaceInfo;
        private ipgsdk.ICE_IPCSDK_OnSerialPort onSerialPort;
        private ipgsdk.ICE_IPCSDK_OnSerialPort_RS232 onSerialPortRS232;

        public delegate void UpdateDeviceEvent(string strIP, uint nType, uint ndata1, uint ndata2, uint ndata3, uint ndata4);
        public UpdateDeviceEvent updateDeviceEvent;
        public delegate void UpdateSpaceInfo(string strIP, ICE_PARKING_SPACE_RESULT_S pstParkingResult);
        public UpdateSpaceInfo updateSpaceInfo;
        public delegate void UpdatePortInfo(int type, string strIp, uint len, int index, string data);
        public UpdatePortInfo updatePortInfo;

        public void showDeviceEvent(string strIP, uint nType, uint ndata1, uint ndata2, uint ndata3, uint ndata4)
        {
            if (listBoxInfo.Items.Count > 1024)
            {
                listBoxInfo.Items.Clear();
            }
            string strText = "";
            if (0 == nType)
                strText = strIP + ":当前状态离线";
            else if (1 == nType)
                strText = strIP + ":当前状态在线";
            else if (2 == nType)
            {
                nDeviceEventCount++;
                strText = nDeviceEventCount.ToString() + " " + strIP + "IO状态改变： " +
                    ndata1.ToString() + ndata2.ToString() + ndata3.ToString() + ndata4.ToString();
            }
            listBoxInfo.Items.Insert(0, strText);
        }

        public void SDK_OnDeviceEvent(System.IntPtr pvParam,
           [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
           uint u32EventType, uint u32EventData1, uint u32EventData2, uint u32EventData3, uint u32EventData4)
        {
            IAsyncResult syncResult = this.BeginInvoke(updateDeviceEvent, pcIP, u32EventType, u32EventData1,
                u32EventData2, u32EventData3, u32EventData4);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ipgsdk.ICE_IPCSDK_Init();

            onDeviceEvent = new ipgsdk.ICE_IPCSDK_OnDeviceEvent(SDK_OnDeviceEvent);
            onParkingSpaceInfo = new ipgsdk.ICE_IPCSDK_OnParkingSpaceInfo(SDK_OnParkingSpaceInfo);
            onSerialPort = new ipgsdk.ICE_IPCSDK_OnSerialPort(SDK_OnSerialPort);
            onSerialPortRS232 = new ipgsdk.ICE_IPCSDK_OnSerialPort_RS232(SDK_OnSerialPortRS232);
            updateDeviceEvent = new UpdateDeviceEvent(showDeviceEvent);
            updateSpaceInfo = new UpdateSpaceInfo(showInfo);
            updatePortInfo = new UpdatePortInfo(showPortData);

            this.listView_devInfo.Columns.Add("设备列表", listView_devInfo.Width, HorizontalAlignment.Center);

            this.listView_spaceInfo.Columns.Add("序号", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("相机ip", listView_spaceInfo.Width * 2/ 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("时间", listView_spaceInfo.Width * 2/ 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("车位ID", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("车位状态", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("车牌号码", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("车牌颜色", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("车位类型", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);
            this.listView_spaceInfo.Columns.Add("事件类型", listView_spaceInfo.Width / 11, HorizontalAlignment.Center);

            if (File.Exists(@"./param.dat"))
            {
                FileStream fs = new FileStream("param.dat", FileMode.Open, FileAccess.Read);
                if (fs != null)
                {
                    try
                    {
                        BinaryReader br = new BinaryReader(fs);
                        if (br != null)
                        {
                            strStorePath = new string(br.ReadChars((int)fs.Length));
                            br.Close();
                        }
                        fs.Close();
                    }
                    catch (System.Exception ex)
                    {

                    }
                }
            }

            ipgsdk.ICE_IPCSDK_SetDeviceEventCallBack(IntPtr.Zero, onDeviceEvent, new IntPtr(0));
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            int count = this.listView_devInfo.Items.Count;
            if (count > MAX_CONNECT_NUM)
                count = MAX_CONNECT_NUM;
            for (int i = 0; i < count; i++ )
            {
                if (IntPtr.Zero != pUid[i])
                {
                    ipgsdk.ICE_IPCSDK_Logout(pUid[i]);
                    pUid[i] = IntPtr.Zero;
                }
            }
            ipgsdk.ICE_IPCSDK_Fini();
        }

        private void savePic(byte[] picData, string strIP)
        {
            DateTime dt = DateTime.Now;

            string strDir = strStorePath + @"\车位抓拍_CSharp\" + strIP + @"\" + dt.ToString("yyyyMMdd");
            if (!Directory.Exists(strDir))
                Directory.CreateDirectory(strDir);

            string strPicName = strDir + @"\" + dt.ToString("yyyyMMddHHmmss") + ".jpg";
            if (File.Exists(strPicName))
            {
                 int count = 1;
                 while (count <= 10)
                 {
                     strPicName = strDir + @"\" + dt.ToString("yyyyMMddHHmmss") + "_" + count.ToString() + ".jpg";
                     if (!File.Exists(strPicName))
                     {
                         break;
                     }
                     count++;
                 }
            }

            try
            {
                FileStream fs = new FileStream(strPicName, FileMode.Create, FileAccess.Write);
                BinaryWriter bw = new BinaryWriter(fs);
                bw.Write(picData);
                bw.Close();
                fs.Close();           
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        private string getSpaceStatus(int nSpaceStatus)
        {
            string strSpaceStatus = null;
            switch (nSpaceStatus)
            {
                case 0x00:
                    strSpaceStatus = "无";
                    break;
                case 0x01:
                    strSpaceStatus = "车位有车";
                    break;
                case 0x02:
                    strSpaceStatus = "空车位";
                    break;
                case 0x04:
                    strSpaceStatus = "单车占多车位";
                    break;
                case 0x08:
                    strSpaceStatus = "车位禁用";
                    break;

            }
            return strSpaceStatus;
        }

        private void showInfo(string strIP, ICE_PARKING_SPACE_RESULT_S pstParkingResult)
        {
            DateTime dt = new DateTime();
            dt = DateTime.Now;
            for (int i = 0; i < pstParkingResult.u8ParkingPlaceNum; i++)
            {
                nTotalNum++;
                ListViewItem lvItem = new ListViewItem();
                lvItem.Text = nTotalNum.ToString();
                lvItem.SubItems.Add(strIP);
                lvItem.SubItems.Add(dt.ToString("yyyy-MM-dd HH:mm:ss"));
                lvItem.SubItems.Add((i + 1).ToString());
                string strSpaceStatus = getSpaceStatus(pstParkingResult.astOutput[i].enParkingPlaceStatus);
                if ((pstParkingResult.astOutput[i].enParkingPlaceStatus >= 0) && (pstParkingResult.astOutput[i].enParkingPlaceStatus <= 8))
                    lvItem.SubItems.Add(strSpaceStatus);
                lvItem.SubItems.Add(pstParkingResult.astOutput[i].stPlateInfo.as8PlateNum);
                if ((pstParkingResult.astOutput[i].stPlateInfo.ePlateColor >= 0) && (pstParkingResult.astOutput[i].stPlateInfo.ePlateColor < 7))
                    lvItem.SubItems.Add(strPlateColor[pstParkingResult.astOutput[i].stPlateInfo.ePlateColor]);
                if ((pstParkingResult.astOutput[i].s32CarType >= 0) && (pstParkingResult.astOutput[i].s32CarType < 3))
                    lvItem.SubItems.Add(strCarType[pstParkingResult.astOutput[i].s32CarType]);
                if ((pstParkingResult.astOutput[i].s32EventType < 3) && (pstParkingResult.astOutput[i].s32EventType >= 0))
                    lvItem.SubItems.Add(strEventType[pstParkingResult.astOutput[i].s32EventType]);
                listView_spaceInfo.Items.Insert(0, lvItem);
            }
        }

        //显示收到的串口数据
        public void showPortData(int type, string strIp, uint len, int index, string data)
        {
            string strText = "";

            if (0 == type)
            {
                nRecvPortCount_RS485[index]++;
                strText = nRecvPortCount_RS485[index].ToString() + ":" + strIp + "接收到RS485数据 " + len.ToString() + "字节"; ;
            }
            else
            {
                nRecvPortCount_RS232[index]++;
                strText = nRecvPortCount_RS232[index].ToString() + ":" + strIp + "接收到RS232数据 " + len.ToString() + "字节"; ;
            }

            if (data != null)
                listBoxInfo.Items.Insert(0, data);
            if (strText != null)
                listBoxInfo.Items.Insert(0, strText);
        }

        public void SDK_OnParkingSpaceInfo(System.IntPtr pvParam,
       [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
       ref ICE_PARKING_SPACE_RESULT_S pstParkingResult, System.IntPtr pcPicData, uint u32PicLen,
       System.IntPtr pvReserve, uint u32Reserve1, uint u32Reserve2, uint u32Reserve3, uint u32Reserve4)
        {
            int index = (int)pvParam;
            this.BeginInvoke(updateSpaceInfo, pcIP, pstParkingResult);


            if (u32PicLen > 0)
            {
                IntPtr ptr = pcPicData;
                byte[] dataJpg = new byte[u32PicLen];
                Marshal.Copy(ptr, dataJpg, 0, (int)u32PicLen);
                savePic(dataJpg, pcIP);
            }
        }

        public void SDK_OnSerialPort(System.IntPtr pvParam,
           [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
           System.IntPtr pcData, uint u32Len)
        {
            int index = (int)pvParam;
            IntPtr tmp = pcData;
            byte[] dataPort2 = new byte[u32Len];
            Marshal.Copy(tmp, dataPort2, 0, dataPort2.Length);//拷贝串口数据
            string strPort = BitConverter.ToString(dataPort2);
            strPort = strPort.Replace("-", " ");
            //委托，用于在界面上显示收到的串口数据
            IAsyncResult syncResult = this.BeginInvoke(updatePortInfo, 0, pcIP, u32Len, index, strPort);
        }

        public void SDK_OnSerialPortRS232(System.IntPtr pvParam,
           [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pcIP,
           System.IntPtr pcData, uint u32Len)
        {
            int index = (int)pvParam;
            IntPtr tmp = pcData;
            byte[] dataPort2 = new byte[u32Len];
            Marshal.Copy(tmp, dataPort2, 0, dataPort2.Length);//拷贝串口数据
            string strPort = BitConverter.ToString(dataPort2);
            strPort = strPort.Replace("-", " ");
            //委托，用于在界面上显示收到的串口数据
            IAsyncResult syncResult = this.BeginInvoke(updatePortInfo, 1, pcIP, u32Len, index, strPort);
        }

        private void button_login_Click(object sender, EventArgs e)
        {
            int index = 0;
            if (this.listView_devInfo.SelectedItems.Count != 0)
            {
                index = this.listView_devInfo.SelectedItems[0].Index;
                if ((index < MAX_CONNECT_NUM) && (IntPtr.Zero != pUid[index]))
                {
                    MessageBox.Show("选中的设备正在使用中，请断开后再尝试。");
                    return;
                }
            }
            else if (this.listView_devInfo.Items.Count < MAX_CONNECT_NUM)
                index = this.listView_devInfo.Items.Count;
            else
            {
                MessageBox.Show("连接满，请断开一路连接后再尝试。");
                return;
            }
            pUid[index] = ipgsdk.ICE_IPCSDK_Login(textBox_IP.Text, "", "",IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, 1);
            if (IntPtr.Zero != pUid[index])
            {
                IntPtr videoHwnd = new IntPtr();
                if (0 == index)
                    videoHwnd = pictureBox1.Handle;
                else if (1 == index)
                    videoHwnd = pictureBox2.Handle;
                else if (2 == index)
                    videoHwnd = pictureBox3.Handle;
                else if (3 == index)
                    videoHwnd = pictureBox4.Handle;
                if (videoHwnd != IntPtr.Zero)
                {
                    //连接视频，因为ICE_IPCSDK_Login不带视频流；如果不需要视频，可不调用该接口
                    UInt32 ret = ipgsdk.ICE_IPCSDK_StartStream(pUid[index], 1, (UInt32)videoHwnd);
                    if (ret == 0)
                    {
                        ipgsdk.ICE_IPCSDK_StopStream(pUid[this.listView_devInfo.Items.Count]);//连接视频失败，调用断开视频接口释放资源
                        return;
                    }
                }
                else
                {
                    MessageBox.Show("未获得视频播放窗口");
                    return;
                }

                ipgsdk.ICE_IPCSDK_SetParkingSpaceInfoCallBack(pUid[index], onParkingSpaceInfo, new IntPtr(index));
                ipgsdk.ICE_IPCSDK_SetSerialPortCallBack(pUid[index], onSerialPort, new IntPtr(index));
                ipgsdk.ICE_IPCSDK_SetSerialPortCallBack_RS232(pUid[index], onSerialPortRS232, new IntPtr(index));
                uint success = ipgsdk.ICE_IPCSDK_GetParkingSpaceNum(pUid[index], ref nTotalSpaceNum[index]);
                if (0 == success)
                    nTotalSpaceNum[index] = 2;

                comboBox_spaceId.Items.Clear();
                for (int i = 1; i <= nTotalSpaceNum[index]; i++)
                {
                    comboBox_spaceId.Items.Add(i.ToString());
                    comboBox_spaceId.SelectedIndex = 0;
                }
                comboBox_spaceId.SelectedIndex = 0;
                if (this.listView_devInfo.SelectedItems.Count != 0)
                    listView_devInfo.Items[index].Checked = true;

                if (this.listView_devInfo.SelectedItems.Count == 0)
                {
                    ListViewItem lvItem = new ListViewItem();//连接成功，添加到列表中
                    lvItem.Text = textBox_IP.Text;
                    this.listView_devInfo.Items.Add(lvItem);
                }
                else
                {
                    this.listView_devInfo.SelectedItems[0].Text = textBox_IP.Text;
                    button_login.Enabled = false;
                    button_logout.Enabled = true;
                    button_systemParam.Enabled = true;
                    button_uartParam.Enabled = true;
                    button_algoParam.Enabled = true;
                    button_singleState.Enabled = true;
                    button_allState.Enabled = true;
                    button_uartSend_485.Enabled = true;
                    button_uartSend_232.Enabled = true;
                    button_lightCtl.Enabled = true;
                    button_syncTime.Enabled = true;
                    button_getDevTime.Enabled = true;
                }
            }
            else
            {
                MessageBox.Show("登录失败");
            }
        }

        private void button_logout_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count != 0)
            {
                int index = this.listView_devInfo.SelectedItems[0].Index;
                if ((index < MAX_CONNECT_NUM) && (IntPtr.Zero != pUid[index]))
                {
                    ipgsdk.ICE_IPCSDK_Logout(pUid[index]);
                    pUid[index] = IntPtr.Zero;
                }
                button_login.Enabled = true;
                button_logout.Enabled = false;
                button_systemParam.Enabled = false;
                button_uartParam.Enabled = false;
                button_algoParam.Enabled = false;
                button_singleState.Enabled = false;
                button_allState.Enabled = false;
                button_uartSend_485.Enabled = false;
                button_uartSend_232.Enabled = false;
                nTotalSpaceNum[index] = 0;
                button_lightCtl.Enabled = false;
                button_syncTime.Enabled = false;
                button_getDevTime.Enabled = false;
            }
        }

        private void listView_devInfo_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            textBox_IP.Text = this.listView_devInfo.SelectedItems[0].Text;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index < MAX_CONNECT_NUM) && (IntPtr.Zero != pUid[index]))
            {
                button_login.Enabled = false;
                button_logout.Enabled = true;
                button_systemParam.Enabled = true;
                button_uartParam.Enabled = true;
                button_algoParam.Enabled = true;
                button_singleState.Enabled = true;
                button_allState.Enabled = true;
                button_uartSend_485.Enabled = true;
                button_uartSend_232.Enabled = true;
                button_lightCtl.Enabled = true;
                button_syncTime.Enabled = true;
                button_getDevTime.Enabled = true;
            }
            else
            {
                button_login.Enabled = true;
                button_logout.Enabled = false;
                button_systemParam.Enabled = false;
                button_uartParam.Enabled = false;
                button_algoParam.Enabled = false;
                button_singleState.Enabled = false;
                button_allState.Enabled = false;
                button_uartSend_485.Enabled = false;
                button_uartSend_232.Enabled = false;
                button_lightCtl.Enabled = false;
                button_syncTime.Enabled = false;
                button_getDevTime.Enabled = false;
            }
        }

        private void listView_devInfo_MouseUp(object sender, MouseEventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count != 0)
            {
                int index = this.listView_devInfo.SelectedItems[0].Index;
                if ((index < MAX_CONNECT_NUM) && (IntPtr.Zero != pUid[index]))
                {
                    comboBox_spaceId.Items.Clear();
                    for (int i = 1; i <= nTotalSpaceNum[index]; i++)
                    {
                        comboBox_spaceId.Items.Add(i.ToString());
                        comboBox_spaceId.SelectedIndex = 0;
                    }
                    button_login.Enabled = false;
                    button_logout.Enabled = true;
                    button_systemParam.Enabled = true;
                    button_uartParam.Enabled = true;
                    button_algoParam.Enabled = true;
                    button_singleState.Enabled = true;
                    button_allState.Enabled = true;
                    button_uartSend_485.Enabled = true;
                    button_uartSend_232.Enabled = true;
                    button_lightCtl.Enabled = true;
                    button_syncTime.Enabled = true;
                    button_getDevTime.Enabled = true;
                    return;
                }
            }

            if (this.listView_devInfo.SelectedItems.Count == 0)
                textBox_IP.Text = "192.168.55.100";

            button_login.Enabled = true;
            button_logout.Enabled = false;
            button_systemParam.Enabled = false;
            button_uartParam.Enabled = false;
            button_algoParam.Enabled = false;
            button_singleState.Enabled = false;
            button_allState.Enabled = false;
            button_uartSend_485.Enabled = false;
            button_uartSend_232.Enabled = false;
            button_lightCtl.Enabled = false;
            button_syncTime.Enabled = false;
            button_getDevTime.Enabled = false;
        }

        private void button_systemParam_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            FormSystem form = new FormSystem();

            form.nSpaceNum = nTotalSpaceNum[index];
            for (uint i = 0; i < nTotalSpaceNum[index]; i++)
            {
                ipgsdk.ICE_IPCSDK_GetEnableParkingSpace(pUid[index], i, ref form.nSpaceEn[i]);
                ipgsdk.ICE_IPCSDK_GetParkingSpaceType(pUid[index], i, ref form.nSpaceType[i]);
            }

            StringBuilder strIp = new StringBuilder(20);
            uint nEnable = 0;
            uint tmp = 0;

            uint success = ipgsdk.ICE_IPCSDK_GetRemoteDevState(pUid[index], ref nEnable, strIp, ref tmp, ref tmp);
            if (1 == success)
            {
                form.strRemoteIp = strIp.ToString();
                form.nRemoteEn = nEnable;
            }

            success = ipgsdk.ICE_IPCSDK_GetControlDevState(pUid[index], ref nEnable, strIp, ref tmp, ref tmp);
            if (1 == success)
            {
                form.strControlIp = strIp.ToString();
                form.nControlEn = nEnable;
            }

            strIp = null;

            http_conf_t httpPram = new http_conf_t();
            ipgsdk.ICE_IPCSDK_GetCGIParam(pUid[index], ref httpPram);
            form.httpParam = httpPram;

            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            if (form.bSpaceChange)
            {
                for (uint i = 0; i < nTotalSpaceNum[index]; i++)
                {
                    ipgsdk.ICE_IPCSDK_SetEnableParkingSpace(pUid[index], i, form.nSpaceEn[i]);
                    ipgsdk.ICE_IPCSDK_SetParkingSpaceType(pUid[index], i, form.nSpaceType[i]);
                }
            }
            if (form.bControlChange)
            {
                success = ipgsdk.ICE_IPCSDK_SetRemoteDevState(pUid[index], form.nRemoteEn, form.strRemoteIp, 0, 0);
                success = ipgsdk.ICE_IPCSDK_SetControlDevState(pUid[index], form.nControlEn, form.strControlIp, 0, 0);
            }

            httpPram = form.httpParam;
            ipgsdk.ICE_IPCSDK_SetCGIParam(pUid[index], ref httpPram);
        }

        private void button_uartParam_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;
            ICE_UART_PARAM uart_param = new ICE_UART_PARAM();
            uint success = ipgsdk.ICE_IPCSDK_GetUARTCfg(pUid[index], ref uart_param);
            if (0 == success)
            {
                MessageBox.Show("获取串口参数失败");
                return;
            }

            FormUart form = new FormUart();
            form.baudrate = uart_param.uart_param[1].baudRate;
            form.databits = uart_param.uart_param[1].dataBits;
            form.parity   = uart_param.uart_param[1].parity;
            form.stopbits = uart_param.uart_param[1].stopBits;
            form.flowctrl = uart_param.uart_param[1].flowControl;
            form.uartEn = uart_param.uart_param[1].uartEn;

            form.baudrate2 = uart_param.uart_param[0].baudRate;
            form.databits2 = uart_param.uart_param[0].dataBits;
            form.parity2 = uart_param.uart_param[0].parity;
            form.stopbits2 = uart_param.uart_param[0].stopBits;
            form.flowctrl2 = uart_param.uart_param[0].flowControl;
            form.uartEn2 = uart_param.uart_param[0].uartEn;

            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            uart_param.uart_param[1].baudRate = form.baudrate;
            uart_param.uart_param[1].dataBits = form.databits;
            uart_param.uart_param[1].parity   = form.parity;
            uart_param.uart_param[1].stopBits = form.stopbits;
            uart_param.uart_param[1].flowControl = form.flowctrl;
            uart_param.uart_param[1].uartEn = form.uartEn;

            uart_param.uart_param[0].baudRate = form.baudrate2;
            uart_param.uart_param[0].dataBits = form.databits2;
            uart_param.uart_param[0].parity = form.parity2;
            uart_param.uart_param[0].stopBits = form.stopbits2;
            uart_param.uart_param[0].flowControl = form.flowctrl2;
            uart_param.uart_param[0].uartEn = form.uartEn2;

            success = ipgsdk.ICE_IPCSDK_SetUARTCfg(pUid[index], ref uart_param);
        }

        private void button_uartSend_485_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            FormTrans form = new FormTrans();
            form.m_hSDK = pUid[index];
            form.m_type = 0;

            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            //string strSendData = @"相机:" + this.listView_devInfo.SelectedItems[0].Text + @" send rs485 data to camera.";
            //发送RS232数据
            //ipgsdk.ICE_IPCSDK_TransSerialPort(pUid[index], strSendData, (UInt32)(strSendData.Length + 2));
        }

        private void button_uartSend_232_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            FormTrans form = new FormTrans();
            form.m_hSDK = pUid[index];
            form.m_type = 1;

            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            //string strSendData = @"相机:" + this.listView_devInfo.SelectedItems[0].Text + @" send rs232 data to camera.";
            //发送RS232数据
            //ipgsdk.ICE_IPCSDK_TransSerialPort_RS232(pUid[index], strSendData, (UInt32)(strSendData.Length + 2));
        }

        private void button_singleState_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            uint nSpaceNum = 0;
            byte[] pdata = new byte[1048676];
            uint nLen = 0;
            uint tmp = 0;
            ICE_PARKING_SPACE_OUTPUT_S stSingleStatus = new ICE_PARKING_SPACE_OUTPUT_S();
            uint success = ipgsdk.ICE_IPCSDK_GetSingleParkingSpaceStatus(pUid[index], (uint)comboBox_spaceId.SelectedIndex,
                ref nSpaceNum, ref stSingleStatus, pdata, 1048576, ref nLen, IntPtr.Zero, 0, ref tmp);
            if (1 == success)
            {
                nTotalNum++;
                DateTime dt = new DateTime();
                dt = DateTime.Now;
                ListViewItem lvItem = new ListViewItem();
                lvItem.Text = nTotalNum.ToString();
                lvItem.SubItems.Add(this.listView_devInfo.SelectedItems[0].Text);
                lvItem.SubItems.Add(dt.ToString("yyyy-MM-dd HH:mm:ss"));
                lvItem.SubItems.Add((comboBox_spaceId.SelectedIndex + 1).ToString());
                if ((stSingleStatus.enParkingPlaceStatus >= 0) && (stSingleStatus.enParkingPlaceStatus <= 8))
                {
                    string strSpaceStatus = getSpaceStatus(stSingleStatus.enParkingPlaceStatus);
                    lvItem.SubItems.Add(strSpaceStatus);
                }
                lvItem.SubItems.Add(stSingleStatus.stPlateInfo.as8PlateNum);
                if ((stSingleStatus.stPlateInfo.ePlateColor >= 0) && (stSingleStatus.stPlateInfo.ePlateColor < 7))
                    lvItem.SubItems.Add(strPlateColor[stSingleStatus.stPlateInfo.ePlateColor]);
                if ((stSingleStatus.s32CarType >= 0) && (stSingleStatus.s32CarType < 3))
                    lvItem.SubItems.Add(strCarType[stSingleStatus.s32CarType]);
                if ((stSingleStatus.s32EventType < 3) && (stSingleStatus.s32EventType >= 0))
                    lvItem.SubItems.Add(strEventType[stSingleStatus.s32EventType]);
                this.listView_spaceInfo.Items.Insert(0, lvItem);

                if ((nLen > 0) && (nLen < 1048576))
                {
                    byte[] dataJpg = new byte[nLen];
                    Array.Copy(pdata, dataJpg, nLen);
                    savePic(dataJpg, this.listView_devInfo.SelectedItems[0].Text);
                }
            }
        }

        private void button_allState_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            byte[] pdata = new byte[1048676];
            uint nLen = 0;
            uint tmp = 0;
            ICE_PARKING_SPACE_RESULT_S stSpaceStatus = new ICE_PARKING_SPACE_RESULT_S();
            uint success = ipgsdk.ICE_IPCSDK_GetAllParkingSpaceStatus(pUid[index], ref stSpaceStatus, pdata, 1048576, ref nLen,
                                                                        IntPtr.Zero, ref tmp);
            if (1 == success)
            {
                DateTime dt = new DateTime();
                dt = DateTime.Now;

                byte[] dataJpg = null;
                if ((nLen > 0) && (nLen < 1048576))
                {
                    dataJpg = new byte[nLen];
                    Array.Copy(pdata, dataJpg, nLen);
                }

                for (int i = 0; i < stSpaceStatus.u8ParkingPlaceNum; i++)
                {
                    nTotalNum++;                    
                    ListViewItem lvItem = new ListViewItem();
                    lvItem.Text = nTotalNum.ToString();
                    lvItem.SubItems.Add((this.listView_devInfo.SelectedItems[0]).Text);
                    lvItem.SubItems.Add(dt.ToString("yyyy-MM-dd HH:mm:ss"));
                    lvItem.SubItems.Add((i + 1).ToString());
                    if ((stSpaceStatus.astOutput[i].enParkingPlaceStatus >= 0) && (stSpaceStatus.astOutput[i].enParkingPlaceStatus <= 8))
                    {
                        string strSpaceStatus = getSpaceStatus(stSpaceStatus.astOutput[i].enParkingPlaceStatus);
                        lvItem.SubItems.Add(strSpaceStatus);
                    }
                    lvItem.SubItems.Add(stSpaceStatus.astOutput[i].stPlateInfo.as8PlateNum);
                    if ((stSpaceStatus.astOutput[i].stPlateInfo.ePlateColor >= 0) && (stSpaceStatus.astOutput[i].stPlateInfo.ePlateColor < 7))
                        lvItem.SubItems.Add(strPlateColor[stSpaceStatus.astOutput[i].stPlateInfo.ePlateColor]);
                    if ((stSpaceStatus.astOutput[i].s32CarType >= 0) && (stSpaceStatus.astOutput[i].s32CarType < 3))
                        lvItem.SubItems.Add(strCarType[stSpaceStatus.astOutput[i].s32CarType]);
                    if ((stSpaceStatus.astOutput[i].s32EventType < 3) && (stSpaceStatus.astOutput[i].s32EventType >= 0))
                        lvItem.SubItems.Add(strEventType[stSpaceStatus.astOutput[i].s32EventType]);
                    this.listView_spaceInfo.Items.Insert(0, lvItem);
                }

                if ((nLen > 0) && (nLen < 1048576))
                {
                    savePic(dataJpg, this.listView_devInfo.SelectedItems[0].Text);
                }
                
            }
        }

        private void SettingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormLocalSetting form = new FormLocalSetting();
            form.strStorePath = strStorePath;
            if (form.ShowDialog() == DialogResult.OK)
            {
                strStorePath = form.strStorePath;
            }
        }

        private void button_algoParam_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            FormAlgo form = new FormAlgo();
            string strText = "";

            if (2 == nTotalSpaceNum[index])
            {
                form.nWidth = 1280;
                form.nHeight = 720;
            }
            else if (3 == nTotalSpaceNum[index])
            {
                form.nWidth = 1920;
                form.nHeight = 1080;
            }

            ICE_IPG_PLACE_CONFIG_S stPlaceCfg = new ICE_IPG_PLACE_CONFIG_S();
            uint success = ipgsdk.ICE_IPCSDK_GetAllParkingSpaceLoops(pUid[index], ref stPlaceCfg, form.nWidth, form.nHeight);
            if (1 == success)
            {
                form.nSpaceNum = stPlaceCfg.u8ParkingPlaceNum;
                form.bSpecial = Convert.ToBoolean(stPlaceCfg.bSpecialPlace);
                for (int i = 0; i < stPlaceCfg.u8ParkingPlaceNum; i++)
                {
                    form.nLeftx[i] = stPlaceCfg.stPlaceParam[i].stRecRect.s16Left;
                    form.nLefty[i] = stPlaceCfg.stPlaceParam[i].stRecRect.s16Bottom;
                    form.nRightx[i] = stPlaceCfg.stPlaceParam[i].stRecRect.s16Right;
                    form.nRighty[i] = stPlaceCfg.stPlaceParam[i].stRecRect.s16Top;
                }
                strText = "相机" + (index+1).ToString() + "获取识别区域成功";
                listBoxInfo.Items.Insert(0, strText);
            }
            else
            {
                strText = "相机" + (index+1).ToString() + "获取识别区域失败";
                listBoxInfo.Items.Insert(0, strText);
            }

            if (form.ShowDialog() == DialogResult.OK)
            {
                stPlaceCfg.bSpecialPlace = Convert.ToInt32(form.bSpecial);

                for (int i = 0; i < stPlaceCfg.u8ParkingPlaceNum; i++)
                {
                    stPlaceCfg.stPlaceParam[i].stRecRect.s16Left = form.nLeftx[i];
                    stPlaceCfg.stPlaceParam[i].stRecRect.s16Bottom = form.nLefty[i];
                    stPlaceCfg.stPlaceParam[i].stRecRect.s16Right = form.nRightx[i];
                    stPlaceCfg.stPlaceParam[i].stRecRect.s16Top = form.nRighty[i];   
                }
                success = ipgsdk.ICE_IPCSDK_SetAllParkingSpaceLoops(pUid[index], ref stPlaceCfg, form.nWidth, form.nHeight);
                if (1 == success)
                    listBoxInfo.Items.Insert(0, "设置识别区域成功");
                else
                    listBoxInfo.Items.Insert(0, "设置识别区域失败");
            }
        }

        private void DevSearchToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormIPSearch form = new FormIPSearch();
            form.ShowDialog();
        }

        private void button_lightCtl_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;
            string strText;
            LightCtlParam param = new LightCtlParam();
            uint success = ipgsdk.ICE_IPCSDK_GetLightCtlParam(pUid[index], ref param);
            if (1 == success)
            {
                strText = "相机" + (index + 1).ToString() + "获取强制控灯参数成功";
                listBoxInfo.Items.Insert(0, strText);
            }
            else
            {
                strText = "相机" + (index + 1).ToString() + "获取强制控灯参数失败";
                listBoxInfo.Items.Insert(0, strText);
                return;
            }

            
            FormLightCtrl form = new FormLightCtrl();

            form.nStyle = param.u8LightEn;
            form.nColor = param.u8Color;
            if (form.ShowDialog() == DialogResult.Cancel)
                return;

            param.u8LightEn = Convert.ToByte(form.nStyle);
            param.u8Color = Convert.ToByte(form.nColor);
            success = ipgsdk.ICE_IPCSDK_SetLightCtlParam(pUid[index], ref param);
            if (1 == success)
            {
                strText = "相机" + (index + 1).ToString() + "设置强制控灯参数成功";
                listBoxInfo.Items.Insert(0, strText);
            }
            else
            {
                strText = "相机" + (index + 1).ToString() + "设置强制控灯参数失败";
                listBoxInfo.Items.Insert(0, strText);
            }
        }

        private void button_syncTime_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;

            uint success = ipgsdk.ICE_IPCSDK_SyncTime(pUid[0], (UInt16)DateTime.Now.Year, (byte)DateTime.Now.Month,
                (byte)DateTime.Now.Day, (byte)DateTime.Now.Hour, (byte)DateTime.Now.Minute, (byte)DateTime.Now.Second);

            string strText;
            if (1 == success)
            {
                strText = "相机" + (index + 1).ToString() + "同步时间成功";
                listBoxInfo.Items.Insert(0, strText);
            }
            else
            {
                strText = "相机" + (index + 1).ToString() + "同步时间失败";
                listBoxInfo.Items.Insert(0, strText);
            }
        }

        private void button_getDevTime_Click(object sender, EventArgs e)
        {
            if (this.listView_devInfo.SelectedItems.Count == 0)
                return;
            int index = this.listView_devInfo.SelectedItems[0].Index;
            if ((index >= MAX_CONNECT_NUM) || (IntPtr.Zero == pUid[index]))
                return;
            UInt16 year = 0;
            byte month = 0, day = 0, hour = 0, minute = 0, second = 0;

            uint success = ipgsdk.ICE_IPCSDK_GetDevTime(pUid[0], ref year, ref month, ref day, ref hour, ref minute, ref second);

            string strText;
            if (1 == success)
            {
                strText = "相机" + (index + 1).ToString() + "时间:" + year.ToString("0000") + "-" + month.ToString("00") + "-" + 
                    day.ToString("00") + " " + hour.ToString("00") + ":" + minute.ToString("00") + ":" + second.ToString("00");
                listBoxInfo.Items.Insert(0, strText);
            }
            else
            {
                strText = "相机" + (index + 1).ToString() + "获取相机时间失败";
                listBoxInfo.Items.Insert(0, strText);
            }
        }
    }
}
