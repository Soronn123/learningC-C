#include "FileCreater.h"


HWND CreateWindowAll(const wchar_t type_[], const wchar_t name_[], DWORD style_, int x, int y, int w, int h, HWND hwnd, HMENU id)
{
    HWND button_;
    button_ = CreateWindow(
        type_, 
        name_,
        style_,
        x, y, w, h,
        hwnd,
        id,
        NULL,
        NULL);
    return button_;
}


void ErorrMessage(char* where_, char* what_)
{
    char msg[70];
    strcpy(msg, where_);
    strcpy(msg, " : ");
    strcpy_s(msg, what_);
    MessageBoxA(NULL, msg, "ERROR", MB_OK);
}


char* CreateDialogBoxOpen(HWND hwnd)
{
    try
    {
        OPENFILENAMEA ofn; 
        char szFile[260];

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = 
                "Image files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0"
                "All files\0*.*\0";;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if (GetOpenFileNameA(&ofn) == TRUE){ return szFile; }
    }
    catch(...)
    {
        ErorrMessage((char*)"CreateDialogBoxOpen", (char*)"Ne znau");
    }
    return (char*)"Xd";
}


char* CreateDialogBoxSave(HWND hwnd, char*filepath)
{
    try
    {
        OPENFILENAMEA ofn; 
        char szFile[260];
        strcpy(szFile, filepath);

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = 
                "Image files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0"
                "All files\0*.*\0";;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if (GetSaveFileNameA(&ofn) == TRUE){ return szFile; }
    }
    catch(...)
    {
        ErorrMessage((char*)"CreateDialogBoxSave", (char*)"Ne znau");
    }
    return (char*)"Xd";
}