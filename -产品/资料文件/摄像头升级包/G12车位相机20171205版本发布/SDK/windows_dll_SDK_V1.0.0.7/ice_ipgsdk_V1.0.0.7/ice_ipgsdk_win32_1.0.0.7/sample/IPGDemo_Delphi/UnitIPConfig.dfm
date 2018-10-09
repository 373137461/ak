object FormIPConfig: TFormIPConfig
  Left = 861
  Top = 332
  Width = 375
  Height = 271
  Caption = 'FormIPConfig'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 72
    Top = 24
    Width = 46
    Height = 13
    Caption = 'IP'#22320#22336#65306
  end
  object Label2: TLabel
    Left = 56
    Top = 64
    Width = 65
    Height = 13
    Caption = #23376#32593#25513#30721#65306
  end
  object Label3: TLabel
    Left = 56
    Top = 104
    Width = 65
    Height = 13
    Caption = #40664#35748#32593#20851#65306
  end
  object Edit_IP: TEdit
    Left = 136
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Edit_mask: TEdit
    Left = 136
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '255.255.255.0'
  end
  object Edit_gateway: TEdit
    Left = 136
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object Button_ok: TButton
    Left = 56
    Top = 168
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 3
    OnClick = Button_okClick
  end
  object Button_cancel: TButton
    Left = 208
    Top = 168
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 4
    OnClick = Button_cancelClick
  end
end
