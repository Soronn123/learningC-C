#pragma once
#ifndef UNICODE
#define UNICODE
#endif 
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>
#include <windows.h>
#include <Shlwapi.h>
#include <opencv2/opencv.hpp>
#include <cstring>

#define btn_post 101
#define btn_get 102 
#define status_bar 103


cv::Mat image;
char filepath[260];


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void show_image_();


