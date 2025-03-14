#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "convert.h"
#include "FileCreater.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              
        CLASS_NAME,                     
        L"Convert Image",    
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        GetSystemMetrics(SM_CXSCREEN)/2-160, GetSystemMetrics(SM_CYSCREEN)/2-120, 300, 200,
        NULL,          
        NULL,       
        hInstance,  
        NULL       
        );
    
    HWND button_post_image = CreateWindowAll(L"button", L"Post", WS_VISIBLE | WS_CHILD, 10, 10, 100, 50, hwnd, (HMENU)btn_post);
    HWND button_get_image = CreateWindowAll(L"button", L"Get", WS_VISIBLE | WS_CHILD, 170, 10, 100, 50, hwnd, (HMENU)btn_get);
    HWND buttotext_fieldn_get_image = CreateWindowAll(L"STATIC", L"Welcome", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 140, 300, 20, hwnd, (HMENU)status_bar);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == btn_post)
        {
            strcpy(filepath, CreateDialogBoxOpen(hwnd));

            image = cv::imread(filepath);

            show_image_();

            SetDlgItemText(hwnd, status_bar, L"upload successful");
        }
        if (LOWORD(wParam) == btn_get)
        {
            strcpy(filepath, CreateDialogBoxSave(hwnd, (char*)"output.png"));

            std::vector<int> compression_params;
            compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
            compression_params.push_back(9);
            cv::imwrite(filepath, image, compression_params);

            SetDlgItemText(hwnd, status_bar, L"save successful");
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        cv::destroyAllWindows();
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int main()
{
    //you can leave it empty
    return 0;
}


void show_image_()
{
    cv::imshow("image", image);
    cv::waitKey(-1);  
}
