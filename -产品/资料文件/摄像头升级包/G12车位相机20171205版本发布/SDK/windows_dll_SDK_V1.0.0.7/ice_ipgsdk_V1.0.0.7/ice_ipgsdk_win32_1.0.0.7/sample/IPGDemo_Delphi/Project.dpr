program Project;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  ipgsdk in 'ipgsdk.pas',
  UintSystemCfg in 'UintSystemCfg.pas' {SystemCfg},
  UartSet in 'UartSet.pas' {Form2},
  UnitAlgoCfg in 'UnitAlgoCfg.pas' {FormAlgoCfg},
  UnitTrans in 'UnitTrans.pas' {FormTrans},
  UnitIPSearch in '..\..\sdk_dll\delphi\UnitIPSearch.pas' {FormIPSearch},
  UnitIPConfig in 'UnitIPConfig.pas' {FormIPConfig},
  UnitLightCtrl in 'UnitLightCtrl.pas' {FormLightCtrl};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TSystemCfg, SystemCfg);
  Application.CreateForm(TFormUartSet, FormUartSet);
  Application.CreateForm(TFormAlgoCfg, FormAlgoCfg);
  Application.CreateForm(TFormTrans, FormTrans);
  Application.CreateForm(TFormIPSearch, FormIPSearch);
  Application.CreateForm(TFormIPConfig, FormIPConfig);
  Application.CreateForm(TFormLightCtrl, FormLightCtrl);
  Application.Run;
end.
