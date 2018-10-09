unit UnitAlgoCfg;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ipgsdk;

type
  TFormAlgoCfg = class(TForm)
    CheckBox_Define: TCheckBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    ComboBox_SettingPPI: TComboBox;
    ComboBox_SpaceNum: TComboBox;
    Edit_LeftX: TEdit;
    Edit_TopY: TEdit;
    Edit_RightX: TEdit;
    Edit_BottomY: TEdit;
    Button_OK: TButton;
    Button_Cancle: TButton;
    procedure Button_OKClick(Sender: TObject);
    procedure Button_CancleClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ComboBox_SettingPPIChange(Sender: TObject);
    procedure ComboBox_SpaceNumChange(Sender: TObject);
    procedure Edit_LeftXKeyPress(Sender: TObject; var Key: Char);
    procedure Edit_TopYKeyPress(Sender: TObject; var Key: Char);
    procedure Edit_RightXKeyPress(Sender: TObject; var Key: Char);
    procedure Edit_BottomYKeyPress(Sender: TObject; var Key: Char);
    procedure Edit_LeftXChange(Sender: TObject);
    procedure Edit_TopYChange(Sender: TObject);
    procedure Edit_RightXChange(Sender: TObject);
    procedure Edit_BottomYChange(Sender: TObject);
  private
    { Private declarations }
    procedure getIndex();
    procedure getPPI();
  public
    { Public declarations }
    procedure setValue(param: ICE_IPG_PLACE_CONFIG_S; width: Integer; height: Integer; spaceNum: Integer);
    procedure getValue(var param: ICE_IPG_PLACE_CONFIG_S; var width: Integer; var height: Integer);
  end;

var
  FormAlgoCfg: TFormAlgoCfg;
  stAlgoCfg: ICE_IPG_PLACE_CONFIG_S;
  nSpaceNum, nSpaceCode: Integer;
  nWidth, nHeight: Integer;
  nIndexPPI: Integer;

implementation

{$R *.dfm}

procedure TFormAlgoCfg.Button_OKClick(Sender: TObject);
begin
  if CheckBox_Define.Checked then
  begin
    stAlgoCfg.bSpecialPlace := 1;
  end
  else begin
    stAlgoCfg.bSpecialPlace := 0;
  end;
  
  getPPI();

  nSpaceCode := ComboBox_SpaceNum.ItemIndex;
  stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Left := StrToInt(Edit_LeftX.Text);
  stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Right := strToInt(Edit_RightX.Text);
  stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Top := strToInt(Edit_TopY.Text);
  stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Bottom := StrToInt(Edit_BottomY.Text);

  self.ModalResult := mrOK;
end;

