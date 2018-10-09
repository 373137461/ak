object FormAlgoCfg: TFormAlgoCfg
  Left = 1289
  Top = 497
  Width = 293
  Height = 356
  Caption = #31639#27861#21442#25968
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 48
    Width = 72
    Height = 13
    Caption = #35774#32622#20998#36776#29575#65306
  end
  object Label2: TLabel
    Left = 16
    Top = 80
    Width = 60
    Height = 13
    Caption = #36710#20301#32534#21495#65306
  end
  object Label3: TLabel
    Left = 16
    Top = 112
    Width = 53
    Height = 13
    Caption = #24038'x'#22352#26631#65306
  end
  object Label4: TLabel
    Left = 16
    Top = 144
    Width = 53
    Height = 13
    Caption = #19978'y'#22352#26631#65306
  end
  object Label5: TLabel
    Left = 16
    Top = 176
    Width = 53
    Height = 13
    Caption = #21491'x'#22352#26631#65306
  end
  object Label6: TLabel
    Left = 16
    Top = 208
    Width = 53
    Height = 13
    Caption = #19979'y'#22352#26631#65306
  end
  object CheckBox_Define: TCheckBox
    Left = 16
    Top = 16
    Width = 129
    Height = 17
    Caption = #33258#23450#20041#35782#21035#21306#22495
    TabOrder = 0
  end
  object ComboBox_SettingPPI: TComboBox
    Left = 112
    Top = 40
    Width = 145
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 1
    OnChange = ComboBox_SettingPPIChange
  end
  object ComboBox_SpaceNum: TComboBox
    Left = 112
    Top = 72
    Width = 145
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 2
    OnChange = ComboBox_SpaceNumChange
  end
  object Edit_LeftX: TEdit
    Left = 112
    Top = 104
    Width = 145
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 3
    OnChange = Edit_LeftXChange
    OnKeyPress = Edit_LeftXKeyPress
  end
  object Edit_TopY: TEdit
    Left = 112
    Top = 136
    Width = 145
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 4
    OnChange = Edit_TopYChange
    OnKeyPress = Edit_TopYKeyPress
  end
  object Edit_RightX: TEdit
    Left = 112
    Top = 168
    Width = 145
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 5
    OnChange = Edit_RightXChange
    OnKeyPress = Edit_RightXKeyPress
  end
  object Edit_BottomY: TEdit
    Left = 112
    Top = 200
    Width = 145
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 6
    OnChange = Edit_BottomYChange
    OnKeyPress = Edit_BottomYKeyPress
  end
  object Button_OK: TButton
    Left = 24
    Top = 264
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 7
    OnClick = Button_OKClick
  end
  object Button_Cancle: TButton
    Left = 176
    Top = 264
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 8
    OnClick = Button_CancleClick
  end
end
