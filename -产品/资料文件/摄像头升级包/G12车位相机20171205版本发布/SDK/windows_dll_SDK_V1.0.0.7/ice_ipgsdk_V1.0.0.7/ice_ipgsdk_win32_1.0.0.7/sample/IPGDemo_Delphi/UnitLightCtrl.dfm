object FormLightCtrl: TFormLightCtrl
  Left = 523
  Top = 360
  Width = 269
  Height = 271
  Caption = 'FormLightCtrl'
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
  object Label_style: TLabel
    Left = 24
    Top = 48
    Width = 60
    Height = 13
    Caption = #20142#28783#26041#24335#65306
  end
  object Label_color: TLabel
    Left = 24
    Top = 96
    Width = 60
    Height = 13
    Caption = #28783#20809#39068#33394#65306
  end
  object ComboBox_style: TComboBox
    Left = 104
    Top = 40
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object ComboBox_color: TComboBox
    Left = 104
    Top = 88
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object Button_ok: TButton
    Left = 24
    Top = 152
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 2
    OnClick = Button_okClick
  end
  object Button_cancel: TButton
    Left = 136
    Top = 152
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 3
    OnClick = Button_cancelClick
  end
end
