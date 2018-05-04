object Form1: TForm1
  Left = 381
  Top = 154
  Width = 579
  Height = 579
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 8
    Top = 8
    Width = 449
    Height = 89
    Caption = #35774#22791#21442#25968
    TabOrder = 0
    object Label8: TLabel
      Left = 16
      Top = 24
      Width = 72
      Height = 13
      Caption = #35774#22791#32034#24341#21495#65306
    end
    object Label2: TLabel
      Left = 20
      Top = 56
      Width = 72
      Height = 13
      Caption = #26381#21153#22120#31471#21475#65306
    end
    object Edit3: TEdit
      Left = 106
      Top = 51
      Width = 71
      Height = 21
      TabOrder = 0
      Text = '4001'
    end
    object Button1: TButton
      Left = 363
      Top = 56
      Width = 75
      Height = 25
      Caption = #36830#25509
      TabOrder = 1
      OnClick = Button1Click
    end
    object ComboBox1: TComboBox
      Left = 106
      Top = 27
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7')
    end
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 114
    Width = 449
    Height = 89
    Caption = ' '#21457#36865#25968#25454#24103' '
    TabOrder = 1
    object Label4: TLabel
      Left = 16
      Top = 24
      Width = 48
      Height = 13
      Caption = #24103#31867#22411#65306
    end
    object Label5: TLabel
      Left = 144
      Top = 24
      Width = 48
      Height = 13
      Caption = #24103#26684#24335#65306
    end
    object Label6: TLabel
      Left = 272
      Top = 24
      Width = 35
      Height = 13
      Caption = #24103'ID'#65306
    end
    object Label7: TLabel
      Left = 16
      Top = 56
      Width = 36
      Height = 13
      Caption = #25968#25454#65306
    end
    object ComboBox6: TComboBox
      Left = 64
      Top = 20
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      Items.Strings = (
        #26631#20934#24103
        #25193#23637#24103)
    end
    object ComboBox7: TComboBox
      Left = 192
      Top = 20
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      Items.Strings = (
        #25968#25454#24103
        #36828#31243#24103)
    end
    object Edit1: TEdit
      Left = 312
      Top = 20
      Width = 73
      Height = 21
      TabOrder = 2
      Text = '00000080'
    end
    object Edit4: TEdit
      Left = 56
      Top = 53
      Width = 193
      Height = 21
      TabOrder = 3
      Text = '01 02 03 04 05 06 07 08 '
    end
    object Button4: TButton
      Left = 272
      Top = 51
      Width = 75
      Height = 25
      Caption = #21457#36865
      TabOrder = 4
      OnClick = Button4Click
    end
  end
  object GroupBox6: TGroupBox
    Left = 8
    Top = 216
    Width = 545
    Height = 137
    Caption = #20449#24687
    TabOrder = 2
    object ListBox1: TListBox
      Left = 8
      Top = 16
      Width = 529
      Height = 113
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 384
    Width = 545
    Height = 145
    Caption = #36830#25509#21040#26412#26426#26381#21153#22120#30340#23458#25143#31471#20449#24687
    TabOrder = 3
    object ListBox2: TListBox
      Left = 8
      Top = 24
      Width = 361
      Height = 113
      ItemHeight = 13
      TabOrder = 0
    end
    object Button2: TButton
      Left = 392
      Top = 112
      Width = 75
      Height = 25
      Caption = #26029#24320#36830#25509
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 512
    Top = 408
  end
end
