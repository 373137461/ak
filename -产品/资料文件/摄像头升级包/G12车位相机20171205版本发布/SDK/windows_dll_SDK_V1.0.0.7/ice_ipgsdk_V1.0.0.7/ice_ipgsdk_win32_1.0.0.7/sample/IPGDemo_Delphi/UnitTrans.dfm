object FormTrans: TFormTrans
  Left = 569
  Top = 260
  Width = 425
  Height = 362
  Caption = #36879#20256#25968#25454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyPress = Memo1KeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 232
    Top = 272
    Width = 73
    Height = 33
    Caption = #21457#36865
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 320
    Top = 272
    Width = 73
    Height = 33
    Caption = #21462#28040
    TabOrder = 1
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 16
    Top = 16
    Width = 377
    Height = 241
    ImeMode = imDisable
    ScrollBars = ssVertical
    TabOrder = 2
    OnKeyPress = Memo1KeyPress
  end
end
