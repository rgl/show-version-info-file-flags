# About

[![Build status](https://github.com/rgl/show-version-info-file-flags/workflows/Build/badge.svg)](https://github.com/rgl/show-version-info-file-flags/actions?query=workflow%3ABuild)

This shows a Windows executable [Version Info File Flags](https://learn.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource).

## Develop

Install [Chocolatey](https://chocolatey.org/install).

Install [MSYS2](https://community.chocolatey.org/packages/msys2):

```batch
choco install -y msys2 --params="'/NoPath'"
```

Execute the following commands in a MSYS2 `bash` session.

Install [GCC](https://packages.msys2.org/packages/mingw-w64-x86_64-gcc):

```bash
pacman --noconfirm -Sy mingw-w64-x86_64-gcc
```

Build and execute the application:

```bash
make
```

Show the other parts of the executable version info using PowerShell 7+:

```bash
# NB this command also returns the Version Info File Flags as the IsDebug,
#    IsPreRelease, IsPatched, IsPrivateBuild, and IsSpecialBuild properties.
#    thou, it does not return the VS_FF_INFOINFERRED flag.
pwsh -Command '(Get-Item show-version-info-file-flags.exe).VersionInfo | Format-List'
```

Show the other parts of the executable version info using [Resource Hacker](https://community.chocolatey.org/packages/reshack):

```bash
choco install -y reshack
'/C/Program Files (x86)/Resource Hacker/ResourceHacker.exe' \
    -open show-version-info-file-flags.exe \
    -save show-version-info-file-flags.exe.rc \
    -action extract \
    -mask 'VERSIONINFO,,'
cat show-version-info-file-flags.exe.rc
rm show-version-info-file-flags.exe.rc
```
