unit UnitIPConfig;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, StrUtils;

type
  TFormIPConfig = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Edit_IP: TEdit;
    Edit_mask: TEdit;
    Edit_gateway: TEdit;
    Button_ok: TButton;
    Button_cancel: TButton;
    procedure Button_okClick(Sender: TObject);
    procedure Button_cancelClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure setValue(strInIP: string);
    procedure getValue(var strOutIP: string; var strOutMask: string; var strOutGateway: string);
  end;

var
  FormIPConfig: TFormIPConfig;
  strIP: string;

implementation

{$R *.dfm}

procedure TFormIPConfig.Button_okClick(Sender: TObject);
begin
  self.ModalResult := mrOK;
end;

procedure TFormIPConfig.Button_cancelClick(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

procedure TFormIPConfig.setValue(strInIP: string);
begin
  strIP := strInIP;
end;

procedure TFormIPConfig.getValue(var strOutIP: string; var strOutMask: string; var strOutGateway: string);
begin
  strOutIP := Edit_IP.Text;
  strOutMask := Edit_mask.Text;
  strOutGateway := Edit_gateway.Text;
end;

procedure TFormIPConfig.FormShow(Sender: TObject);
begin
  Edit_IP.Text := strIP;
  Edit_gateway.Text := LeftStr(strIP, LastDelimiter( '.', strIP)) + '1';
end;

end.
