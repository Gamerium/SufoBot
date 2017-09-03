#include "threads.h"

// constr.

MousePosition::MousePosition(wxTextCtrl* tX, wxTextCtrl* tY, wxCheckBox* c)
{
    this->txtX = tX;
    this->txtY = tY;
    this->getMousePoscheck = c;
}

// Entry methode

void* MousePosition::Entry()
{

    Display* display = XOpenDisplay(NULL); // try opening display
    if(display == NULL)
    {
        fprintf(stderr, "Error cannot open display !\n");
        exit(EXIT_FAILURE);
    }

    XEvent event;
    Window root = XDefaultRootWindow(display);
    XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

    //XSelectInput(display, root, ButtonPressMask); // freez/stop program

    bool success = false;

    while(!success)
    {
        XNextEvent(display, &event);
        switch(event.type)
        {
            case ButtonPress:
                Mx << event.xbutton.x;
                My << event.xbutton.y;
                success = true;
                break;
        }
    } // fin while

    XCloseDisplay(display); // closing display (or mouse click will freez)

    return 0; // success
}

void MousePosition::OnExit()
{
    // changing textBoxs values
    txtX->SetValue(Mx);
    txtY->SetValue(My);

    getMousePoscheck->Enable(); // enable checkbox
    getMousePoscheck->SetValue(false); // uncheck checkbox
}

// constr. bot thread

BotThread::BotThread(wxString trajetPath, Display* display, Window gameWindow, int gameWidth, int gameHeight, wxButton* lancerBtn, wxButton* stopBtn, wxTextCtrl* txtConsole, bool keepMouse, int* repriseIndex, bool repeterTrajet, wxString optionsCoMeFile)
{
    // les memes noms (par rapport aux attributs) ne comptent pas le this fait la différence
    this->trajetPath = trajetPath;
    this->display = display;
    this->gameWindow = gameWindow;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->lancerBtn = lancerBtn;
    this->stopBtn = stopBtn;
    this->txtConsole = txtConsole;
    this->keepMouse = keepMouse;
    this->repriseIndex = repriseIndex;
    this->repeterTrajet = repeterTrajet;
    this->optionsCoMeFile = optionsCoMeFile;
}

// Entry methode

void* BotThread::Entry()
{
    Window root = DefaultRootWindow(display);

    do
    {
        int x, y, currentLineIndex = 1; // 1 => first line
        forcedStop = false;

        // get current mouse position / the difference beetween here and simulateBotAction() function is that we call mouseCoords() function just one time
        if (keepMouse)
            mouseCoords(display, root, &x, &y);

        // open the file
        wxTextFile file;
        file.Open(trajetPath);

        if ((*repriseIndex) == -1) // pas de reprise, il vaux mieu mettre un pointeur entre () pr éviter les conflits entre adresse et valeur
        {
            // read First Line & execute first command
            moveBot(file.GetFirstLine(), gameWidth, gameHeight, display, gameWindow, root, optionsCoMeFile, txtConsole);
            if (keepMouse)
                moveMouse(display, root, x, y);
        }
        else
        {
            //file.GetFirstLine(); // pas obligatoire içi
            while(currentLineIndex < ((*repriseIndex) - 1)) // -1 car on ne doit pas atteindre le repriseIndex
            {
                file.GetNextLine();
                currentLineIndex++;
            }
            // une fois le currentLineIndex == repriseIndex on reprend le trajet du bot
        }

        // read all lines one by one
        // until the end of the file
        while(!file.Eof())
        {
            // fermeture des fenetres succes/défi/échange/lvl_up si ouvertes
            fermerToutesLesFenetresGenantes(display, gameWindow);

            // on récupère l'instruction/l'action à faire
            wxString instruction = file.GetNextLine();

            // if we must Stop, or internet connection disabled, or [STOP] action/instruction in 'trajet file'
            isConnected = checkInternetConnection();
            if(TestDestroy() || !isConnected || (instruction == _("[STOP]")))
            {
                file.Close();
                (*repriseIndex) = ++currentLineIndex; // l'index de reprise est celui d'après la ligne actuelle
                forcedStop = true;
                this->Exit();  // or return;
            }
            else if (checkCombat(display)) // si nn si Aggro
            {
                AppendToLogAndConsole(_("Aggro /!\\"), txtConsole);
                // Gestion de l'aggro/Combat
                moveBot(_("[COMBAT]"), gameWidth, gameHeight, display, gameWindow, root, optionsCoMeFile, txtConsole);
            }

            // do bot work
            moveBot(instruction, gameWidth, gameHeight, display, gameWindow, root, optionsCoMeFile, txtConsole);

            if (keepMouse)
                moveMouse(display, root, x, y);

            currentLineIndex++;
        }

        // close file
        file.Close();

        (*repriseIndex) = -1; // trajet fini, pas de reprise possible

    } while(repeterTrajet);

    return 0; // success
}

void BotThread::OnExit()
{
    lancerBtn->Enable(true);
    stopBtn->Enable(false);

    if (!isConnected)
        AppendToLogAndConsole(_("Arret forcé du bot (connection perdu)"), txtConsole);
    else
        AppendToLogAndConsole(forcedStop ? _("Arret forcé du bot") : _("Arret du bot"), txtConsole);
}

// contr. Simuler Combat Thread

SimulerCombatThread::SimulerCombatThread(wxButton* simulerCombatBtn, int gameWidth, int gameHeight, Display* display, Window gameWindow, Window root, wxString optionsCoMeFile, wxTextCtrl* txtConsole)
{
    this->simulerCombatBtn = simulerCombatBtn;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->display = display;
    this->gameWindow = gameWindow;
    this->root = root;
    this->optionsCoMeFile = optionsCoMeFile;
    this->txtConsole = txtConsole;
}

// Entry methode

void* SimulerCombatThread::Entry()
{
    moveBot(_("[COMBAT]"), gameWidth, gameHeight, display, gameWindow, root, optionsCoMeFile, txtConsole);

    return 0; // success
}

void SimulerCombatThread::OnExit()
{
    // activation du boutton simuler Combat
    simulerCombatBtn->Enable(true);
}
