; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define QtInstallPath "C:\Qt\5.14.2"
#define IconName "chess.ico"
#define OutputDir "C:\Users\laure\Documents\Programmation\ProjetsPersos\Qt"
#define SourcePath "C:\Users\laure\Documents\Programmation\ProjetsPersos\Qt\ChessPgnReviser"
#define BuildPath "C:\Users\laure\Documents\Programmation\ProjetsPersos\Qt\build-ChessPgnReviser-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release"
#define MyAppName "Chess Pgn Reviser"
#define MyAppVersion "0.1.0"
#define MyAppPublisher "loloof64"
#define MyAppURL "https://github.com/loloof64/ChessPgnReviser"
#define MyAppExeName "ChessPgnReviser.exe"
#define MyAppIcoName "C:\Users\laure\Documents\Programmation\ProjetsPersos\Qt\ChessPgnReviser\chess.ico"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{8C5EDA8B-6DDC-458B-962B-95CFE21D1B7A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile="{#SourcePath}\LICENSE.txt"
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir="{#OutputDir}"
OutputBaseFilename=ChessPgnReviser
SetupIconFile="{#MyAppIcoName}"
Compression=lzma
SolidCompression=yes
WizardStyle=modern
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#BuildPath}\ChessPgnReviser.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#QtInstallPath}\msvc2017_64\plugins\platforms\*"; DestDir: "{app}\plugins\platforms"; Flags: ignoreversion
Source: "{#QtInstallPath}\msvc2017_64\plugins\imageformats\*"; DestDir: "{app}\plugins\imageformats"; Flags: ignoreversion
Source: "{#SourcePath}\chess.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#SourcePath}\resources\translations\ChessPgnReviser.en.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#SourcePath}\resources\translations\ChessPgnReviser.es.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#SourcePath}\resources\translations\ChessPgnReviser.fr.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#QtInstallPath}\msvc2017_64\bin\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion 
Source: "{#QtInstallPath}\msvc2017_64\bin\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#QtInstallPath}\msvc2017_64\bin\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#QtInstallPath}\msvc2017_64\bin\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#IconName}"; Tasks: desktopicon
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

