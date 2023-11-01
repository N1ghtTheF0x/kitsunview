#include <N1ghtTheF0x/Kitsunview/Window.hpp>

#define THIS_HINSTANCE (HINSTANCE)GetModuleHandle(NULL)
#define EXIT_ERROR(title,content) \
    { MessageBox(NULL,title,content,MB_OK); \
    exit(EXIT_FAILURE); }

inline N1ghtTheF0x::Kitsunview::Window::StateInfo *GetAppState(HWND handle)
{
    LONG_PTR ptr = GetWindowLongPtr(handle,GWLP_USERDATA);
    N1ghtTheF0x::Kitsunview::Window::StateInfo *state = reinterpret_cast<N1ghtTheF0x::Kitsunview::Window::StateInfo*>(ptr);
    return state;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    N1ghtTheF0x::Kitsunview::Window::StateInfo *state; 
    if(uMsg == WM_CREATE)
    {
        CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT*>(lParam);
        state = reinterpret_cast<N1ghtTheF0x::Kitsunview::Window::StateInfo*>(create->lpCreateParams);
        SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)state);
    } else state = GetAppState(hwnd);
    switch(uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd,&ps);

            FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));

            EndPaint(hwnd,&ps);
            return 0;
        }
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
            return 0;
        }
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

namespace N1ghtTheF0x
{
    namespace Kitsunview
    {
        Window::Window(LibKitsune::String title): Window(title,CW_USEDEFAULT,CW_USEDEFAULT)
        {

        }
        Window::Window(LibKitsune::String title,s32 width,s32 height): Window(title,CW_USEDEFAULT,CW_USEDEFAULT,width,height)
        {

        }
        Window::Window(LibKitsune::String title,s32 x,s32 y,s32 width,s32 height)
        {
            LibKitsune::String class_name = "KitsunView-";
            class_name.append(title);

            WNDCLASS wc = { };
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = THIS_HINSTANCE;
            wc.lpszClassName = class_name;

            if(!RegisterClass(&wc))
                EXIT_ERROR("KitsunView Error","Couldn't RegisterClass(&wc)")
            
            StateInfo *state = new StateInfo;
            if(state == NULL)
                EXIT_ERROR("KitsunView Error","Couldn't new StateInfo")
            state->window = this;

            _handle = CreateWindowEx(0,class_name,title,WS_OVERLAPPEDWINDOW,x,y,width,height,NULL,NULL,THIS_HINSTANCE,state);
            if(_handle == NULL)
                EXIT_ERROR("KitsunView Error","Couldn't CreateWindowEx")
            show();
        }
        void Window::show() const
        {
            if(_handle == NULL)
                return;
            ShowWindow(_handle,SW_SHOW);
        }
        void Window::hide() const
        {
            if(_handle == NULL)
                return;
            ShowWindow(_handle,SW_SHOW);
        }
        void Window::_pull_events()
        {
            MSG msg = { };
            _running = GetMessage(&msg,NULL,0,0) > 0;
            while(_running)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}