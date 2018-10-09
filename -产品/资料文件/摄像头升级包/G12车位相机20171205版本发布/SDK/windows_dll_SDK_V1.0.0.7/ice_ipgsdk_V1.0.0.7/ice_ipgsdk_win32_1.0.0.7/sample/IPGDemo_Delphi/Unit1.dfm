object Form1: TForm1
  Left = 311
  Top = 110
  Width = 1203
  Height = 740
  Caption = 'DelphiTest'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 24
    Top = 16
    Width = 385
    Height = 201
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 432
    Top = 16
    Width = 385
    Height = 201
    TabOrder = 1
  end
  object Panel3: TPanel
    Left = 24
    Top = 232
    Width = 385
    Height = 201
    TabOrder = 2
  end
  object Panel4: TPanel
    Left = 432
    Top = 232
    Width = 385
    Height = 201
    TabOrder = 3
  end
  object EditIP: TEdit
    Left = 840
    Top = 24
    Width = 145
    Height = 21
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 4
    Text = '192.168.55.100'
  end
  object Button_Login: TButton
    Left = 1000
    Top = 24
    Width = 75
    Height = 25
    Caption = #30331#24405
    TabOrder = 5
    OnClick = Button_LoginClick
  end
  object GroupBox1: TGroupBox
    Left = 840
    Top = 168
    Width = 321
    Height = 193
    Caption = #25805#20316
    TabOrder = 6
    object Button_Logout: TButton
      Left = 8
      Top = 24
      Width = 75
      Height = 25
      Caption = #36864#20986
      Enabled = False
      TabOrder = 0
      OnClick = Button_LogoutClick
    end
    object Button_Single: TButton
      Left = 104
      Top = 24
      Width = 105
      Height = 25
      Caption = #21333#20010#36710#20301#29366#24577'    '
      Enabled = False
      TabOrder = 1
      OnClick = Button_SingleClick
    end
    object ComboBox_SpaceNum: TComboBox
      Left = 216
      Top = 24
      Width = 73
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object Button_System: TButton
      Left = 8
      Top = 56
      Width = 75
      Height = 25
      Caption = #31995#32479#21442#25968
      Enabled = False
      TabOrder = 3
      OnClick = Button_SystemClick
    end
    object Button_All: TButton
      Left = 104
      Top = 56
      Width = 105
      Height = 25
      Caption = #25152#26377#36710#20301#29366#24577'  '
      Enabled = False
      TabOrder = 4
      OnClick = Button_AllClick
    end
    object Button_Uart: TButton
      Left = 8
      Top = 88
      Width = 75
      Height = 25
      Caption = #22806#35774#21442#25968
      Enabled = False
      TabOrder = 5
      OnClick = Button_UartClick
    end
    object Button_RS232: TButton
      Left = 104
      Top = 120
      Width = 105
      Height = 25
      Caption = '232'#20018#21475#21457#36865
      Enabled = False
      TabOrder = 6
      OnClick = Button_RS232Click
    end
    object Button_Algo: TButton
      Left = 8
      Top = 120
      Width = 75
      Height = 25
      Caption = #31639#27861#21442#25968
      Enabled = False
      TabOrder = 7
      OnClick = Button_AlgoClick
    end
    object CheckBox_SaveLog_232: TCheckBox
      Left = 216
      Top = 96
      Width = 97
      Height = 17
      Caption = #20445#23384'232'#26085#24535
      TabOrder = 8
    end
    object Button_RS485: TButton
      Left = 104
      Top = 88
      Width = 105
      Height = 25
      Caption = '485'#20018#21475#21457#36865
      Enabled = False
      TabOrder = 9
      OnClick = Button_RS485Click
    end
    object Button_lightCtrl: TButton
      Left = 216
      Top = 56
      Width = 75
      Height = 25
      Caption = #24378#21046#25511#28783
      Enabled = False
      TabOrder = 10
      OnClick = Button_lightCtrlClick
    end
    object Button_getDevTime: TButton
      Left = 216
      Top = 120
      Width = 75
      Height = 25
      Caption = #33719#21462#26102#38388
      Enabled = False
      TabOrder = 11
      OnClick = Button_getDevTimeClick
    end
    object Button_syncTime: TButton
      Left = 216
      Top = 152
      Width = 75
      Height = 25
      Caption = #26102#38388#21516#27493
      Enabled = False
      TabOrder = 12
      OnClick = Button_syncTimeClick
    end
  end
  object ListBoxInfo: TListBox
    Left = 840
    Top = 376
    Width = 321
    Height = 297
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 7
  end
  object ListView_IP: TListView
    Left = 840
    Top = 56
    Width = 241
    Height = 105
    Columns = <>
    GridLines = True
    ReadOnly = True
    TabOrder = 8
    ViewStyle = vsReport
    OnClick = ListView_IPClick
    OnMouseUp = ListView_IPMouseUp
  end
  object ListView_SpaceInfo: TListView
    Left = 24
    Top = 452
    Width = 793
    Height = 221
    Columns = <>
    GridLines = True
    ReadOnly = True
    TabOrder = 9
    ViewStyle = vsReport
  end
  object MainMenu1: TMainMenu
    Top = 8
    object N1: TMenuItem
      Caption = #36873#39033
      object N2: TMenuItem
        Caption = #35774#22791#25628#32034
        OnClick = N2Click
      end
    end
  end
end
