unit UnitLightCtrl;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TFormLightCtrl = class(TForm)
    Label_style: TLabel;
    Label_color: TLabel;
    ComboBox_style: TComboBox;
    ComboBox_color: TComboBox;
    Button_ok: TButton;
    Button_cancel: TButton;
    procedure FormShow(Sender: TObject);
    procedure Button_okClick(Sender: TObject);
    procedure Button_cancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure setValue(nInStyle: Integer; nInColor: Integer);
    procedure getValue(var nOutStyle: Integer; var nOutColor: Integer);
  end;

var
  FormLightCtrl: TFormLightCtrl;
  nStyle: Integer;
  nColor: Integer;

implementation

{$R *.dfm}

procedure TFormLightCtrl.setValue(nInStyle: Integer; nInColor: Integer);
begin
  nStyle := nInStyle;
  nColor := nInColor;
end;

procedure TFormLightCtrl.getValue(var nOutStyle: Integer; var nOutColor: Integer);
begin
  nOutStyle := ComboBox_style.ItemIndex;
  nOutColor := ComboBox_color.ItemIndex +1;
end;
procedure TFormLightCtrl.FormShow(Sender: TObject);
begin
  ComboBox_style.Items.Clear;
  ComboBox_color.Items.Clear;

  ComboBox_style.Items.Add('¹Ø±Õsdk¿ØµÆ');
  ComboBox_style.Items.Add('Ãð');
  ComboBox_style.Items.Add('ÁÁ');
  ComboBox_style.Items.Add('ÉÁË¸');
  ComboBox_color.Items.Add('ºìÉ«');
  ComboBox_color.Items.Add('ÂÌÉ«');
  ComboBox_color.Items.Add('»ÆÉ«');
  ComboBox_color.Items.Add('À¶É«');
  
  if nStyle >=0 then
    ComboBox_style.ItemIndex := nStyle;
  if nColor > 0 then
  begin
    ComboBox_color.ItemIndex := nColor - 1;
  end
  else begin
    ComboBox_color.ItemIndex := 0;
  end;
end;

procedure TFormLightCtrl.Button_okClick(Sender: TObject);
begin
  self.ModalResult := mrOK;
end;

procedure TFormLightCtrl.Button_cancelClick(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

end.
