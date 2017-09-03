#include "functions.h"

// functions to get all running window names

Window *list (Display *disp, unsigned long *len) {
    Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST",False), type;
    int form;
    unsigned long remain;
    unsigned char *list;

    if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,&type,&form,len,&remain,&list) != Success) {
        return 0;
    }

    return (Window*)list;
}

char *name (Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"WM_NAME",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;


    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,&type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (char*)list;
}

// function to simulate mouse click

void mouseClick(Display *display, int button, Window win)
{
    XEvent event;
    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, win, True, 0xfff, &event) == 0)
        fprintf(stderr, "Error cannot send press event !\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, win, True, 0xfff, &event) == 0)
        fprintf(stderr, "Error cannot send release event !\n");

    XFlush(display);
}

// Get mouse coordinates

void mouseCoords(Display *display, Window root, int *x, int *y)
{
    XEvent event;
    XQueryPointer (display, root, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    *x = event.xbutton.x;
    *y = event.xbutton.y;
}

// function that move mouse only

void moveMouse(Display* display, Window root, int x, int y)
{
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush (display);
}

// function that move mouse and left click

void mouseMoveAndLeftClick(Display *display, Window win, int x, int y)
{
    moveMouse(display, DefaultRootWindow(display), x, y);
    mouseClick(display, Button1, win);
}

// function append text to console and log file

void AppendToLogAndConsole(wxString msg, wxTextCtrl* txtConsole)
{
    // get date & time
    wxDateTime dt = wxDateTime::Now();
    // Create full msg string (include time ...)
    wxString strToApprend = _("[") + dt.FormatTime() + _("] - ") + msg;
    // Append To Console
    txtConsole->AppendText(strToApprend + _("\n"));
    wxMilliSleep(100); // on attend 100 millisecondes (pour éviter les crash)
    // Append To Log File
    wxTextFile file(dt.FormatISODate() + _(".txt"));
    if (file.Exists())
        file.Open();
    else
        file.Create();

    file.AddLine(strToApprend);
    file.Write();
    file.Close();
}

// function append text to IA log

void AppendToIALog(wxString msg)
{
    // get date & time
    wxDateTime dt = wxDateTime::Now();
    // Create full msg string (include time ...)
    wxString strToApprend = _("[") + dt.FormatTime() + _("] - ") + msg;
    // Append To Log File
    wxTextFile file(dt.FormatISODate() + _("_IA.txt"));
    if (file.Exists())
        file.Open();
    else
    {
        file.Create();
        file.AddLine(_("[IA Log]"));
    }

    file.AddLine(strToApprend);
    file.Write();
    file.Close();
}

// Function to create a keyboard event

XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}

// function to press key

void pressKey(Display* display, Window root, Window gameWindow, wxString keyToPress)
{
    KeySym keycode;
    XKeyEvent event;
    bool ctrlMod = false;

    if (keyToPress.Contains(_("+"))) // donc c'est un CTRL + ..
    {
        ctrlMod = true;
        // split by '+'
        wxStringTokenizer st2(keyToPress, _("+"));
        wxString ctrlStr = st2.GetNextToken();
        keyToPress = st2.GetNextToken();
    }

    if (ctrlMod)
    {
        keycode = XK_Control_L;
        // Send a fake key press event to the window.
        event = createKeyEvent(display, gameWindow, root, true, keycode, 0);
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
        XFlush(display);
    }

    // convert key to keySym/int
    if (keyToPress == _("ESC")) // si ECHAP, conversion manuelle
        keycode = XK_Escape;
    else
        keycode = XStringToKeysym(keyToPress.mb_str());

    // Send a fake key press event to the window.
    event = createKeyEvent(display, gameWindow, root, true, keycode, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    XFlush(display);

    // Send a fake key release event to the window.
    event = createKeyEvent(display, gameWindow, root, false, keycode, 0);
    XSendEvent(event.display, event.window, True, KeyReleaseMask, (XEvent *)&event);
    XFlush(display);

    if (ctrlMod)
    {
        // Send a fake key release event to the window.
        event = createKeyEvent(display, gameWindow, root, false, keycode, 0);
        XSendEvent(event.display, event.window, True, KeyReleaseMask, (XEvent *)&event);
        XFlush(display);
    }
}

// function to check internet connection

bool checkInternetConnection()
{
    struct addrinfo hints, *res, *p;
    int status, sockfd;
    char ipstr[INET6_ADDRSTRLEN];
    bool isConnected;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("www.google.com", "http", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return false;
    }

    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        //char *ipver;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET)
        { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            //ipver = "IPv4";
        }
        else
        { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            //ipver = "IPv6";
        }

        // convert the IP to a string
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
    {
        //printf("Connection error\n");
        isConnected = false;
    }
    else
    {
        //printf("Connection successful\n");
        isConnected = true;
    }

    close(sockfd);

    freeaddrinfo(res); // free the linked list

    return isConnected;
}

// function to show window on top

void setWindowOntop(Display* display, Window w, int windowState)
{
    Atom stateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
    XChangeProperty(display, w, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *) &stateAbove, 1);

    XEvent ev;
    ev.xclient.type = ClientMessage;
    ev.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
    ev.xclient.window = w;
    ev.xclient.format = 32;
    ev.xclient.data.l[0] = windowState;
    ev.xclient.data.l[1] = stateAbove;
    ev.xclient.data.l[2] = 0;
    ev.xclient.data.l[3] = 0;
    ev.xclient.data.l[4] = 0;

    XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &ev);
    XFlush(display);
}

// functions to get pixel color & check it

void getPixelColor(Display *d, int x, int y, XColor *color)
{
  XImage *image;
  image = XGetImage (d, RootWindow (d, DefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
  color->pixel = XGetPixel (image, 0, 0);
  XFree (image);
  XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), color);
}

bool checkPixelColor(Display* display, GameCase btn)
{
    XColor pixelColor;
    getPixelColor(display, btn.x, btn.y, &pixelColor);
    if (pixelColor.red/256 == btn.red && pixelColor.blue/256 == btn.blue && pixelColor.green/256 == btn.green)
        return true;
    else
        return false;
}

bool checkColorsSimilarity(XColor c1, int c2Red, int c2Blue, int c2Green, int maxDifference)
{
    // converting to correct RGB
    c1.red /= 256;
    c1.blue /= 256;
    c1.green /= 256;

    for (int i = 0; i <= maxDifference; i++)
    {
        // si la couleur rouge + différence (qui varie de 0 à maxDifference) == la 2ème couleur rouge ou l'invers
        if ((c1.red + i == c2Red) || (c2Red + i == c1.red))
        {
            for (int j = 0; j <= maxDifference; j++)
            {
                // si la couleur bleu + différence (qui varie de 0 à maxDifference) == la 2ème couleur bleu ou l'invers
                if ((c1.blue + j == c2Blue) || (c2Blue + j == c1.blue))
                {
                    for (int k = 0; k <= maxDifference; k++)
                    {
                        // si la couleur verte + différence (qui varie de 0 à maxDifference) == la 2ème couleur verte ou l'invers
                        if ((c1.green + k == c2Green) || (c2Green + k == c1.green))
                            return true; // c bon les 2 couleurs se ressemble
                    } // fin for k
                }
            } // fin for j
        }
    } // fin for i

    // aucune ressemblance
    return false;
}
