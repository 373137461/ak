unit UintSystemCfg;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ipgsdk;

const
   MAX_CONNECT_NUM= 4;
type
  TSystemCfg = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    ComboBox_SpaceNum: TComboBox;
    RadioGroup_Enable: TRadioGroup;
    RadioGroup_Type: TRadioGroup;
    GroupBox2: TGroupBox;
    Label4: TLabel;
    CheckBox_Remote: TCheckBox;
    Label5: TLabel;
    Edit_RemoteIP: TEdit;
    Label6: TLabel;
    CheckBox_Control: TCheckBox;
    Label7: TLabel;
    Edit_ControlIP: TEdit;
    Button_OK: TButton;
    Button_Cancle: TButton;
    GroupBox3: TGroupBox;
    CheckBox_httpEnable: TCheckBox;
    Label8: TLabel;
    Edit_httpAddr: TEdit;
    CheckBox_smallPic: TCheckBox;
    CheckBox_bigPic: TCheckBox;
    CheckBox_uploadEnable: TCheckBox;
    Label9: TLabel;
    CheckBox_heartbeatEnable: TCheckBox;
    Label10: TLabel;
    Edit_uploadInterval: TEdit;
    Edit_heartbeatInterval: TEdit;
    procedure Button_CancleClick(Sender: TObject);
    procedure Button_OKClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ComboBox_SpaceNumChange(Sender: TObject);
    procedure Edit_uploadIntervalKeyPress(Sender: TObject; var Key: Char);
    procedure Edit_heartbeatIntervalChange(Sender: TObject);
    procedure Edit_uploadIntervalChange(Sender: TObject);
    procedure Edit_heartbeatIntervalKeyPress(Sender: TObject;
      var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure setValue(totalNum: Integer; spaceEn: array of Integer; spaceType: array of Integer;
                        remoteIp: String; remoteEn: Integer; controlIp: String; controlEn: Integer;
                        httpParam: http_conf_t);
    procedure getValue(var spaceEn: array of Integer; var spaceType: array of Integer;
                        var remoteIp: PChar; var remoteEn: Integer; var controlIp: PChar; var controlEn: Integer;
                        var httpParam: http_conf_t);
  end;

var
  SystemCfg: TSystemCfg;
  nSpaceNum: Integer;
  nSpaceEn: array[0..(MAX_CONNECT_NUM-1)] of Integer;
  nSpaceType: array[0..(MAX_CONNECT_NUM-1)] of Integer;
  strRemoteIP, strControlIP: String;
  nRemoteEnable, nControlEnable: Integer;
  nSpaceCode: Integer;
  stHttpParam: http_conf_t;

implementation

{$R *.dfm}

procedure TSystemCfg.Button_CancleClick(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

procedure TSystemCfg.Button_OKClick(Sender: TObject);
begin
  nSpaceCode := ComboBox_SpaceNum.ItemIndex;
  nSpaceEn[nSpaceCode] := RadioGroup_Enable.ItemIndex;
  nSpaceType[nSpaceCode] := RadioGroup_Type.ItemIndex;

  if CheckBox_Remote.Checked then
  begin
    nRemoteEnable := 1;
  end
  else begin
    nRemoteEnable := 0;
  end;

  if CheckBox_Control.Checked then
  begin
    nControlEnable := 1;
  end
  else begin
    nControlEnable := 0;
  end;

  strRemoteIP := Edit_RemoteIP.Text;
  strControlIP := Edit_ControlIP.Text;

  if length(Edit_heartbeatInterval.Text) = 0 then
  begin
    showmessage('请输入一个整数');
    exit;
  end;
  if length(Edit_uploadInterval.Text) = 0 then
  begin
    showmessage('请输入一个整数');
    exit;
  end;

  FillChar(stHttpParam, SizeOf(http_conf_t), 0);

  if CheckBox_httpEnable.Checked then
  begin
    stHttpParam.http_enable := 1;
  end
  else begin
    stHttpParam.http_enable := 0;
  end;

  CopyMemory(@stHttpParam.http_Addr[0], PChar(Edit_httpAddr.Text), length(Edit_httpAddr.Text));

  if CheckBox_smallPic.Checked then
  begin
    stHttpParam.small_pic := 1;
  end
  else begin
     stHttpParam.small_pic := 0;
  end;

  if CheckBox_bigPic.Checked then
  begin
    stHttpParam.big_pic := 1;
  end
  else begin
    stHttpParam.big_pic := 0;
  end;

  if CheckBox_uploadEnable.Checked then
  begin
    stHttpParam.upload_enable := 1;
  end
  else begin
    stHttpParam.upload_enable := 0;
  end;

    stHttpParam.upload_interval := StrToInt(Edit_uploadInterval.Text);

  if CheckBox_heartbeatEnable.Checked then
  begin
    stHttpParam.heartbeat_enable := 1;
  end
  else begin
    stHttpParam.heartbeat_enable := 0;
  end;

  stHttpParam.heartbeat_interval := StrToInt(Edit_heartbeatInterval.Text);
  self.ModalResult := mrOk;
end;

procedure TSystemCfg.setValue(totalNum: Integer; spaceEn: array of Integer; spaceType:array of Integer;
                              remoteIp: String; remoteEn: Integer; controlIp: String; controlEn: Integer;
                              httpParam: http_conf_t);
begin
  nSpaceNum := totalNum;
  strRemoteIP := remoteIp;
  strControlIP := controlIp;
  nRemoteEnable := remoteEn;
  nControlEnable := controlEn;
  Move(spaceEn, nSpaceEn, MAX_CONNECT_NUM*sizeof(Integer));
  Move(spaceType, nSpaceType, MAX_CONNECT_NUM*sizeof(Integer));
  stHttpParam := httpParam;
end;

procedure TSystemCfg.FormShow(Sender: TObject);
var
  i: Integer;
begin
  comboBox_SpaceNum.Items.Clear;
  for i := 1 to nSpaceNum do
  begin
  comboBox_SpaceNum.Items.Add(IntToStr(i));
  end;
  comboBox_SpaceNum.ItemIndex := 0;
  nSpaceCode := 0;

  RadioGroup_Enable.ItemIndex :=  nSpaceEn[0];
  RadioGroup_Type.ItemIndex := nSpaceType[0];

  if nRemoteEnable = 1 then
  begin
    CheckBox_Remote.Checked := true;
  end
  else begin
    CheckBox_Remote.Checked := false;
  end;

  if nControlEnable = 1 then
  begin
    CheckBox_Control.Checked := true;
  end
  else begin
    CheckBox_Control.Checked := false;
  end;

   Edit_RemoteIP.Text := strRemoteIP;
   Edit_ControlIP.Text := strControlIP;

   if stHttpParam.http_enable = 1 then
   begin
    CheckBox_httpEnable.Checked := true;
   end
   else begin
    CheckBox_httpEnable.Checked := false;
   end;

    Edit_httpAddr.Text := strPas(@stHttpParam.http_addr);

   if stHttpParam.small_pic = 1 then
   begin
    CheckBox_smallPic.Checked := true;
   end
   else begin
    CheckBox_smallPic.Checked := false;
   end;

   if stHttpParam.big_pic = 1 then
   begin
    CheckBox_bigPic.Checked := true;
   end
   else begin
    CheckBox_bigPic.Checked := false;
   end;

   if stHttpParam.upload_enable = 1 then
   begin
    CheckBox_uploadEnable.Checked := true;
   end
   else begin
   CheckBox_uploadEnable.Checked := false;
   end;

    Edit_uploadInterval.Text := intToStr(stHttpParam.upload_interval);

   if stHttpParam.heartbeat_enable = 1 then
   begin
   CheckBox_heartbeatEnable.Checked := true;
   end
   else begin
    CheckBox_heartbeatEnable.Checked := false;
   end;

   Edit_heartbeatInterval.Text := intToStr(stHttpParam.heartbeat_interval);
end;

procedure TSystemCfg.FormCreate(Sender: TObject);
begin
  RadioGroup_Enable.Items.Add('禁用');
  RadioGroup_Enable.Items.Add('使能');

  RadioGroup_Type.Items.Add('临时');
  RadioGroup_Type.Items.Add('预定');
  RadioGroup_Type.Items.Add('固定');
end;

procedure TSystemCfg.ComboBox_SpaceNumChange(Sender: TObject);
begin
  nSpaceEn[nSpaceCode] := RadioGroup_Enable.ItemIndex;
  nSpaceType[nSpaceCode] := RadioGroup_Type.ItemIndex;

  nSpaceCode := ComboBox_SpaceNum.ItemIndex;
  RadioGroup_Enable.ItemIndex :=  nSpaceEn[nSpaceCode];
  RadioGroup_Type.ItemIndex := nSpaceType[nSpaceCode];
end;

 procedure TSystemCfg.getValue(var spaceEn: array of Integer; var spaceType: array of Integer;
                        var remoteIp: PChar; var remoteEn: Integer; var controlIp: PChar;
                        var controlEn: Integer; var httpParam: http_conf_t);
begin
  remoteIp := PChar(strRemoteIP);
  controlIp := PChar(strControlIP);
  remoteEn := nRemoteEnable;
  controlEn := nControlEnable;
  Move(nSpaceEn, spaceEn, MAX_CONNECT_NUM*sizeof(Integer));
  Move(nSpaceType, spaceType, MAX_CONNECT_NUM*sizeof(Integer));
  httpParam := stHttpParam;
end;
procedure TSystemCfg.Edit_uploadIntervalKeyPress(Sender: TObject;
  var Key: Char);
begin
  if not (key in ['0'..'9', #8]) then
    key := #0;
end;

procedure TSystemCfg.Edit_heartbeatIntervalChange(Sender: TObject);
begin
  if length(Edit_heartbeatInterval.Text) = 0 then
    exit;

  if StrToInt(Edit_heartbeatInterval.Text) > 60 then
  begin
     Edit_heartbeatInterval.Text := '60';
  end
  else if StrToInt(Edit_heartbeatInterval.Text) < 1 then
  begin
    Edit_heartbeatInterval.Text := '1';
  end;
end;

procedure TSystemCfg.Edit_uploadIntervalChange(Sender: TObject);
begin
  if length(Edit_uploadInterval.Text) = 0 then
    exit;

  if StrToInt(Edit_uploadInterval.Text) > 60 then
  begin
     Edit_uploadInterval.Text := '60';
  end
  else if StrToInt(Edit_uploadInterval.Text) < 1 then
  begin
    Edit_uploadInterval.Text := '1';
  end;
end;

procedure TSystemCfg.Edit_heartbeatIntervalKeyPress(Sender: TObject;
  var Key: Char);
begin
   if not (key in ['0'..'9', #8]) then
    key := #0;
end;

end.
