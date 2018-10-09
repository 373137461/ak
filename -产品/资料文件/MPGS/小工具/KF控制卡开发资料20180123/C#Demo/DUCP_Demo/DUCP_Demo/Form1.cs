using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Net;
using System.Net.Sockets;

namespace DUCP_Demo
{
    public partial class Form1 : Form
    {
        /*定义网络环境变量 默认IP为192.168.0.10，端口为7*/
        public static UdpClient DUCP_NetSocket;
        public static IPAddress DeviceIP = IPAddress.Parse("192.168.1.10");
        public static IPEndPoint RPoint = new IPEndPoint(DeviceIP, 7);
        public static IPEndPoint TPoint = new IPEndPoint(DeviceIP, 7);

        /*
            #0.实现协议栈数据输出回调函数
        */
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        unsafe public delegate byte cbDUCP_DataOutType(byte* Data, int Size);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static void MB_STK_SetOutCallback(cbDUCP_DataOutType cb);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        unsafe extern static sbyte MB_STK_In(byte* Data, int Size);
        unsafe static byte cbDUCP_DataOut(byte* Data, int Size)
        {
            sbyte Ret;
            byte[] buff = new byte[256];
            byte[] RxBuff = new byte[256];
            for (int i = 0; i < Size; i++)
            {
                buff[i] = Data[i];
            }

            /*发送数据到显示屏*/
            DUCP_NetSocket.Send(buff, Size, TPoint);

            /*接收显示屏回复的数据*/
            RxBuff = DUCP_NetSocket.Receive(ref RPoint); 

            /*将显示屏的回复的数据传输给协议栈*/
            unsafe
            {
                fixed (byte* pArray = RxBuff)
                Ret = MB_STK_In(pArray, RxBuff.Length);
            }
            return (byte)Ret;
        }

        public Form1()
        {
            InitializeComponent();

            /*#1.设置协议栈的回调函数*/
            unsafe
            {
                MB_STK_SetOutCallback(cbDUCP_DataOut);
            }
            /*#2.创建UDP网络套接字*/
            DUCP_NetSocket = new UdpClient();

            TextBox.Text = "欢迎光临";
            TextBox_WID.Text = "0";
        }




        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        unsafe extern static byte DUCP_HOST_TTS_Play(byte* pText, byte Opt);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        unsafe extern static byte DUCP_HOST_TWIN_DisText(	int WinID,
                                                            byte* pText,
									                        int EnterMode,
									                        int EnterSpeed,
									                        int DelayMode,
									                        int DelayTime,
									                        int EixtMode,
									                        int EixtSpeed,
									                        int FontIndex,
									                        int TextColor,
									                        int BkColor,
									                        int DisTimes);
        private void DISTEXT_Click(object sender, EventArgs e)
        {

            unsafe
            {
                byte[] Buff = System.Text.Encoding.Default.GetBytes(TextBox.Text);
                //byte[] Str = new byte[Buff.Length + 1];
                int WID;
                //int i;
                //for(i = 0;i < Buff.Length;i ++) {
                //    Str[i] = Buff[i];
                //}
                //Str[i] = 0;
                int.TryParse(TextBox_WID.Text, out WID);
                fixed (byte* pArray = Buff)
                DUCP_HOST_TWIN_DisText(WID, pArray, 0X15, 1, 0X00, 2, 0X15, 1, 3, 0XFF, 0X00, 0);
            }
        }

