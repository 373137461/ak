unit UnitIPSearch;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, ipgsdk;

type
  TFormIPSearch = class(TForm)
    ListView_DevInfo: TListView;
    Button_IPSearch: TButton;
    Button_modIP: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button_IPSearchClick(Sender: TObject);
    procedure Button_modIPClick(Sender: TObject);
  private
    { Private declarations }
    function SplitString(const Source,ch:String):TStringList;
  public
    { Public declarations }
  end;

var
  FormIPSearch: TFormIPSearch;
  strDevTitle: array[0..4] of String=('id', 'mac', 'ip', 'ver', 'hwInfo');

implementation

{$R *.dfm}

procedure TFormIPSearch.FormCreate(Sender: TObject);
var
  i: Integer;
begin
 begin
  with ListView_DevInfo do
  begin
    for i:=0 to 4 do
    begin
      Columns.Add;
      Columns.Items[i].Caption := strDevTitle[i];
      if (i = 0) then
        Columns.Items[i].Width := 60;
      if (i = 1) then
        Columns.Items[i].Width := 130;
      if (i = 2) then
        Columns.Items[i].Width := 110;
      if (i = 3) then
        Columns.Items[i].Width := 520;
      if (i = 4) then
        Columns.Items[i].Width := 160;
    end;
  end
  end;
end;

procedure TFormIPSearch.Button_IPSearchClick(Sender: TObject);
var
  data: PChar;
  subStrs: TStringList;
  subStrsList: TStringList;
  i: Integer;
  j: Integer;
  nID: Integer;
begin
  subStrs := TStringList.Create;

  ListView_DevInfo.Items.Clear;
  data := strAlloc(4096 * sizeof(char));
  ICE_IPCSDK_SearchDev(data);

  subStrs := SplitString(data, #$D#$A);
  for i:=0 to (subStrs.Count-2) do
  begin
    nID := ListView_DevInfo.Items.Count;

    subStrsList := TStringList.Create;
    subStrsList := SplitString(subStrs[i], #9);

    if subStrsList.Count > 1 then
    begin
      with ListView_DevInfo.Items.Insert(nID) do
      begin
        caption := IntToStr(nID + 1);
        for j:=0 to (subStrsList.Count - 1) do
        subitems.Add(subStrsList[j]);
      end;
    end;
  end;

  strDispose(data);
end;

function TFormIPSearch.SplitString(const Source,ch:String):TStringList;
var
Temp:String;
I:Integer;
chLength:Integer;
begin
Result:=TStringList.Create;
//如果是空自符串则返回空列表
if Source='' then Exit;
Temp:=Source;
I:=Pos(ch,Source);
chLength := Length(ch);
while I<>0 do
begin
Result.Add(Copy(Temp,0,I-chLength+1));
Delete(Temp,1,I-1 + chLength);
I:=pos(ch,Temp);
end;
Result.add(Temp);
end;

procedure TFormIPSearch.Button_modIPClick(Sender: TObject);
begin
  if ListView_DevInfo.Selected <> nil then
  begin
  end;
end;

end.
