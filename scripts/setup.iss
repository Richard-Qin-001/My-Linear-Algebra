#define MyAppName "My Linear Algebra"
#define MyAppVersion "0.2.0"
#define MyAppPublisher "Richard Qin"
#define MyAppURL "https://github.com/Richard-Qin-001/My-Linear-Algebra"
#define MyAppExeName "MyLinearAlgebraApp.exe"

[Setup]
AppId={{A1B2C3D4-E5F6-7890-ABCD-EF1234567890}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=..\LICENSE
OutputDir=output
OutputBaseFilename=MyLinearAlgebra-Setup
SetupIconFile=..\resources\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "chinesesimplified"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\bin\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName} (CLI Mode)"; Filename: "{app}\{#MyAppExeName}"; Parameters: ""
Name: "{group}\{#MyAppName} (GUI Mode)"; Filename: "{app}\{#MyAppExeName}"; Parameters: "gui"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{autodesktop}\{#MyAppName} (CLI)"; Filename: "{app}\{#MyAppExeName}"; Parameters: ""; Tasks: desktopicon
Name: "{autodesktop}\{#MyAppName} (GUI)"; Filename: "{app}\{#MyAppExeName}"; Parameters: "gui"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Parameters: "gui"; Description: "Launch {#MyAppName} (GUI Mode)"; Flags: nowait postinstall skipifsilent