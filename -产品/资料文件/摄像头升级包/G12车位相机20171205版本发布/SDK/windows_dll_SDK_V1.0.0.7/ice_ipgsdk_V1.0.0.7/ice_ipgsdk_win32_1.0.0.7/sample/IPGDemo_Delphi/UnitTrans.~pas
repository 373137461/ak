unit UnitTrans;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, ipgsdk;

type
  TFormTrans = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Memo1: TMemo;
    procedure Memo1KeyPress(Sender: TObject; var Key: Char);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    hSDK: Pointer;
    nType: Integer;
  end;

var
  FormTrans: TFormTrans;

implementation

{$R *.dfm}

procedure TFormTrans.Memo1KeyPress(Sender: TObject; var Key: Char);
begin
  if (((Key >= '0') and (Key <= '9')) or
  ((Key >= 'a') and (Key <= 'f')) or
  ((Key >= 'A') and (Key <= 'F')) or
  (Key = ' ') or (Key = '\t') or
  (Key = '\r') or (Key = '\n') or
  (Key = Char(VK_BACK)) or (Key = Char(VK_DELETE)) or
  //(Key = Char(VK_CONTROL)) or (Key = Char(VK_ESCAPE)) or
  (Key = Char(VK_LEFT)) or (Key = Char(VK_RIGHT)) or
  (Key = Char(VK_UP)) or (Key = Char(VK_DOWN)) or
  (Key = Char(3)) or (Key = Char(22))) then
  begin
    exit;
  end
  else
  begin
    MessageBeep(MB_OK);
    Key := Char(0);
  end;
end;

procedure TFormTrans.Button1Click(Sender: TObject);
var
  len, count, i, value, trans_len: Integer;
  trans_buf: array[0..4095] of Char;
  data: Char;
begin
  len := Length(Memo1.Text);
  trans_len := 0;
  count := 0;

  for i := 1 to len do
	begin
		data := Memo1.Text[i];
		if ((data = ' ') or (data = '\t') or
      (data = '\r') or (data = '\n')) then
			continue;

		value := 0;
		if ((data >= '0') and (data <= '9')) then
    begin
			value := Integer(data) - 48;
    end
		else if ((data >= 'A') and (data <= 'F')) then
    begin
			value := 10 + Integer(data) - 65;
    end
    else if ((data >= 'a') and (data <= 'f')) then
    begin
			value := 10 + Integer(data) - 97;
    end;

		if ((len = i) and (0 <> ((count + 1) mod 2))) then
		begin
			trans_buf[trans_len] := Char(value);
			trans_len := trans_len + 1;
		end
		else
		begin
			if (0 = (count mod 2)) then
			begin
				trans_buf[trans_len] := Char(value * 16);
			end
			else
			begin
				trans_buf[trans_len] := Char(Integer(trans_buf[trans_len]) + value);
				trans_len := trans_len + 1;
			end;

      count := count + 1;
    end;
  end;

  if (nType = 0) then
  begin
    ICE_IPCSDK_TransSerialPort(hSDK, trans_buf, trans_len);
  end
  else
  begin
    ICE_IPCSDK_TransSerialPort_RS232(hSDK, trans_buf, trans_len);
  end;
end;

procedure TFormTrans.Button2Click(Sender: TObject);
begin
  self.ModalResult := mrCancel;
end;

end.
