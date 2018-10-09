unit UartSet;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ipgsdk, ExtCtrls;

type
  TFormUartSet = class(TForm)
    ButtonCancle: TButton;
    ButtonOk: TButton;
    GroupBox1: TGroupBox;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label2: TLabel;
    CheckBoxEnable: TCheckBox;
    ComboBoxBaudrate: TComboBox;
    ComboBoxDataBits: TComboBox;
    ComboBoxParity: TComboBox;
    ComboBoxStopBits: TComboBox;
    ComboBoxFlowCtrl: TComboBox;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    CheckBoxEnable2: TCheckBox;
    ComboBoxBaudrate2: TComboBox;
    ComboBoxDataBits2: TComboBox;
    ComboBoxParity2: TComboBox;
    ComboBoxStopBits2: TComboBox;
    ComboBoxFlowCtrl2: TComboBox;
    procedure ButtonOkClick(Sender: TObject);
    procedure ButtonCancleClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ComboBoxUartOnChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure setValue(param: ICE_UART_PARAM);
    function getValue():ICE_UART_PARAM;
    procedure showDlg();
    procedure updateUartParam();
  end;

var
  FormUartSet: TFormUartSet;
  uartParam: ICE_UART_PARAM;

implementation

{$R *.dfm}

procedure TFormUartSet.ButtonOkClick(Sender: TObject);
begin
  updateUartParam();
  self.ModalResult := mrOk;
end;

procedure TFormUartSet.ButtonCancleClick(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

procedure TFormUartSet.setValue(param: ICE_UART_PARAM);
begin
  uartParam := param;
end;

procedure TFormUartSet.FormShow(Sender: TObject);
begin
  showDlg();
end;

function TFormUartSet.getValue():ICE_UART_PARAM;
begin
result := uartParam;
end;

procedure TFormUartSet.FormCreate(Sender: TObject);
begin
  ComboBoxBaudrate.Items.Add('1200');
  ComboBoxBaudrate.Items.Add('2400');
  ComboBoxBaudrate.Items.Add('4800');
  ComboBoxBaudrate.Items.Add('9600');
  ComboBoxBaudrate.Items.Add('19200');
  ComboBoxBaudrate.Items.Add('38400');
  ComboBoxBaudrate.Items.Add('115200');

  ComboBoxBaudrate2.Items.Add('1200');
  ComboBoxBaudrate2.Items.Add('2400');
  ComboBoxBaudrate2.Items.Add('4800');
  ComboBoxBaudrate2.Items.Add('9600');
  ComboBoxBaudrate2.Items.Add('19200');
  ComboBoxBaudrate2.Items.Add('38400');
  ComboBoxBaudrate2.Items.Add('115200');

  ComboBoxDataBits.Items.Add('5');
  ComboBoxDataBits.Items.Add('6');
  ComboBoxDataBits.Items.Add('7');
  ComboBoxDataBits.Items.Add('8');

  ComboBoxDataBits2.Items.Add('5');
  ComboBoxDataBits2.Items.Add('6');
  ComboBoxDataBits2.Items.Add('7');
  ComboBoxDataBits2.Items.Add('8');

  ComboBoxParity.Items.Add('无');
  ComboBoxParity.Items.Add('奇校验');
  ComboBoxParity.Items.Add('偶校验');
  ComboBoxParity.Items.Add('标记');
  ComboBoxParity.Items.Add('空格');

  ComboBoxParity2.Items.Add('无');
  ComboBoxParity2.Items.Add('奇校验');
  ComboBoxParity2.Items.Add('偶校验');
  ComboBoxParity2.Items.Add('标记');
  ComboBoxParity2.Items.Add('空格');

  ComboBoxStopBits.Items.Add('1');
  ComboBoxStopBits.Items.Add('2');

  ComboBoxStopBits2.Items.Add('1');
  ComboBoxStopBits2.Items.Add('2');

  ComboBoxFlowCtrl.Items.Add('无');
  ComboBoxFlowCtrl.Items.Add('硬件');
  ComboBoxFlowCtrl.Items.Add('Xon');
  ComboBoxFlowCtrl.Items.Add('Xoff');

  ComboBoxFlowCtrl2.Items.Add('无');
  ComboBoxFlowCtrl2.Items.Add('硬件');
  ComboBoxFlowCtrl2.Items.Add('Xon');
  ComboBoxFlowCtrl2.Items.Add('Xoff');
end;

procedure TFormUartSet.ComboBoxUartOnChange(Sender: TObject);
begin
  updateUartParam();
  showDlg();
end;


procedure TFormUartSet.showDlg();
begin
  if uartParam.uart_param[0].uartEn = 1 then
  begin
    checkBoxEnable2.Checked := true;
  end
  else
  begin
    checkBoxEnable2.Checked := false;
  end;
  ComboBoxBaudrate2.ItemIndex := uartParam.uart_param[0].baudRate;
  ComboBoxDataBits2.ItemIndex :=  uartParam.uart_param[0].dataBits;
  ComboBoxParity2.ItemIndex   := uartParam.uart_param[0].parity;
  ComboBoxStopBits2.ItemIndex :=  uartParam.uart_param[0].stopBits;
  ComboBoxFlowCtrl2.ItemIndex :=  uartParam.uart_param[0].flowControl;

  if uartParam.uart_param[1].uartEn = 1 then
  begin
    checkBoxEnable.Checked := true;
  end
  else
  begin
    checkBoxEnable.Checked := false;
  end;
  ComboBoxBaudrate.ItemIndex := uartParam.uart_param[1].baudRate;
  ComboBoxDataBits.ItemIndex :=  uartParam.uart_param[1].dataBits;
  ComboBoxParity.ItemIndex   := uartParam.uart_param[1].parity;
  ComboBoxStopBits.ItemIndex :=  uartParam.uart_param[1].stopBits;
  ComboBoxFlowCtrl.ItemIndex :=  uartParam.uart_param[1].flowControl;
end;

procedure TFormUartSet.updateUartParam();
begin
  if checkBoxEnable2.Checked then
  begin
    uartParam.uart_param[0].uartEn := 1;
  end
  else
  begin
    uartParam.uart_param[0].uartEn := 0;
  end;
    uartParam.uart_param[0].baudRate     := ComboBoxBaudrate2.ItemIndex;
    uartParam.uart_param[0].dataBits     := ComboBoxDataBits2.ItemIndex;
    uartParam.uart_param[0].parity       := ComboBoxParity2.ItemIndex;
    uartParam.uart_param[0].stopBits     := ComboBoxStopBits2.ItemIndex;
    uartParam.uart_param[0].flowControl  := ComboBoxFlowCtrl2.ItemIndex ;

  if checkBoxEnable.Checked then
  begin
    uartParam.uart_param[1].uartEn := 1;
  end
  else
  begin
    uartParam.uart_param[1].uartEn := 0;
  end;
    uartParam.uart_param[1].baudRate     := ComboBoxBaudrate.ItemIndex;
    uartParam.uart_param[1].dataBits     := ComboBoxDataBits.ItemIndex;
    uartParam.uart_param[1].parity       := ComboBoxParity.ItemIndex;
    uartParam.uart_param[1].stopBits     := ComboBoxStopBits.ItemIndex;
    uartParam.uart_param[1].flowControl  := ComboBoxFlowCtrl.ItemIndex ;
end;

end.
