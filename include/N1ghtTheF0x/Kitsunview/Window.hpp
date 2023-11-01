#ifndef __N1GHTTHEF0X_KITSUNVIEW_WINDOW_HPP
#define __N1GHTTHEF0X_KITSUNVIEW_WINDOW_HPP

#ifdef _WIN32
    #include <windows.h>
#endif

#include <N1ghtTheF0x/LibKitsune/String.hpp>

namespace N1ghtTheF0x
{
    namespace Kitsunview
    {
        class Window
        {
        private:
            bool _running = false;
#ifdef _WIN32
            HWND _handle;
        public:
            Window(LibKitsune::String title);
            struct StateInfo
            {
                Window *window;
            };
#endif
        private: // OS specific
            void _pull_events();
        public:
            Window(LibKitsune::String title,s32 width,s32 height);
            Window(LibKitsune::String title,s32 x,s32 y,s32 width,s32 height);
            void show() const;
            void hide() const;
        public: // non-OS specific
            bool running() const;
        };
    }
}

#endif