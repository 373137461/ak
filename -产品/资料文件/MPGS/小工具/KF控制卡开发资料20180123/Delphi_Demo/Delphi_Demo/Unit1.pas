unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms, HR_KFLED,  Sv800,
  Dialogs, StdCtrls, sComboBox, sLabel;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Edit1: TEdit;
    Edit2: TEdit;
    sLabel1: TsLabel;
    sComboBox1: TComboBox;
    sComboBox2: TComboBox;
    Button5: TButton;
    Button6: TButton;
    Button2: TButton;
    sLabel2: TsLabel;
    sLabel3: TsLabel;
    Edit3: TEdit;
    sLabel4: TsLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}


function URLEncode_gbk(S: string): string;
var i: Integer; InQueryString :Boolean;
begin
   Result :='';
   InQueryString :=true;

   for i :=1 to Length(S) do begin
      case S[i] of
         'A'..'Z', 'a'..'z', '0'..'9', '-', '_', '.': //1 用户常用的字母和数字，以及'-_.'不作为系统分隔符，可以不做转换。
            Result := Result + S[i];
         ' ': //2 空格符号，转化为+或%20，函数最后，都加替换掉’+‘的处理代码
            if InQueryString then
                 Result :=Result +'+'
            else Result :=Result +'%20';
         else //3 其他特殊符号或中文，都要转化为3位的Utf-8编码值
            Result := Result + SysUtils.IntToHex(Ord(S[i]), 2);
      end;
   end;
   Result :=StringReplace(Result, '+', '%20', [rfReplaceAll]);
   Result :=StringReplace(Result, '*', '%2A', [rfReplaceAll]);
end;
                    
//function URLEncode_gbk(S: string): string;
//var i: Integer; InQueryString :Boolean;
//begin
//   Result :='';
//   InQueryString :=true;
//
//   for i :=1 to Length(S) do begin
//      case S[i] of
//         'A'..'Z', 'a'..'z', '0'..'9', '-', '_', '.': //1 用户常用的字母和数字，以及'-_.'不作为系统分隔符，可以不做转换。
//            Result := Result + S[i];
//         ' ': //2 空格符号，转化为+或%20，函数最后，都加替换掉’+‘的处理代码
//            if InQueryString then
//                 Result :=Result +'+'
//            else Result :=Result +'%20';
//         else //3 其他特殊符号或中文，都要转化为3位的Utf-8编码值
//            Result := Result + '%' + SysUtils.IntToHex(Ord(S[i]), 2);
//      end;
//   end;
//   Result :=StringReplace(Result, '+', '%20', [rfReplaceAll]);
//   Result :=StringReplace(Result, '*', '%2A', [rfReplaceAll]);
//end;

procedure TForm1.Button1Click(Sender: TObject);
var
  i:integer;
  Len1,Len2:string;
  len:integer;
  le:string;
  sColor:string;
begin
    len:= Length(Trim(Self.Edit1.Text));
    le:= IntToHex(len,4);
    Len1:= Copy(le,1,2);
    Len2:= Copy(le,3,2);
    if sComboBox1.Text = '红色' then   sColor:= 'FF000000';
    if sComboBox1.Text = '绿色' then   sColor:= '00FF0000';
    if sComboBox1.Text = '黄色' then   sColor:= 'FFFF0000';
    Sv800.HR_KFGGDisplayText(self.Edit3.Text,IntToHex(1,2),IntToHex(1,2),'FF','15','01','00','05','15','01','03',sColor,'00000000',
    len2+Len1,PChar(Trim(Edit1.text)),nil);
end;



procedure TForm1.Button2Click(Sender: TObject);
begin
   sv800.HR_KFSpack(self.Edit3.Text,'01',PChar(Edit1.Text),Nil); ///'欢迎光临'
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  Close_Comm(Self.sComboBox2.Text);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
   Init_Comm(self.sComboBox2.Text)
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  Close_Comm(Self.sComboBox2.Text);
end;

procedure TForm1.Button7Click(Sender: TObject);
var
  i:integer;
  Len1,Len2:string;
  len:integer;
  le:string;
  sColor:string;
begin
    len:= Length(Trim(Self.Edit1.Text));
    le:= IntToHex(len,4);
    Len1:= Copy(le,1,2);
    Len2:= Copy(le,3,2);
    if sComboBox1.Text = '红色' then   sColor:= 'FF000000';
    if sComboBox1.Text = '绿色' then   sColor:= '00FF0000';
    if sComboBox1.Text = '黄色' then   sColor:= 'FFFF0000';
    Sv800.HR_KFGGDisplayText(IntToHex(1,2),IntToHex(1,2),IntToHex(1,2),'FF','15','01','00','05','15','01','03',sColor,'00000000',
    len2+Len1,PChar(Trim(Edit1.text)),nil);
end;


end.


