object SystemCfg: TSystemCfg
  Left = 893
  Top = 123
  Width = 822
  Height = 512
  Caption = #31995#32479#21442#25968
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
  object GroupBox1: TGroupBox
    Left = 24
    Top = 16
    Width = 377
    Height = 153
    Caption = #36710#20301#21442#25968
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 32
      Width = 60
      Height = 13
      Caption = #36710#20301#32534#21495#65306
    end
    object Label2: TLabel
      Left = 24
      Top = 64
      Width = 60
      Height = 13
      Caption = #20351#33021#36710#20301#65306
    end
    object Label3: TLabel
      Left = 24
      Top = 112
      Width = 60
      Height = 13
      Caption = #36710#20301#31867#22411#65306
    end
    object ComboBox_SpaceNum: TComboBox
      Left = 104
      Top = 24
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
      OnChange = ComboBox_SpaceNumChange
    end
    object RadioGroup_Enable: TRadioGroup
      Left = 104
      Top = 48
      Width = 241
      Height = 41
      Columns = 2
      TabOrder = 1
    end
    object RadioGroup_Type: TRadioGroup
      Left = 104
      Top = 96
      Width = 241
      Height = 41
      Columns = 3
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 24
    Top = 192
    Width = 377
    Height = 193
    Caption = #25511#28783#21442#25968
    TabOrder = 1
    object Label4: TLabel
      Left = 16
      Top = 24
      Width = 84
      Height = 13
      Caption = #36828#31243#25511#28783#21442#25968#65306
    end
    object Label5: TLabel
      Left = 32
      Top = 72
      Width = 109
      Height = 13
      Caption = #36828#31243#25511#21046#20854#20182#30456#26426'IP:'
    end
    object Label6: TLabel
      Left = 16
      Top = 104
      Width = 72
      Height = 13
      Caption = #21463#25511#28783#21442#25968#65306
    end
    object Label7: TLabel
      Left = 32
      Top = 160
      Width = 118
      Height = 13
      Caption = #21463#25511#20110#36828#31243#30456#26426#30340'IP'#65306
    end
    object CheckBox_Remote: TCheckBox
      Left = 32
      Top = 48
      Width = 145
      Height = 17
      Caption = #36828#31243#25511#21046#20854#20182#30456#26426
      TabOrder = 0
    end
    object Edit_RemoteIP: TEdit
      Left = 184
      Top = 64
      Width = 145
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object CheckBox_Control: TCheckBox
      Left = 32
      Top = 128
      Width = 121
      Height = 17
      Caption = #21463#25511#20110#36828#31243#30456#26426
      TabOrder = 2
    end
    object Edit_ControlIP: TEdit
      Left = 184
      Top = 152
      Width = 145
      Height = 21
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
    end
  end
  object Button_OK: TButton
    Left = 240
    Top = 424
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 2
    OnClick = Button_OKClick
  end
  object Button_Cancle: TButton
    Left = 480
    Top = 424
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 3
    OnClick = Button_CancleClick
  end
  object GroupBox3: TGroupBox
    Left = 424
    Top = 16
    Width = 369
    Height = 169
    Caption = 'http'#25512#36865#21442#25968
    TabOrder = 4
    object Label8: TLabel
      Left = 32
      Top = 48
      Width = 89
      Height = 13
      Caption = 'http'#25512#36865#22320#22336#65306
    end
    object Label9: TLabel
      Left = 144
      Top = 104
      Width = 153
      Height = 13
      Caption = #23450#26102#19978#20256#26102#38388#65288#20998#38047#65289#65306
    end
    object Label10: TLabel
      Left = 144
      Top = 144
      Width = 153
      Height = 13
      Caption = #24515#36339#19978#20256#26102#38388#65288#20998#38047#65289#65306
    end
    object CheckBox_httpEnable: TCheckBox
      Left = 8
      Top = 24
      Width = 97
      Height = 17
      Caption = #21551#21160'http'#25512#36865
      TabOrder = 0
    end
    object Edit_httpAddr: TEdit
      Left = 128
      Top = 40
      Width = 233
      Height = 21
      TabOrder = 1
    end
    object CheckBox_smallPic: TCheckBox
      Left = 32
      Top = 72
      Width = 97
      Height = 17
      Caption = #23567#22270#29255
      TabOrder = 2
    end
    object CheckBox_bigPic: TCheckBox
      Left = 152
      Top = 72
      Width = 97
      Height = 17
      Caption = #22823#22270#29255
      TabOrder = 3
    end
    object CheckBox_uploadEnable: TCheckBox
      Left = 32
      Top = 104
      Width = 105
      Height = 17
      Caption = #21551#21160#23450#26102#19978#20256
      TabOrder = 4
    end
    object CheckBox_heartbeatEnable: TCheckBox
      Left = 32
      Top = 144
      Width = 105
      Height = 17
      Caption = #21551#21160#24515#36339#21151#33021
      TabOrder = 5
    end
    object Edit_uploadInterval: TEdit
      Left = 304
      Top = 96
      Width = 57
      Height = 21
      TabOrder = 6
      Text = '1'
      OnChange = Edit_uploadIntervalChange
      OnKeyPress = Edit_uploadIntervalKeyPress
    end
    object Edit_heartbeatInterval: TEdit
      Left = 304
      Top = 136
      Width = 57
      Height = 21
      TabOrder = 7
      Text = '1'
      OnChange = Edit_heartbeatIntervalChange
      OnKeyPress = Edit_heartbeatIntervalKeyPress
    end
  end
end
