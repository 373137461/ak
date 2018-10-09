object FormIPSearch: TFormIPSearch
  Left = 506
  Top = 223
  Width = 1020
  Height = 645
  Caption = 'FormIPSearch'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ListView_DevInfo: TListView
    Left = 8
    Top = 47
    Width = 985
    Height = 538
    Columns = <>
    GridLines = True
    ReadOnly = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Button_IPSearch: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = #25628#32034
    TabOrder = 1
    OnClick = Button_IPSearchClick
  end
  object Button_modIP: TButton
    Left = 128
    Top = 8
    Width = 75
    Height = 25
    Caption = #20462#25913'IP'
    TabOrder = 2
    OnClick = Button_modIPClick
  end
end
