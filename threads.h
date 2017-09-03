#ifndef SUFOTHREADS_H
#define SUFOTHREADS_H

#include <wx/thread.h>
//#include <X11/Xlib.h>
#include "bot.h"

// MousePosition thread class

class MousePosition : public wxThread
{
    public:
        MousePosition(wxTextCtrl*, wxTextCtrl*, wxCheckBox*);
    private:
        void* Entry(); // the entry point to the thread
        void OnExit();
        wxString Mx, My;
        wxTextCtrl* txtX;
        wxTextCtrl* txtY;
        wxCheckBox* getMousePoscheck;
};

// Bot thread class

class BotThread : public wxThread
{
    public:
        BotThread(wxString, Display*, Window, int, int, wxButton*, wxButton*, wxTextCtrl*, bool, int*, bool, wxString);
    private:
        void* Entry(); // the entry point to the thread
        void OnExit();
        wxString trajetPath;
        Display* display;
        Window gameWindow;
        int gameWidth, gameHeight;
        wxButton* lancerBtn;
        wxButton* stopBtn;
        wxTextCtrl* txtConsole;
        bool keepMouse;
        bool isConnected;
        bool forcedStop;
        int* repriseIndex;
        bool repeterTrajet;
        wxString optionsCoMeFile;
};

// Simuler Combat Thread

class SimulerCombatThread : public wxThread
{
    public:
        SimulerCombatThread(wxButton*, int, int, Display*, Window, Window, wxString, wxTextCtrl*);
    private:
        void* Entry(); // the entry point to the thread
        void OnExit();
        wxButton* simulerCombatBtn;
        int gameWidth;
        int gameHeight;
        Display* display;
        Window gameWindow;
        Window root;
        wxString optionsCoMeFile;
        wxTextCtrl* txtConsole;
};

#endif