procedure TFormAlgoCfg.Button_CancleClick(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

procedure TFormAlgoCfg.setValue(param: ICE_IPG_PLACE_CONFIG_S; width: Integer; height: Integer; spaceNum: Integer);
begin
  stAlgoCfg := param;
  nWidth := width;
  nHeight := height;
  nSpaceNum := spaceNum;
end;

procedure TFormAlgoCfg.getValue(var param: ICE_IPG_PLACE_CONFIG_S; var width: Integer; var height: Integer);
begin
  param := stAlgoCfg;
  width := nWidth;
  height := nHeight;
end;

procedure TFormAlgoCfg.FormCreate(Sender: TObject);
begin
   ComboBox_SettingPPI.Items.Add('1080P(1920 x 1080)');
   ComboBox_SettingPPI.Items.Add('900P(1600 x 900)');
   ComboBox_SettingPPI.Items.Add('720P(1280 x 720)');
   ComboBox_SettingPPI.Items.Add('540P(960 x 540)');
   ComboBox_SettingPPI.Items.Add('D1(704 x 396)');
end;

procedure TFormAlgoCfg.getIndex();
begin
  if (nWidth = 1920) and (nHeight = 1080) then
  begin
    nIndexPPI := 0;
  end
  else if (nWidth = 1600) and (nHeight = 900) then
  begin
    nIndexPPI := 1;
  end
  else if (nWidth = 1280) and (nHeight = 720) then
  begin
    nIndexPPI := 2;
  end
  else if (nWidth = 960) and (nHeight = 540) then
  begin
    nIndexPPI := 3;
  end
  else if (nWidth = 704) and (nHeight = 396) then
  begin
    nIndexPPI := 4;
  end;

end;

procedure TFormAlgoCfg.getPPI();
begin
  if nIndexPPI < 0 then
    exit;
  if nIndexPPI = 0 then
  begin
    nWidth := 1920;
    nHeight := 1080;
  end
  else if nIndexPPI = 1 then
  begin
    nWidth := 1600;
    nHeight := 900;
  end
  else if nIndexPPI = 2 then
  begin
    nWidth := 1280;
    nHeight := 720;
  end
  else if nIndexPPI = 3 then
  begin
    nWidth := 960;
    nHeight := 540;
  end
  else if nIndexPPI = 4 then
  begin
    nWidth := 704;
    nHeight := 396;
  end
end;

procedure TFormAlgoCfg.FormShow(Sender: TObject);
var
  i: Integer;
begin
  ComboBox_SpaceNum.Items.Clear;

  for i := 1 to nSpaceNum do
  begin
    ComboBox_SpaceNum.Items.Add(IntToStr(i));
  end;

  getIndex();
  ComboBox_SpaceNum.ItemIndex := 0;
  ComboBox_SettingPPI.ItemIndex := nIndexPPI;
  Edit_LeftX.Text := IntToStr(stAlgoCfg.stPlaceParam[0].stRecRect.s16Left);
  Edit_RightX.Text := IntToStr(stAlgoCfg.stPlaceParam[0].stRecRect.s16Right);
  Edit_TopY.Text := IntToStr(stAlgoCfg.stPlaceParam[0].stRecRect.s16Top);
  Edit_BottomY.Text := IntToStr(stAlgoCfg.stPlaceParam[0].stRecRect.s16Bottom);
  nSpaceCode := 0;
  if stAlgoCfg.bSpecialPlace = 1 then
  begin
    CheckBox_Define.Checked := true;
  end
  else begin
  CheckBox_Define.Checked := false;
  end;
end;

procedure TFormAlgoCfg.ComboBox_SettingPPIChange(Sender: TObject);
var
  width, height: Integer;
  rx, ry: Single;
  i: Integer;
begin
  width := nWidth;
  height := nHeight;
  nIndexPPI := ComboBox_SettingPPI.ItemIndex;
  getPPI();
  rx := nWidth / width;
  ry := nHeight / height;

  for i := 0 to (nSpaceNum-1) do
  begin
    stAlgoCfg.stPlaceParam[i].stRecRect.s16Left := Round (stAlgoCfg.stPlaceParam[i].stRecRect.s16Left * rx);
    stAlgoCfg.stPlaceParam[i].stRecRect.s16Right := Round (stAlgoCfg.stPlaceParam[i].stRecRect.s16Right * rx);
    stAlgoCfg.stPlaceParam[i].stRecRect.s16Top := Round (stAlgoCfg.stPlaceParam[i].stRecRect.s16Top * ry);
    stAlgoCfg.stPlaceParam[i].stRecRect.s16Bottom := Round (stAlgoCfg.stPlaceParam[i].stRecRect.s16Bottom * ry);
  end;
  nSpaceCode := ComboBox_SpaceNum.ItemIndex;

  Edit_LeftX.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Left);
  Edit_RightX.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Right);
  Edit_TopY.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Top);
  Edit_BottomY.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Bottom);
end;

procedure TFormAlgoCfg.ComboBox_SpaceNumChange(Sender: TObject);
begin
    stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Left := StrToInt(Edit_LeftX.Text);
    stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Right := StrToInt(Edit_RightX.Text);
    stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Top := StrToInt(Edit_TopY.Text);
    stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Bottom := StrToInt(Edit_BottomY.Text);

    nSpaceCode := ComboBox_SpaceNum.ItemIndex;
    Edit_LeftX.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Left);
    Edit_RightX.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Right);
    Edit_TopY.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Top);
    Edit_BottomY.Text := IntToStr(stAlgoCfg.stPlaceParam[nSpaceCode].stRecRect.s16Bottom);
end;

procedure TFormAlgoCfg.Edit_LeftXKeyPress(Sender: TObject; var Key: Char);
begin
  if not (key in ['0'..'9', #8]) then
    key := #0;
end;

procedure TFormAlgoCfg.Edit_TopYKeyPress(Sender: TObject; var Key: Char);
begin
  if not (key in ['0'..'9', #8]) then
    key := #0;
end;

procedure TFormAlgoCfg.Edit_RightXKeyPress(Sender: TObject; var Key: Char);
begin
  if not (key in ['0'..'9', #8]) then
    key := #0;
end;

procedure TFormAlgoCfg.Edit_BottomYKeyPress(Sender: TObject;
  var Key: Char);
begin
  if not (key in ['0'..'9', #8]) then
    key := #0;
end;

procedure TFormAlgoCfg.Edit_LeftXChange(Sender: TObject);
begin
  if StrToInt(Edit_LeftX.Text) > nWidth then
     Edit_LeftX.Text := IntToStr(nWidth - 10);
end;

procedure TFormAlgoCfg.Edit_TopYChange(Sender: TObject);
begin
   if StrToInt(Edit_TopY.Text) > nHeight then
     Edit_TopY.Text := IntToStr(nHeight - 10);
end;

procedure TFormAlgoCfg.Edit_RightXChange(Sender: TObject);
begin
  if StrToInt(Edit_RightX.Text) > nWidth then
     Edit_RightX.Text := IntToStr(nWidth - 10);
end;

procedure TFormAlgoCfg.Edit_BottomYChange(Sender: TObject);
begin
  if StrToInt(Edit_BottomY.Text) > nHeight then
     Edit_BottomY.Text := IntToStr(nHeight - 10);
end;

end.
