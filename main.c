#include <windows.h>
#include <stdio.h>

void ShowVersionInfoFileFlags(const wchar_t* filePath) {
    DWORD handle = 0;
    DWORD size = GetFileVersionInfoSizeW(filePath, &handle);

    if (size == 0) {
        wprintf(L"Error: Could not get the version info size for %ls\n", filePath);
        wprintf(L"Error code: 0x%08X\n", GetLastError());
        return;
    }

    BYTE* buffer = (BYTE*)malloc(size);
    if (buffer == NULL) {
        wprintf(L"Error: Memory allocation failed\n");
        return;
    }

    if (!GetFileVersionInfoW(filePath, handle, size, buffer)) {
        wprintf(L"Error: Could not get the version info\n");
        wprintf(L"Error code: 0x%08X\n", GetLastError());
        free(buffer);
        return;
    }

    VS_FIXEDFILEINFO* fileInfo = NULL;
    UINT infoSize = 0;

    if (!VerQueryValueW(buffer, L"\\", (LPVOID*)&fileInfo, &infoSize)) {
        wprintf(L"Error: Could not query the version info\n");
        free(buffer);
        return;
    }

    DWORD fileFlagsMask = fileInfo->dwFileFlagsMask;
    DWORD fileFlags = fileInfo->dwFileFlags;

    wprintf(L"FileFlagsMask: 0x%08X\n", fileFlagsMask);
    wprintf(L"FileFlags:     0x%08X\n", fileFlags);
    #define SHOW_FILE_FLAG(flag, name) \
        wprintf(L"  %-18ls 0x%02X %ls%ls\n", \
            name, \
            flag, \
            (fileFlags & flag) ? L"[X]" : L"[ ]", \
            (fileFlagsMask & flag) ? L"" : L" [IGNORED]");
    SHOW_FILE_FLAG(VS_FF_DEBUG, L"VS_FF_DEBUG");
    SHOW_FILE_FLAG(VS_FF_PRERELEASE, L"VS_FF_PRERELEASE");
    SHOW_FILE_FLAG(VS_FF_PATCHED, L"VS_FF_PATCHED");
    SHOW_FILE_FLAG(VS_FF_PRIVATEBUILD, L"VS_FF_PRIVATEBUILD");
    SHOW_FILE_FLAG(VS_FF_INFOINFERRED, L"VS_FF_INFOINFERRED");
    SHOW_FILE_FLAG(VS_FF_SPECIALBUILD, L"VS_FF_SPECIALBUILD");

    free(buffer);
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) {
        wprintf(L"Usage: show-version-info-file-flags.exe <file.exe>\n");
        wprintf(L"Example: show-version-info-file-flags.exe C:\\Windows\\System32\\notepad.exe\n");
        return 1;
    }

    ShowVersionInfoFileFlags(argv[1]);

    return 0;
}
