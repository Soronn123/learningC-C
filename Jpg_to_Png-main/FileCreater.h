#pragma once
#ifndef UNICODE
#define UNICODE
#endif 
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>


HWND CreateWindowAll(const wchar_t type_[], const wchar_t name_[], DWORD style_, int x, int y, int w, int h, HWND hwnd, HMENU id);
void ErorrMessage(char* where_, char* what_);
char* CreateDialogBoxOpen(HWND hwnd);
char* CreateDialogBoxSave(HWND hwnd, char*filepath);