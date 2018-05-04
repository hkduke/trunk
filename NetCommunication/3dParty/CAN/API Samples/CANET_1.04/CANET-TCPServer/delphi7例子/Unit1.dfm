object Form1: TForm1
  Left = 229
  Top = 147
  Width = 588
  Height = 536
  Caption = 'Form1'
  Color = clBtnFace
  DragKind = dkDock
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object GroupBox2: TGroupBox
    Left = 8
    Top = 16
    Width = 457
    Height = 81
    Caption = #35774#22791#21442#25968
    TabOrder = 3
    object Label8: TLabel
      Left = 16
      Top = 24
      Width = 72
      Height = 12
      Caption = #35774#22791#32034#24341#21495#65306
    end
    object Label2: TLabel
      Left = 18
      Top = 53
      Width = 72
      Height = 12
      Caption = #26381#21153#22120#31471#21475#65306
    end
    object Edit3: TEdit
      Left = 103
      Top = 48
      Width = 132
      Height = 20
      TabOrder = 0
      Text = '4001'
    end
  end
  object ComboBox1: TComboBox
    Left = 112
    Top = 35
    Width = 65
    Height = 20
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#24494#36719#25340#38899
    ItemHeight = 12
    TabOrder = 0
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '')
  end
  object Button1: TButton
    Left = 344
    Top = 64
    Width = 97
    Height = 25
    Caption = #21551#21160#26381#21153#22120
    TabOrder = 1
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 112
    Width = 457
    Height = 81
    Caption = ' '#21457#36865#25968#25454#24103' '
    TabOrder = 2
    object Label4: TLabel
      Left = 16
      Top = 24
      Width = 48
      Height = 12
      Caption = #24103#31867#22411#65306
    end
    object Label5: TLabel
      Left = 152
      Top = 24
      Width = 48
      Height = 12
      Caption = #24103#26684#24335#65306
    end
    object Label6: TLabel
      Left = 288
      Top = 24
      Width = 36
      Height = 12
      Caption = #24103'ID'#65306
    end
    object Label7: TLabel
      Left = 16
      Top = 56
      Width = 36
      Height = 12
      Caption = #25968#25454#65306
    end
    object Button5: TButton
      Left = 272
      Top = 49
      Width = 57
      Height = 24
      Caption = #21457#36865
      TabOrder = 0
      OnClick = Button5Click
    end
    object ComboBox6: TComboBox
      Left = 64
      Top = 19
      Width = 81
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 1
      Items.Strings = (
        #26631#20934#24103
        #25193#23637#24103)
    end
    object ComboBox7: TComboBox
      Left = 200
      Top = 19
      Width = 81
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 2
      Items.Strings = (
        #25968#25454#24103
        #36828#31243#24103)
    end
    object Edit1: TEdit
      Left = 328
      Top = 19
      Width = 73
      Height = 20
      TabOrder = 3
      Text = '00000080'
    end
    object Edit4: TEdit
      Left = 56
      Top = 51
      Width = 201
      Height = 20
      TabOrder = 4
      Text = '01 02 03 04 05 06 07 08 '
    end
  end
  object GroupBox6: TGroupBox
    Left = 8
    Top = 208
    Width = 561
    Height = 145
    Caption = #20449#24687
    TabOrder = 4
    object ListBox1: TListBox
      Left = 8
      Top = 16
      Width = 545
      Height = 121
      ItemHeight = 12
      TabOrder = 0
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 368
    Width = 561
    Height = 129
    Caption = #36830#25509#21040#26412#22320#26381#21153#22120#30340#36828#31243#23458#25143#31471
    TabOrder = 5
    object ListBoxClient: TListBox
      Left = 8
      Top = 24
      Width = 369
      Height = 97
      ItemHeight = 12
      TabOrder = 0
    end
    object Disconn: TButton
      Left = 416
      Top = 96
      Width = 75
      Height = 25
      Caption = #26029#24320#36830#25509
      TabOrder = 1
      OnClick = DisconnClick
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 488
    Top = 416
  end
end
