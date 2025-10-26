; Inno Setup Script for Video Frame Extractor Pro
; Generated for Mehmet Yüksel Şekeroğlu
; MIT License - https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx

#define MyAppName "Video Frame Extractor Pro"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Mehmet Yüksel Şekeroğlu"
#define MyAppURL "https://github.com/MehmetYukselSekeroglu/VideoFrameExtractorCxx"
#define MyAppExeName "VideoFrameExtractor.exe"
#define MyAppIcon "app_icon.ico"

[Setup]
; Basic Setup Information
AppId={{115e5a37-cdfe-423b-b9e0-2780291c70c1}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
AppCopyright=Copyright © 2025 {#MyAppPublisher}. MIT License.

; Directory Settings
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
DisableProgramGroupPage=auto

; Output Configuration
OutputBaseFilename=VideoFrameExtractorPro_Setup
Compression=lzma2/max
SolidCompression=yes
SetupIconFile=app_icon.ico
WizardStyle=modern

; License Information
LicenseFile=LICENSE.txt

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 6.1

[Files]
; Main Application
Source: "VideoFrameExtractor.exe"; DestDir: "{app}"; Flags: ignoreversion

; Application Icon
Source: "app_icon.ico"; DestDir: "{app}"; Flags: ignoreversion

; OpenCV Libraries
Source: "opencv_world4120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "opencv_videoio_ffmpeg4120_64.dll"; DestDir: "{app}"; Flags: ignoreversion

; Qt Core Libraries
Source: "Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Pdf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion

; System Dependencies
Source: "D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion

; Qt Plugins
Source: "platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "networkinformation\*"; DestDir: "{app}\networkinformation"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "tls\*"; DestDir: "{app}\tls"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "generic\*"; DestDir: "{app}\generic"; Flags: ignoreversion recursesubdirs createallsubdirs

; License File
Source: "LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppIcon}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\{#MyAppIcon}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon; IconFilename: "{app}\{#MyAppIcon}"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent