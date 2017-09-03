#ifndef SUFOFUNCTIONS_H
#define SUFOFUNCTIONS_H

#include <wx/tokenzr.h>
#include <wx/textfile.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h> // for function XGetPixel();
#include <X11/keysym.h>

//#include <sys/types.h>
//#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

// structures
struct GameCase {
    int x;
    int y;
    unsigned short red;
    unsigned short blue;
    unsigned short green;
};

// prototypes
Window *list (Display *disp, unsigned long *len);
char *name (Display *disp, Window win);
void mouseClick(Display *display, int button, Window win);
void mouseCoords(Display *display, Window root, int *x, int *y);
void moveMouse(Display* display, Window root, int x, int y);
void mouseMoveAndLeftClick(Display *display, Window win, int x, int y);
void AppendToLogAndConsole(wxString msg, wxTextCtrl* txtConsole);
void AppendToIALog(wxString msg);
XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers);
void pressKey(Display* display, Window root, Window gameWindow, wxString keyToPress);
bool checkInternetConnection();
void setWindowOntop(Display* display, Window w, int windowState);
void getPixelColor(Display *d, int x, int y, XColor *color);
bool checkPixelColor(Display* display, GameCase btn);
bool checkColorsSimilarity(XColor c1, int c2Red, int c2Blue, int c2Green, int maxDifference);

#endif
