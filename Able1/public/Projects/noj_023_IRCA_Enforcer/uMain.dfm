object frmMain: TfrmMain
  Left = 337
  Top = 218
  Width = 562
  Height = 399
  Caption = 'Maintain IRCA Page Headers'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 554
    Height = 365
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 186
      Top = 30
      Width = 3
      Height = 315
      Cursor = crHSplit
    end
    object Panel2: TPanel
      Left = 1
      Top = 30
      Width = 185
      Height = 315
      Align = alLeft
      TabOrder = 0
      object Splitter2: TSplitter
        Left = 1
        Top = 137
        Width = 183
        Height = 3
        Cursor = crVSplit
        Align = alTop
      end
      object ListBox1: TListBox
        Left = 1
        Top = 169
        Width = 183
        Height = 145
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
      object Panel4: TPanel
        Left = 1
        Top = 1
        Width = 183
        Height = 136
        Align = alTop
        TabOrder = 1
        object lblSite: TLabel
          Left = 24
          Top = 24
          Width = 28
          Height = 13
          Caption = 'lblSite'
        end
        object lblFolder: TLabel
          Left = 24
          Top = 64
          Width = 39
          Height = 13
          Caption = 'lblFolder'
        end
        object lblFiles: TLabel
          Left = 24
          Top = 104
          Width = 31
          Height = 13
          Caption = 'lblFiles'
        end
        object StaticText1: TStaticText
          Left = 8
          Top = 8
          Width = 41
          Height = 17
          Caption = 'Site:'
          TabOrder = 0
        end
        object StaticText2: TStaticText
          Left = 8
          Top = 48
          Width = 36
          Height = 17
          Caption = 'Folder:'
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Left = 8
          Top = 88
          Width = 55
          Height = 17
          Caption = 'File Types:'
          TabOrder = 2
        end
      end
      object ToolBar3: TToolBar
        Left = 1
        Top = 140
        Width = 183
        Height = 29
        Caption = 'ToolBar3'
        TabOrder = 2
        object ToolButton11: TToolButton
          Left = 0
          Top = 2
          Width = 8
          Caption = 'ToolButton11'
          Style = tbsSeparator
        end
        object ToolButton12: TToolButton
          Left = 8
          Top = 2
          Action = actSiteInfoCreate
        end
        object ToolButton13: TToolButton
          Left = 31
          Top = 2
          Width = 8
          Caption = 'ToolButton13'
          ImageIndex = 0
          Style = tbsSeparator
        end
        object ToolButton14: TToolButton
          Left = 39
          Top = 2
          Action = actSiteInfoEdit
        end
        object ToolButton15: TToolButton
          Left = 62
          Top = 2
          Width = 8
          Caption = 'ToolButton15'
          ImageIndex = 1
          Style = tbsSeparator
        end
        object ToolButton16: TToolButton
          Left = 70
          Top = 2
          Action = actSiteInfoDelete
        end
      end
    end
    object Panel3: TPanel
      Left = 189
      Top = 30
      Width = 364
      Height = 315
      Align = alClient
      TabOrder = 1
      object ToolBar2: TToolBar
        Left = 1
        Top = 1
        Width = 362
        Height = 29
        Caption = 'ToolBar2'
        TabOrder = 0
        object ToolButton7: TToolButton
          Left = 0
          Top = 2
          Width = 8
          Caption = 'ToolButton7'
          Style = tbsSeparator
        end
        object ToolButton8: TToolButton
          Left = 8
          Top = 2
          Action = actCheckSite
        end
        object ToolButton9: TToolButton
          Left = 31
          Top = 2
          Width = 8
          Caption = 'ToolButton9'
          ImageIndex = 0
          Style = tbsSeparator
        end
        object ToolButton10: TToolButton
          Left = 39
          Top = 2
          Action = actProcessSite
        end
        object ToolButton17: TToolButton
          Left = 62
          Top = 2
          Width = 8
          Caption = 'ToolButton17'
          ImageIndex = 0
          Style = tbsSeparator
        end
        object ToolButton18: TToolButton
          Left = 70
          Top = 2
          Action = actEditIrcaTemplate
        end
      end
      object memReport: TMemo
        Left = 1
        Top = 30
        Width = 362
        Height = 284
        Align = alClient
        Lines.Strings = (
          'memReport')
        TabOrder = 1
      end
    end
    object ToolBar1: TToolBar
      Left = 1
      Top = 1
      Width = 552
      Height = 29
      Caption = 'ToolBar1'
      TabOrder = 2
      object ToolButton1: TToolButton
        Left = 0
        Top = 2
        Width = 8
        Caption = 'ToolButton1'
        Style = tbsSeparator
      end
      object ToolButton2: TToolButton
        Left = 8
        Top = 2
        Caption = 'ToolButton2'
      end
      object ToolButton3: TToolButton
        Left = 31
        Top = 2
        Width = 8
        Caption = 'ToolButton3'
        ImageIndex = 0
        Style = tbsSeparator
      end
      object ToolButton4: TToolButton
        Left = 39
        Top = 2
        Caption = 'ToolButton4'
        ImageIndex = 0
      end
      object ToolButton5: TToolButton
        Left = 62
        Top = 2
        Width = 8
        Caption = 'ToolButton5'
        ImageIndex = 1
        Style = tbsSeparator
      end
      object ToolButton6: TToolButton
        Left = 70
        Top = 2
        Caption = 'ToolButton6'
        ImageIndex = 1
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 345
      Width = 552
      Height = 19
      Panels = <>
      SimplePanel = False
    end
  end
  object ActionList1: TActionList
    Left = 480
    Top = 48
    object actSiteInfoCreate: TAction
      Category = 'SiteInfo'
      Caption = 'actSiteInfoCreate'
      Hint = 'Create Site Info'
    end
    object actSiteInfoDelete: TAction
      Category = 'SiteInfo'
      Caption = 'actSiteInfoDelete'
      Hint = 'Delete Selected Site Info'
    end
    object actSiteInfoEdit: TAction
      Category = 'SiteInfo'
      Caption = 'actSiteInfoEdit'
      Hint = 'Edit Selected Site Info'
    end
    object actCheckSite: TAction
      Category = 'SiteProcessing'
      Caption = 'actCheckSite'
      Hint = 'Check Headers for Site Info'
    end
    object actProcessSite: TAction
      Category = 'SiteProcessing'
      Caption = 'actProcessSite'
      Hint = 'Enforce Site Headers'
    end
    object actEditIrcaTemplate: TAction
      Category = 'Templates'
      Caption = 'actEditIrcaTemplate'
      Hint = 'Edit IRCA Header Template'
    end
  end
end