        private void 播放语音_Click(object sender, EventArgs e)
        {
            unsafe
            {
                byte[] Buff = System.Text.Encoding.Default.GetBytes(TextBox.Text);
                fixed (byte* pArray = Buff)
                DUCP_HOST_TTS_Play(pArray, 0x01);

                DUCP_HOST_SYS_SetOutState(0, 1);
                 
                DUCP_HOST_SYS_SetOutState(0, 0);
            }
        }

        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_SYS_SetOutState(int io, int OnOff);

        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_TWIN_Create(int WinID, int Stile, int x0, int y0, int xSize, int ySize);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_TWIN_DelFile(int WinID, int FileID);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_TWIN_Del(int WinID);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_PIC_Del(int WinID);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_2D_SetColor(int Color);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_2D_FillRect(int x0, int y0, int x1, int y1);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_2D_DrawSysIcon(int x0, int y0, int Num, int Denom, int IconIndex);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_PIC_Create(int WinID,int x0, int y0, int xSize, int ySize);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static byte DUCP_HOST_PIC_Add(int WinID, int FID, byte EnterMode, byte EnterSpeed,
                                            byte StopMode, byte StopTime, byte ExitMode, byte ExitSpeed);
        [DllImport("DUCP.dll", CallingConvention = CallingConvention.Cdecl)]
        unsafe extern static byte DUCP_HOST_TWIN_DownTextFile(	int WinID,
										                        int FileID,
										                        byte * pText,
										                        int EnterMode,
										                        int EnterSpeed,
										                        int DelayMode,
										                        int DelayTime,
										                        int EixtMode,
										                        int EixtSpeed,
										                        int FontIndex,
										                        int TextColor,
										                        int BkColor);
        private void BUTTON_DEMO1_Click(object sender, EventArgs e)
        {
	        DUCP_HOST_TWIN_Create(0,0,0,0,64,16);
	        DUCP_HOST_TWIN_Create(1, 0, 0, 16, 64, 16);
	        DUCP_HOST_TWIN_Create(2, 0, 0, 32, 64, 16);
	        DUCP_HOST_TWIN_Create(3, 0, 0, 48, 64, 16);
	        DUCP_HOST_TWIN_Create(4, 0, 0, 64, 64, 16);
	        DUCP_HOST_TWIN_Create(5, 0, 0, 80, 64, 16);
	        DUCP_HOST_TWIN_Create(6, 0, 0, 96, 64, 16);
	        DUCP_HOST_TWIN_Create(7, 0, 0, 112, 64, 16);

            unsafe
            {
                byte[] Buff = System.Text.Encoding.Default.GetBytes("现在时间`C`Y年`M月`D日 星期`V `H:`N:`S");
                fixed (byte* pArray = Buff)
	            DUCP_HOST_TWIN_DownTextFile(0,
								            0,
								            pArray,
								            0X15,
								            1,
								            0X00,
								            2,
								            0X15,
								            1,
								            3,
								            0XFF,
								            0);
                byte[] Buff2 = System.Text.Encoding.Default.GetBytes("欢迎使用");
                fixed (byte* pArray = Buff)
	            for (int i = 1; i < 8; i++) {
		            DUCP_HOST_TWIN_DownTextFile(i,
									            0,
									            pArray,
									            0X15,
									            1,
									            0X00,
									            2,
									            0X15,
									            1,
									            3,
									            0XFF,
									            0);
	            }
            }
        }

        private void BUTTON_DEMO2_Click(object sender, EventArgs e)
        {
            // TODO:  在此添加控件通知处理程序代码
            DUCP_HOST_TWIN_Del(0);
            DUCP_HOST_TWIN_Del(1);
            DUCP_HOST_PIC_Del(4);
            DUCP_HOST_PIC_Del(5);

            DUCP_HOST_2D_SetColor(0);
            DUCP_HOST_2D_FillRect(0, 0, 63, 31);
            DUCP_HOST_2D_DrawSysIcon(-7, 0, 1, 3, 43);

            DUCP_HOST_PIC_Create(4, 24, 16, 48, 16);
            DUCP_HOST_PIC_Add(4, 45, 1, 2, 0, 0, 6, 6);

            DUCP_HOST_TWIN_Create(0, 0, 19, 0, 48, 8);
            DUCP_HOST_TWIN_Create(1, 0, 17, 8, 48, 8);

            unsafe
            {
                byte[] Buff = System.Text.Encoding.Default.GetBytes("`H:`N:`S");
                fixed (byte* pArray = Buff)
                    DUCP_HOST_TWIN_DisText(0,
                                            pArray,
                                            0X00,
                                            1,
                                            0X08,
                                            255,
                                            0x00,
                                            1,
                                            0,
                                            0XFF,
                                            0, 0);
                byte[] Buff2 = System.Text.Encoding.Default.GetBytes("`D-`M-`Y");
                fixed (byte* pArray = Buff2)
                    DUCP_HOST_TWIN_DisText(1,
                                            pArray,
                                            0X00,
                                            1,
                                            0X08,
                                            255,
                                            0x00,
                                            1,
                                            0,
                                            0XFF,
                                            0, 0);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DUCP_HOST_SYS_SetOutState(0, 1);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            DUCP_HOST_SYS_SetOutState(0, 0);
        }
    }
}
