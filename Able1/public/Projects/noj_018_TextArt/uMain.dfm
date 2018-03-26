object frmMain: TfrmMain
  Left = 328
  Top = 180
  Width = 597
  Height = 480
  Caption = 'Text Art'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -20
  Font.Name = 'Courier'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 20
  object Splitter1: TSplitter
    Left = 185
    Top = 0
    Width = 3
    Height = 408
    Cursor = crHSplit
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 408
    Width = 589
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Panel2: TPanel
    Left = 188
    Top = 0
    Width = 401
    Height = 408
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    TabOrder = 1
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 397
      Height = 73
      Align = alTop
      TabOrder = 0
      object Image1: TImage
        Left = 1
        Top = 1
        Width = 395
        Height = 71
        Align = alClient
        AutoSize = True
        Center = True
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 73
      Width = 397
      Height = 331
      Align = alClient
      BevelWidth = 6
      BorderStyle = bsSingle
      TabOrder = 1
      object PaintBox1: TPaintBox
        Left = 6
        Top = 6
        Width = 381
        Height = 315
        Align = alClient
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clGreen
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
        PopupMenu = popImageTools
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 408
    Align = alLeft
    TabOrder = 2
    object Splitter2: TSplitter
      Left = 1
      Top = 313
      Width = 183
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 183
      Height = 312
      Align = alTop
      TabOrder = 0
      object GroupBox1: TGroupBox
        Left = 16
        Top = 8
        Width = 137
        Height = 177
        Caption = ' Sheet '
        TabOrder = 0
        object SpeedButton1: TSpeedButton
          Left = 66
          Top = 35
          Width = 23
          Height = 22
        end
        object SpeedButton2: TSpeedButton
          Left = 24
          Top = 35
          Width = 23
          Height = 22
        end
        object Label1: TLabel
          Left = 64
          Top = 72
          Width = 48
          Height = 20
          Caption = 'wide'
        end
        object Label2: TLabel
          Left = 64
          Top = 104
          Width = 48
          Height = 20
          Caption = 'high'
        end
        object edWidth: TEdit
          Left = 24
          Top = 72
          Width = 33
          Height = 28
          TabOrder = 0
          Text = '80'
        end
        object edHeight: TEdit
          Left = 24
          Top = 104
          Width = 33
          Height = 28
          TabOrder = 1
          Text = '25'
        end
        object CheckBox1: TCheckBox
          Left = 24
          Top = 144
          Width = 97
          Height = 17
          Caption = 'Grid'
          TabOrder = 2
        end
      end
      object GroupBox2: TGroupBox
        Left = 16
        Top = 216
        Width = 113
        Height = 73
        Caption = ' Sel '
        TabOrder = 1
        object SpeedButton3: TSpeedButton
          Left = 66
          Top = 35
          Width = 23
          Height = 22
        end
        object SpeedButton4: TSpeedButton
          Left = 24
          Top = 35
          Width = 23
          Height = 22
        end
      end
    end
    object ListBox1: TListBox
      Left = 1
      Top = 316
      Width = 183
      Height = 91
      Align = alClient
      ItemHeight = 20
      PopupMenu = popArtLoader
      TabOrder = 1
    end
  end
  object MainMenu1: TMainMenu
    Left = 208
    Top = 24
    object Picture1: TMenuItem
      Caption = '&Picture'
      object actRefreshGrid1: TMenuItem
        Action = actRefreshGrid
      end
      object actRefreshText1: TMenuItem
        Action = actRefreshText
      end
    end
    object Tools1: TMenuItem
      Caption = '&Tools'
    end
  end
  object ActionList1: TActionList
    Left = 304
    Top = 24
    object actRefreshGrid: TAction
      Category = 'Picture'
      Caption = 'actRefreshGrid'
    end
    object actRefreshText: TAction
      Category = 'Picture'
      Caption = 'actRefreshText'
    end
    object actToolText: TAction
      Category = 'ClickTools'
      Caption = 'actToolText'
    end
  end
  object ImageList1: TImageList
    Left = 256
    Top = 24
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 344
    Top = 24
  end
  object popImageTools: TPopupMenu
    Left = 216
    Top = 96
  end
  object popArtLoader: TPopupMenu
    Left = 88
    Top = 344
  end
end
