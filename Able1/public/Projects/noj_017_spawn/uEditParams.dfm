object frmEditParams: TfrmEditParams
  Left = 277
  Top = 165
  Width = 696
  Height = 480
  Caption = 'Extended Parameters'
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 688
    Height = 398
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 337
      Top = 1
      Width = 3
      Height = 396
      Cursor = crHSplit
    end
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 336
      Height = 396
      Align = alLeft
      TabOrder = 0
      object Splitter2: TSplitter
        Left = 221
        Top = 42
        Width = 3
        Height = 353
        Cursor = crHSplit
        Align = alRight
      end
      object Panel5: TPanel
        Left = 1
        Top = 1
        Width = 334
        Height = 41
        Align = alTop
        Caption = 'Parameter Template (from EXE)'
        TabOrder = 0
      end
      object memExeTemplate: TMemo
        Left = 1
        Top = 42
        Width = 220
        Height = 353
        Align = alClient
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'memExeTemplate')
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object Panel4: TPanel
        Left = 224
        Top = 42
        Width = 111
        Height = 353
        Align = alRight
        TabOrder = 2
        object btnCloneTemplate: TButton
          Left = 16
          Top = 48
          Width = 75
          Height = 25
          Caption = '>>'
          TabOrder = 0
        end
        object BitBtn1: TBitBtn
          Left = 16
          Top = 96
          Width = 75
          Height = 25
          TabOrder = 1
          Kind = bkOK
        end
        object BitBtn2: TBitBtn
          Left = 16
          Top = 144
          Width = 75
          Height = 25
          TabOrder = 2
          Kind = bkCancel
        end
      end
    end
    object Panel3: TPanel
      Left = 340
      Top = 1
      Width = 347
      Height = 396
      Align = alClient
      TabOrder = 1
      object memParamEdit: TMemo
        Left = 1
        Top = 42
        Width = 345
        Height = 353
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'memParamEdit')
        ParentFont = False
        TabOrder = 0
      end
      object Panel6: TPanel
        Left = 1
        Top = 1
        Width = 345
        Height = 41
        Align = alTop
        Caption = 'Extended Parameters (edit)'
        TabOrder = 1
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 688
    Height = 29
    Caption = 'ToolBar1'
    TabOrder = 1
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 427
    Width = 688
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object ActionList1: TActionList
    Left = 624
    Top = 8
  end
end
