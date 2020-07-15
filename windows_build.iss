; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define IconName "chess.ico"
#define OutputDir "release"
#define SourcePath "C:\projects\chesspgnreviser"
#define BuildPath "C:\projects\chesspgnreviser\release"
#define MyAppName "Chess Pgn Reviser"
#define MyAppVersion "0.1.58"
#define MyAppPublisher "loloof64"
#define MyAppURL "https://github.com/loloof64/ChessPgnReviser"
#define MyAppExeName "ChessPgnReviser.exe"
#define MinGWBinPath "C:\msys64\mingw64\bin"

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
SetupIconFile="{#SourcePath}/{#IconName}"
Compression=lzma
SolidCompression=yes
WizardStyle=modern
ArchitecturesInstallIn64BitMode=x64
UninstallDisplayIcon="{#SourcePath}\{#IconName}"

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#BuildPath}\*"; DestDir: "{app}"; Flags: recursesubdirs
Source: "{#SourcePath}\{#IconName}"; DestDir: "{app}"


; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#IconName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#IconName}"; Tasks: desktopicon
