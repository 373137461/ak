object FormUartSet: TFormUartSet
  Left = 614
  Top = 87
  BorderStyle = bsToolWindow
  Caption = #22806#35774#21442#25968
  ClientHeight = 321
  ClientWidth = 657
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
    Left = 344
    Top = 24
    Width = 289
    Height = 233
    Caption = 'RS232'
    TabOrder = 2
    object Label3: TLabel
      Left = 40
      Top = 96
      Width = 48
      Height = 13
      Caption = #25968#25454#20301#65306
    end
    object Label4: TLabel
      Left = 40
      Top = 128
      Width = 48
      Height = 13
      Caption = #26657#39564#20301#65306
    end
    object Label5: TLabel
      Left = 40
      Top = 160
      Width = 48
      Height = 13
      Caption = #20572#27490#20301#65306
    end
    object Label6: TLabel
      Left = 40
      Top = 192
      Width = 60
      Height = 13
      Caption = #27969#25511#27169#24335#65306
    end
    object Label2: TLabel
      Left = 40
      Top = 64
      Width = 48
      Height = 13
      Caption = #27874#29305#29575#65306
    end
    object CheckBoxEnable: TCheckBox
      Left = 24
      Top = 32
      Width = 97
      Height = 17
      Caption = #20018#21475#20351#33021
      TabOrder = 0
    end
    object ComboBoxBaudrate: TComboBox
      Left = 120
      Top = 56
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object ComboBoxDataBits: TComboBox
      Left = 120
      Top = 88
      Width = 145
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object ComboBoxParity: TComboBox
      Left = 120
      Top = 120
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 3
    end
    object ComboBoxStopBits: TComboBox
      Left = 120
      Top = 152
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
    end
    object ComboBoxFlowCtrl: TComboBox
      Left = 120
      Top = 184
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
    end
  end
  object ButtonCancle: TButton
    Left = 552
    Top = 280
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 0
    OnClick = ButtonCancleClick
  end
  object ButtonOk: TButton
    Left = 464
    Top = 280
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 1
    OnClick = ButtonOkClick
  end
  object GroupBox2: TGroupBox
    Left = 24
    Top = 24
    Width = 289
    Height = 233
    Caption = 'RS485'
    TabOrder = 3
    object Label1: TLabel
      Left = 40
      Top = 96
      Width = 48
      Height = 13
      Caption = #25968#25454#20301#65306
    end
    object Label7: TLabel
      Left = 40
      Top = 128
      Width = 48
      Height = 13
      Caption = #26657#39564#20301#65306
    end
    object Label8: TLabel
      Left = 40
      Top = 160
      Width = 48
      Height = 13
      Caption = #20572#27490#20301#65306
    end
    object Label9: TLabel
      Left = 40
      Top = 192
      Width = 60
      Height = 13
      Caption = #27969#25511#27169#24335#65306
    end
    object Label10: TLabel
      Left = 40
      Top = 64
      Width = 48
      Height = 13
      Caption = #27874#29305#29575#65306
    end
    object CheckBoxEnable2: TCheckBox
      Left = 24
      Top = 32
      Width = 97
      Height = 17
      Caption = #20018#21475#20351#33021
      TabOrder = 0
    end
    object ComboBoxBaudrate2: TComboBox
      Left = 120
      Top = 56
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object ComboBoxDataBits2: TComboBox
      Left = 120
      Top = 88
      Width = 145
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object ComboBoxParity2: TComboBox
      Left = 120
      Top = 120
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 3
    end
    object ComboBoxStopBits2: TComboBox
      Left = 120
      Top = 152
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
    end
    object ComboBoxFlowCtrl2: TComboBox
      Left = 120
      Top = 184
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
    end
  end
end
