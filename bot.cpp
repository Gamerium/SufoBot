#include "bot.h"
#include "globalOrCommon.h"

// function to simulate action of bot

void simulateBotAction(wxString action, int gameWidth, int gameHeight, Display* display, Window gameWindow, bool keepMouse, wxString optionsCoMeFile)
{
    Window root = DefaultRootWindow(display);
    int x, y;

    if (keepMouse)
        mouseCoords(display, root, &x, &y);

    moveBot(action, gameWidth, gameHeight, display, gameWindow, root, optionsCoMeFile);

    if (keepMouse)
        moveMouse(display, root, x, y);
}

// function to move Bot

void moveBot(wxString action, int gameWidth, int gameHeight, Display* display, Window gameWindow, Window root, wxString optionsCoMeFile, wxTextCtrl* txtConsole)
{
    int x, y;

    if (action == _("[HAUT]"))
    {
        // moving mouse
        x = gameWidth / 2;
        y = 50;
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush (display);
        // mouse click
        mouseClick(display, Button1, gameWindow);
    }
    else if (action == _("[GAUCHE]"))
    {
        // moving mouse
        x = 10; // 20px de la marge gauche
        y = gameHeight / 2;
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush (display);
        // mouse click
        mouseClick(display, Button1, gameWindow);
    }
    else if (action == _("[DROITE]"))
    {
        // moving mouse
        x = gameWidth - 10; // - 20px de la marge droite
        y = gameHeight / 2;
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush (display);
        // mouse click
        mouseClick(display, Button1, gameWindow);
    }
    else if (action == _("[BAS]"))
    {
        // moving mouse
        x = gameWidth / 2;
        y = gameHeight - 80; // - 60px de la barre de chat..
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush (display);
        // mouse click
        mouseClick(display, Button1, gameWindow);
    }
    else if (action.Contains(_("[CLICK "))) // let the space after CLICK because if there is no space the code bellow will not work
    {
        // 1st split by space
        wxStringTokenizer st1(action, _(" "));
        wxString actionName = st1.GetNextToken();
        wxString pos = st1.GetNextToken();
        //wxMessageBox(pos);
        // 2nd split by ','
        wxStringTokenizer st2(pos, _(","));
        // moving mouse
        x = wxAtoi(st2.GetNextToken());
        y = wxAtoi(st2.GetNextToken()); // wxAtoi() conversion remove's the ']' character
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush (display);
        // mouse click
        mouseClick(display, Button1, gameWindow);
    }
    else if (action.Contains(_("[KEYPRESS ")))
    {
        // 1st - split by space
        wxStringTokenizer st1(action, _(" "));
        wxString actionName = st1.GetNextToken();
        wxString keyToPress = st1.GetNextToken();
        // 2nd - remove ']'
        keyToPress.RemoveLast();
        //wxMessageBox(keyToPress);
        // press key
        pressKey(display, root, gameWindow, keyToPress);
    }
    else if (action.Contains(_("[SLEEP ")))
    {
        // 1st - split by space
        wxStringTokenizer st1(action, _(" "));
        wxString actionName = st1.GetNextToken();
        wxString sleepTime = st1.GetNextToken();
        // sleep
        wxSleep(wxAtoi(sleepTime));
    }
    else if (action == _("[COMBAT]"))
    {
        // Détection/vérification du combat (Button Pret pixel vérification)
        if (checkCombat(display))
            goCombat(display, gameWindow, optionsCoMeFile, txtConsole);
        else
            AppendToLogAndConsole(_("Aucun combat détecté !"), txtConsole);
    }

    // l'action/l'instruction [STOP] est directement implémenter dans le BotThread
}

// fonction pour détecter/vérifier s'il y'a un combat en cours

bool checkCombat(Display* display)
{
    GameCase pretBtn;
    pretBtn.x = pretBtnX;
    pretBtn.y = pretBtnY;
    pretBtn.red = pretBtnRedColor;
    pretBtn.blue = pretBtnBlueColor;
    pretBtn.green = pretBtnGreenColor;
    if (checkPixelColor(display, pretBtn))
        return true;
    else
        return false;
}

// fonction qui vérifie si le combat est fermé ou pas

bool checkFermetureCombat(Display* display)
{
    GameCase fermerCombatBtn;
    fermerCombatBtn.x = fermBtnX;
    fermerCombatBtn.y = fermBtnY;
    fermerCombatBtn.red = fermBtnRedColor;
    fermerCombatBtn.blue = fermBtnBlueColor;
    fermerCombatBtn.green = fermBtnGreenColor;
    if (checkPixelColor(display, fermerCombatBtn))
        return true;
    else
        return false;
}

// fonction qui vérifie si le mode tactique est activé

bool checkModeTactique(Display* display)
{
    GameCase modeTactiqueBtn;
    modeTactiqueBtn.x = modTBtnX;
    modeTactiqueBtn.y = modTBtnY;
    modeTactiqueBtn.red = modTBtnRedColor;
    modeTactiqueBtn.blue = modTBtnBlueColor;
    modeTactiqueBtn.green = modTBtnGreenColor;
    if (checkPixelColor(display, modeTactiqueBtn))
        return true;
    else
        return false;
}

// fonction qui vérifie si le mode miniature est activé

bool checkModeMiniature(Display* display)
{
    GameCase modeMiniatureBtn;
    modeMiniatureBtn.x = modMBtnX;
    modeMiniatureBtn.y = modMBtnY;
    modeMiniatureBtn.red = modMBtnRedColor;
    modeMiniatureBtn.blue = modMBtnBlueColor;
    modeMiniatureBtn.green = modMBtnGreenColor;
    if (checkPixelColor(display, modeMiniatureBtn))
        return true;
    else
        return false;
}

// fonction qui vérifie si le mode spectateur est activé

bool checkModeSpectateur(Display* display)
{
    GameCase modeSpectateurBtn;
    modeSpectateurBtn.x = modSBtnX;
    modeSpectateurBtn.y = modSBtnY;
    modeSpectateurBtn.red = modSBtnRedColor;
    modeSpectateurBtn.blue = modSBtnBlueColor;
    modeSpectateurBtn.green = modSBtnGreenColor;
    if (checkPixelColor(display, modeSpectateurBtn))
        return true;
    else
        return false;
}

// fonction qui vérifie si c'est le tour du bot ou pas

bool checkTour(Display* display)
{
    GameCase jaugeTour;
    jaugeTour.x = jaugeTrX;
    jaugeTour.y = jaugeTrY;
    jaugeTour.red = jaugeTrRedColor;
    jaugeTour.blue = jaugeTrBlueColor;
    jaugeTour.green = jaugeTrGreenColor;
    if (checkPixelColor(display, jaugeTour))
        return true;
    else
        return false;
}

// fonction de gestion de combat

void goCombat(Display* display, Window gameWindow, wxString optionsCoMeFile, wxTextCtrl* txtConsole)
{
    // Variables de combat
    Window root = DefaultRootWindow(display);
    timelineCase caseTimeline[timelineCasesNumber]; // les cases de la timeline à prendre en compte
    int tour = 1, botTimelinePosition = 0, mobCount = 0, lastTouchedMobPosition = -1; // 1er tour & bot première position par défaut == 0
    wxString cac, sortPrincipal, sortLigneDirecte, sortDiagonale, sortBoost1, sortBoost2;
    short PA, currentBotPA, cacPa, sortPrincipalPa, sortLigneDirectePa, sortDiagonalePa, sortBoost1Pa, sortBoost2Pa;
    wxString s;
    bool connected = true, boosted = false; // connecté à internet, non boosté

    // Lecture des options de combat
    getCombatOptions(optionsCoMeFile, &PA, &cac, &cacPa, &sortPrincipal, &sortPrincipalPa, &sortLigneDirecte, &sortLigneDirectePa, &sortDiagonale, &sortDiagonalePa, &sortBoost1, &sortBoost1Pa, &sortBoost2, &sortBoost2Pa);

    // Fermeture du combat + Activation du mode tactique/miniature (si désactivé) + Désactivation du mode spectateur
    if (!checkFermetureCombat(display))
        mouseMoveAndLeftClick(display, gameWindow, fermBtnX, fermBtnY);
    if (!checkModeTactique(display))
        mouseMoveAndLeftClick(display, gameWindow, modTBtnX, modTBtnY);
    if (!checkModeMiniature(display))
        mouseMoveAndLeftClick(display, gameWindow, modMBtnX, modMBtnY);
    if (!checkModeSpectateur(display))
        mouseMoveAndLeftClick(display, gameWindow, modSBtnX, modSBtnY);

    // Détection de la position du joueur/bot ainsi que le nombre de monstres/mobs
    botTimelinePosition = getBotPositionAndMonstersNumber(display, &caseTimeline[0], &mobCount);

    // si c bon
    if (botTimelinePosition != -1)
    {
        // On poste un message de début du combat
        s << _("Debut de combat (") << mobCount << _(" monstre(s))");
        AppendToLogAndConsole(s, txtConsole);
    }
    else
    {
        AppendToLogAndConsole(_("Echec de la détection de la position du bot !"), txtConsole);
        return;
    }

    // Appui sur le boutton Pret
    //mouseMoveAndLeftClick(display, gameWindow, pretBtnX, pretBtnY);
    if (checkFermetureCombat(display)) // si le boutton de fermeture est en vert/activé, c que le combat vien de commencer, on appui sur pret, si nn => gestion de combat déjà commencé sans appuiyer sur pret car ça fera passer son tour au bot
        pressKey(display, root, gameWindow, _("F1"));

    // Début de boucle (de combat)
    do
    {
        wxSleep(1); // on attend une seconde avant de revérifier si c'est notre tour ou pas

        // Détection de tour (si c'est le tour du bot ou pas)
        if (checkTour(display)) // si oui
        {
            // écriture du rendu
            if (activerLogIA)
            {
                wxString rendu;
                rendu << _("[Tour : ") << tour << _("]");
                AppendToIALog(rendu);
            }
            // on rénitialise le nombre de PA => car c'est début du tour
            currentBotPA = PA;
            // Test d'attaque (1 => attaque cac (sans l'appliquer et sans la répéter))
            if (testerAttaqueOuSortSurToutLesMonstres(&mobCount, &botTimelinePosition, display, root, gameWindow, cac, cacPa, &caseTimeline[0], &currentBotPA, false, false, &lastTouchedMobPosition))
            {// si attaque cac possible, on tente une attaque en ligne directe (car c'est souvent une attaque puissante)
                if (testerAttaqueOuSortSurToutLesMonstres(&mobCount, &botTimelinePosition, display, root, gameWindow, sortLigneDirecte, sortLigneDirectePa, &caseTimeline[0], &currentBotPA, true, true, &lastTouchedMobPosition))
                {// si c'est réussi
                    wxSleep(3); // on attend 3 seconde
                    if (!checkCombat(display)) break; // on vérifie si fin de combat, si oui on sort de la boucle de combat
                }
            }
            else // si nn, on tente le sort principal, si nn sort diagonale
            {
                if (!testerAttaqueOuSortSurToutLesMonstres(&mobCount, &botTimelinePosition, display, root, gameWindow, sortPrincipal, sortPrincipalPa, &caseTimeline[0], &currentBotPA, true, true, &lastTouchedMobPosition))
                {
                    if (testerAttaqueOuSortSurToutLesMonstres(&mobCount, &botTimelinePosition, display, root, gameWindow, sortDiagonale, sortDiagonalePa, &caseTimeline[0], &currentBotPA, true, true, &lastTouchedMobPosition))
                    {// si sort diagonale réussi
                        wxSleep(3); // on attend 3 seconde
                        if (!checkCombat(display)) break; // on vérifie si fin de combat, si oui on sort de la boucle de combat
                    }
                }
                else // si nn si sort principal réussi
                {
                    wxSleep(3); // on attend 3 seconde
                    if (!checkCombat(display)) break; // on vérifie si fin de combat, si oui on sort de la boucle de combat
                }
            }

            // si perte de connection après l'essai des sort/attaque, on sort de la boucle
            if (!checkInternetConnection())
            {
                connected = false;
                break;
            }

            // si aucune attaque sur monstre/mob réussi, on tente un boost (si jamais boosté)
            if (!boosted)
            {
                // écriture du rendu/log
                if (activerLogIA)
                    AppendToIALog(_("Test 1er boost...")); // rendu
                // si boost 1 réussi, on tente le 2ème aussi
                if (testerAttaqueOuSort(display, root, gameWindow, sortBoost1, sortBoost1Pa, caseTimeline[botTimelinePosition], &currentBotPA, true, false))
                {
                    boosted = true; // boosté
                    // écriture du rendu/log
                    if (activerLogIA)
                        AppendToIALog(_("Test 2ème boost...")); // rendu
                    testerAttaqueOuSort(display, root, gameWindow, sortBoost2, sortBoost2Pa, caseTimeline[botTimelinePosition], &currentBotPA, true, false);
                }
            }

            // Si nn on passe le tour (Appui sur le boutton Pret/Passer Tour)
            //mouseMoveAndLeftClick(display, gameWindow, pretBtnX, pretBtnY);
            pressKey(display, root, gameWindow, _("F1"));
            tour++;
            // on actualise le nombre de monstre et la position du bot
            int mobPositionChanged = monstersNumberChanged(display, &caseTimeline[0], mobCount, botTimelinePosition);
            if (mobPositionChanged != -1) // != -1 => il y'a eu un changement, == -1 => aucun changement
            {
                // on diminue le nombre de mob
                mobCount--;
                // on diminue la position du bot
                if (mobPositionChanged < botTimelinePosition) // si le changement affecte la position du bot
                    botTimelinePosition--;
                // on indique qu'on a plus de mob a focus/a tué en priorité, car c'est surement celui qui est mort
                lastTouchedMobPosition = -1;
                // écriture du rendu
                if (activerLogIA)
                {
                    AppendToIALog(_("Monsters Number Changed !"));
                    wxString rendu;
                    rendu << _("Monster Position Changed : ") << mobPositionChanged;
                    AppendToIALog(rendu);
                    rendu.Clear();
                    rendu << _("Last Touched Mob Position : ") << lastTouchedMobPosition;
                    AppendToIALog(rendu);
                    rendu.Clear();
                    rendu << _("New Bot Position : ") << botTimelinePosition;
                    AppendToIALog(rendu);
                    rendu.Clear();
                    rendu << _("New Monsters Number : ") << mobCount;
                    AppendToIALog(rendu);
                }
            }

            // la Détection de fin du combat se fait grace au while de la boucle
        }

        // si perte de connection alors que ce n'est pas notre tour, on sort de la boucle
        if (!checkInternetConnection())
        {
            connected = false;
            break;
        }

    } while(checkCombat(display)); // tant que le combat est toujours en cours (boutton pret toujours visible)

    // On poste un message de fin du combat
    if (connected) // s'il n'y a eu aucune erreur de connection avant la fin/arret du combat
    {
        s.Clear();
        s << _("Fin de combat (durée : ") << tour << _(" tour(s))");
        AppendToLogAndConsole(s, txtConsole);
        // Fermeture de la fenetre de fin de combat
        pressKey(display, root, gameWindow, _("ESC"));
    }
    else
        AppendToLogAndConsole(_("Arret de combat (connection perdu)"), txtConsole);
}

// fonction qui lit le fichier d'options de combat afin d'affecter/remplir les variables de combat

void getCombatOptions(wxString optionsCoMeFile, short* PA, wxString* cac, short* cacPa, wxString* sortPrincipal, short* sortPrincipalPa, wxString* sortLigneDirecte, short* sortLigneDirectePa, wxString* sortDiagonale, short* sortDiagonalePa, wxString* sortBoost1, short* sortBoost1Pa, wxString* sortBoost2, short* sortBoost2Pa)
{
    // open options file
    wxTextFile file;
    file.Open(optionsCoMeFile);

    file.GetFirstLine(); // we don't need this one

    // PA
    (*PA) = wxAtoi(file.GetNextLine());
    // Cac
    wxStringTokenizer cacStr(file.GetNextLine(), _("|"));
    (*cac) = cacStr.GetNextToken();
    (*cacPa) = wxAtoi(cacStr.GetNextToken());
    // Sort Principal
    wxStringTokenizer sortPrincipalStr(file.GetNextLine(), _("|"));
    (*sortPrincipal) = sortPrincipalStr.GetNextToken();
    (*sortPrincipalPa) = wxAtoi(sortPrincipalStr.GetNextToken());
    // Sort Ligne Directe
    wxStringTokenizer sortLigneDirecteStr(file.GetNextLine(), _("|"));
    (*sortLigneDirecte) = sortLigneDirecteStr.GetNextToken();
    (*sortLigneDirectePa) = wxAtoi(sortLigneDirecteStr.GetNextToken());
    // Sort Ligne Directe
    wxStringTokenizer sortDiagonaleStr(file.GetNextLine(), _("|"));
    (*sortDiagonale) = sortDiagonaleStr.GetNextToken();
    (*sortDiagonalePa) = wxAtoi(sortDiagonaleStr.GetNextToken());
    // Sort Boost 1
    wxStringTokenizer sortBoost1Str(file.GetNextLine(), _("|"));
    (*sortBoost1) = sortBoost1Str.GetNextToken();
    (*sortBoost1Pa) = wxAtoi(sortBoost1Str.GetNextToken());
    // Sort Boost 2
    wxStringTokenizer sortBoost2Str(file.GetNextLine(), _("|"));
    (*sortBoost2) = sortBoost2Str.GetNextToken();
    (*sortBoost2Pa) = wxAtoi(sortBoost2Str.GetNextToken());

    file.Close(); // closing file
}

// fonction pour initialiser les informations de chaque case de la timeline

void initTimelineCases(timelineCase* caseTimeline)
{
    // case 1 informations
    caseTimeline[0].jaugeVieX = 832;
    caseTimeline[0].jaugeVieY = 620;
    caseTimeline[0].jaugeVieBasY = 635;
    caseTimeline[0].clickX = 810;
    caseTimeline[0].clickY = 610;
    caseTimeline[0].interdictionAttaque.x = caseTimeline[0].clickX + interdictionX;
    caseTimeline[0].interdictionAttaque.y = caseTimeline[0].clickY + interdictionY;
    caseTimeline[0].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[0].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[0].interdictionAttaque.green = interdictionGreenColor;

    // case 2 informations
    caseTimeline[1].jaugeVieX = 788;
    caseTimeline[1].jaugeVieY = 620;
    caseTimeline[1].jaugeVieBasY = 635;
    caseTimeline[1].clickX = 768;
    caseTimeline[1].clickY = 610;
    caseTimeline[1].interdictionAttaque.x = caseTimeline[1].clickX + interdictionX;
    caseTimeline[1].interdictionAttaque.y = caseTimeline[1].clickY + interdictionY;
    caseTimeline[1].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[1].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[1].interdictionAttaque.green = interdictionGreenColor;

    // case 3 informations
    caseTimeline[2].jaugeVieX = 744;
    caseTimeline[2].jaugeVieY = 620;
    caseTimeline[2].jaugeVieBasY = 635;
    caseTimeline[2].clickX = 724;
    caseTimeline[2].clickY = 610;
    caseTimeline[2].interdictionAttaque.x = caseTimeline[2].clickX + interdictionX;
    caseTimeline[2].interdictionAttaque.y = caseTimeline[2].clickY + interdictionY;
    caseTimeline[2].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[2].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[2].interdictionAttaque.green = interdictionGreenColor;

    // case 4 informations
    caseTimeline[3].jaugeVieX = 700;
    caseTimeline[3].jaugeVieY = 620;
    caseTimeline[3].jaugeVieBasY = 635;
    caseTimeline[3].clickX = 684;
    caseTimeline[3].clickY = 610;
    caseTimeline[3].interdictionAttaque.x = caseTimeline[3].clickX + interdictionX;
    caseTimeline[3].interdictionAttaque.y = caseTimeline[3].clickY + interdictionY;
    caseTimeline[3].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[3].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[3].interdictionAttaque.green = interdictionGreenColor;

    // case 5 informations
    caseTimeline[4].jaugeVieX = 656;
    caseTimeline[4].jaugeVieY = 620;
    caseTimeline[4].jaugeVieBasY = 635;
    caseTimeline[4].clickX = 634;
    caseTimeline[4].clickY = 618;
    caseTimeline[4].interdictionAttaque.x = caseTimeline[4].clickX + interdictionX;
    caseTimeline[4].interdictionAttaque.y = caseTimeline[4].clickY + interdictionY;
    caseTimeline[4].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[4].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[4].interdictionAttaque.green = interdictionGreenColor;

    // case 6 informations
    caseTimeline[5].jaugeVieX = 612;
    caseTimeline[5].jaugeVieY = 620;
    caseTimeline[5].jaugeVieBasY = 635;
    caseTimeline[5].clickX = 598;
    caseTimeline[5].clickY = 618;
    caseTimeline[5].interdictionAttaque.x = caseTimeline[5].clickX + interdictionX;
    caseTimeline[5].interdictionAttaque.y = caseTimeline[5].clickY + interdictionY;
    caseTimeline[5].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[5].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[5].interdictionAttaque.green = interdictionGreenColor;

    // case 7 informations
    caseTimeline[6].jaugeVieX = 568;
    caseTimeline[6].jaugeVieY = 620;
    caseTimeline[6].jaugeVieBasY = 635;
    caseTimeline[6].clickX = 550;
    caseTimeline[6].clickY = 618;
    caseTimeline[6].interdictionAttaque.x = caseTimeline[6].clickX + interdictionX;
    caseTimeline[6].interdictionAttaque.y = caseTimeline[6].clickY + interdictionY;
    caseTimeline[6].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[6].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[6].interdictionAttaque.green = interdictionGreenColor;

    // case 8 informations
    caseTimeline[7].jaugeVieX = 524;
    caseTimeline[7].jaugeVieY = 620;
    caseTimeline[7].jaugeVieBasY = 635;
    caseTimeline[7].clickX = 508;
    caseTimeline[7].clickY = 618;
    caseTimeline[7].interdictionAttaque.x = caseTimeline[7].clickX + interdictionX;
    caseTimeline[7].interdictionAttaque.y = caseTimeline[7].clickY + interdictionY;
    caseTimeline[7].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[7].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[7].interdictionAttaque.green = interdictionGreenColor;

    // case 9 informations
    caseTimeline[8].jaugeVieX = 479;
    caseTimeline[8].jaugeVieY = 620;
    caseTimeline[8].jaugeVieBasY = 635;
    caseTimeline[8].clickX = 466;
    caseTimeline[8].clickY = 618;
    caseTimeline[8].interdictionAttaque.x = caseTimeline[8].clickX + interdictionX;
    caseTimeline[8].interdictionAttaque.y = caseTimeline[8].clickY + interdictionY;
    caseTimeline[8].interdictionAttaque.red = interdictionRedColor;
    caseTimeline[8].interdictionAttaque.blue = interdictionBlueColor;
    caseTimeline[8].interdictionAttaque.green = interdictionGreenColor;
}

// fonction qui retourne la position du bot dans la timeline + calcul le nombre de monstres

int getBotPositionAndMonstersNumber(Display* display, timelineCase* caseTimeline, int* monstersNumber)
{
    // on initialise les informations des cases de la timeline
    initTimelineCases(caseTimeline);

    // on récupère la position du bot
    int botPosition = -1;
    XColor c;
    //(*monstersNumber) = 0; // initialisation
    wxString rendu;
    if (activerLogIA)
        AppendToIALog(_("Get bot position & monsters number..."));

    for (int position = 0; position < timelineCasesNumber; position++)
    {
        getPixelColor(display, caseTimeline[position].jaugeVieX, caseTimeline[position].jaugeVieY, &c);
        // écriture du rendu
        if (activerLogIA)
        {
            rendu.Clear();
            rendu << _("Position [") << position << _("] => Red : ") << c.red/256 << _(" Blue : ") << c.blue/256 << _(" Green : ") << c.green/256;
            AppendToIALog(rendu);
        }
        // si position bot pas encore trouvé, + on vien de la trouver
        if (botPosition == -1 && checkColorsSimilarity(c, botJaugeVieRedColor, botJaugeVieBlueColor, botJaugeVieGreenColor, couleurMaxDifference))
            botPosition = position; // on l'enregistre
        // si nn si mob/monstre trouvé
        else if (checkColorsSimilarity(c, mobJaugeVieRedColor, mobJaugeVieBlueColor, mobJaugeVieGreenColor, couleurMaxDifference))
            (*monstersNumber)++; // on incrémente le nombre de mob/monstres
        else // si nn (ni bot, ni mob) on a tout trouvé alors, on sort de la boucle
            break;
    }

    // écriture du rendu/log
    if (activerLogIA)
    {
        rendu.Clear();
        rendu << _("Bot Position : ") << botPosition;
        AppendToIALog(rendu);
        rendu.Clear();
        rendu << _("Monsters Number : ") << *monstersNumber;
        AppendToIALog(rendu);
    }
    return botPosition; // if -1 (failed) => erreur quelque part (dans les informations des cases)
}

// fonction pour attaquer ou lancer un sort de boost

bool testerAttaqueOuSort(Display* display, Window root, Window gameWindow, wxString attaqueOuSort, short paRequis, timelineCase caseTimeline, short* PA, bool appliquerAttaqueOuSort, bool repeterAttaqueOuSort)
{
    // on vérifie la connection
    if (!checkInternetConnection())
    {
        return false;
    }
    else if (attaqueOuSort == _("None")) // si aucune attaque/sort de ce type
    {
        if (activerLogIA) AppendToIALog(_("=> None..")); // rendu
        return false;
    }
    else if ((*PA) < paRequis) // si nombre de PA insuffisant
    {
        if (activerLogIA) AppendToIALog(_("=> PA insuffisant..")); // rendu
        return false;
    }

    // on choisi le sort
    pressKey(display, root, gameWindow, attaqueOuSort);
    wxMilliSleep(100); // on attend 100 milliseconde le temp que tt s'affiche bien
    // on déplace la sourie sur la timeline (sur la position de click exactement)
    moveMouse(display, root, caseTimeline.clickX, caseTimeline.clickY);
    wxSleep(1); // on attend une seconde le temp que tt s'affiche bien
    // on vérifie s'il n'y a pas d'interdiction d'attaque
    if (!checkPixelColor(display, caseTimeline.interdictionAttaque))
    {
        if (appliquerAttaqueOuSort)
        {
            mouseClick(display, Button1, gameWindow); // on applique le sort
            (*PA) -= paRequis; // on retire le nombre de PA utilisés
            wxSleep(1); // On attend une seconde avant de continuer le combat (le temp que l'animation se joue)
            // écriture du rendu
            if (activerLogIA)
            {
                wxString rendu;
                rendu << _("=> [Attaque/Sort ") << attaqueOuSort << _("] Success ! [PA restant : ") << *PA << _("]");
                AppendToIALog(rendu); // rendu
            }
            // si repetition autorisé
            if (repeterAttaqueOuSort)
            {
                if (activerLogIA) AppendToIALog(_("[Repetition]")); // rendu
                // tant qu'on peu toujours repeter on repete
                while(testerAttaqueOuSort(display, root, gameWindow, attaqueOuSort, paRequis, caseTimeline, PA, true, true));
            }
        }
        else
            if (activerLogIA) AppendToIALog(_("=> Success without apply !")); // rendu
        return true;
    }
    else
    {
        if (activerLogIA) AppendToIALog(_("=> Interdiction..")); // rendu
        return false;
    }
}

// fonction pour tester les attaques/sorts sur tout les mobs/monstres de la Timeline

bool testerAttaqueOuSortSurToutLesMonstres(int* mobCount, int* botPosition, Display* display, Window root, Window gameWindow, wxString attaqueOuSort, short paRequis, timelineCase* caseTimeline, short* PA, bool appliquerAttaqueOuSort, bool repeterAttaqueOuSort, int* lastTouchedMobPosition)
{
    // on vérifie la connection
    if (!checkInternetConnection())
        return false;

    wxString rendu;
    // écriture du rendu
    if (activerLogIA)
    {
        AppendToIALog(_("Test attaque/sort sur tout les monstres..."));
        rendu << _("PA : ") << *PA << _(" | Attaque/Sort : ") << attaqueOuSort << _(" | Pa requis : ") << paRequis << _(" | appliquer(") << (appliquerAttaqueOuSort ? _("oui") : _("non")) << _(")") << _(" | repeter(") << (repeterAttaqueOuSort ? _("oui") : _("non")) << _(")");
        AppendToIALog(rendu);
    }

    // si on a déjà toucher un mob auparavant, on l'entame/le fini
    if ((*lastTouchedMobPosition) != -1)
    {
        // écriture du rendu
        if (activerLogIA)
        {
            rendu.Clear();
            rendu << _("Last Touched Mob Position [") << *lastTouchedMobPosition << _("]");
            AppendToIALog(rendu);
        }
        // si on arrive à le finir
        if (testerAttaqueOuSort(display, root, gameWindow, attaqueOuSort, paRequis, caseTimeline[*lastTouchedMobPosition], PA, appliquerAttaqueOuSort, repeterAttaqueOuSort))
        {
            // ce clic sert a éviter les lags de la timeline après la mort d'un mob
            if (appliquerAttaqueOuSort) // si un sort à été appliqué on click sur le perso/bot pour éviter les lags
                mouseMoveAndLeftClick(display, gameWindow, caseTimeline[*botPosition].clickX, caseTimeline[*botPosition].clickY);
            return true; // success
        }
        // si nn on reteste d'attaquer tt les mobs
    }

    // test attaque sur tout les mobs/monstres
    for (int i = 0; i <= (*mobCount); i++)
    {
        // on teste sur toutes les cases de la timeline sauf celle du bot, et celle du dernier mob touché
        if ((i != (*botPosition) && (*lastTouchedMobPosition) == -1) || (i != (*botPosition) && i != (*lastTouchedMobPosition)))
        {
            // écriture du rendu
            if (activerLogIA)
            {
                rendu.Clear();
                rendu << _("Position [") << i << _("]");
                AppendToIALog(rendu);
            }
            // si on réussi à a voir au moin un mob/monstre
            if (testerAttaqueOuSort(display, root, gameWindow, attaqueOuSort, paRequis, caseTimeline[i], PA, appliquerAttaqueOuSort, repeterAttaqueOuSort))
            {
                // ce clic sert a éviter les lags de la timeline après la mort d'un mob
                if (appliquerAttaqueOuSort) // si un sort à été appliqué on click sur le perso/bot pour éviter les lags
                    mouseMoveAndLeftClick(display, gameWindow, caseTimeline[*botPosition].clickX, caseTimeline[*botPosition].clickY);
                *lastTouchedMobPosition = i; // on enregistre la position du dernier mob touché, pour le finir après
                return true; // success
            }
        }
    }

    // Pour éviter les fausses détection de mort d'un mob
    moveMouse(display, root, caseTimeline[*botPosition].clickX, caseTimeline[*botPosition].clickY);
    //pressKey(display, root, gameWindow, _("ESC"));

    // si nn si on y arrive pas
    return false; // fail
}

// fonction qui vérifie si le nombre de monstres à changer ou pas
// l'erreur de cette fonction c'est que si le mob a peu de vita, il est considéré comme mort, ce qui crée des erreurs dans l'IA

int monstersNumberChanged(Display *display, timelineCase* caseTimeline, int currentMonstersNumber, int botPosition)
{
    for (int i = 0; i < currentMonstersNumber + 1; i++) // (+1) car on doit prendre en compte le bot aussi
    {
        if (i != botPosition)
        {
            XColor c;
            getPixelColor(display, caseTimeline[i].jaugeVieX, caseTimeline[i].jaugeVieBasY, &c);
            if (!checkColorsSimilarity(c, mobJaugeVieBasRedClr, mobJaugeVieBasBlueClr, mobJaugeVieBasGreenClr, couleurMaxDifference))
            {// si une case de la Timeline qui contenais un monstre/mob à subit un changement de couleur dans la jauge de vie
                return i; // il y'a eu un changement sur le mob de la position i (il est surement mort)
            }
        }
    }

    return -1; // rien d'anormal
}

// fonction pour détecter/vérifier s'il y'a la fenetre succes existe ou pas

bool checkFenetreSucces(Display* display)
{
    GameCase fen;
    fen.x = fenSuccesX;
    fen.y = fenSuccesY;
    fen.red = fenSuccesRedColor;
    fen.blue = fenSuccesBlueColor;
    fen.green = fenSuccesGreenColor;
    if (checkPixelColor(display, fen))
        return true;
    else
        return false;
}

// fonction pour détecter/vérifier s'il y'a la fenetre Défi/échange existe ou pas

bool checkFenetreDefiEchange(Display* display)
{
    GameCase fen;
    fen.x = fenDefiEchX;
    fen.y = fenDefiEchY;
    fen.red = fenDefiEchRedColor;
    fen.blue = fenDefiEchBlueColor;
    fen.green = fenDefiEchGreenColor;
    if (checkPixelColor(display, fen))
        return true;
    else
        return false;
}

// fonction pour détecter/vérifier s'il y'a la fenetre lvl up Métier existe ou pas

bool checkFenetreLvlUpMetier(Display* display)
{
    GameCase fen;
    fen.x = fenLvlUpMeX;
    fen.y = fenLvlUpMeY;
    fen.red = fenLvlUpMeRedColor;
    fen.blue = fenLvlUpMeBlueColor;
    fen.green = fenLvlUpMeGreenColor;
    if (checkPixelColor(display, fen))
        return true;
    else
        return false;
}

// fonction pour détecter/vérifier s'il y'a la fenetre lvl up Combat existe ou pas

bool checkFenetreLvlUpCombat(Display* display)
{
    GameCase fen;
    fen.x = fenLvlUpCoX;
    fen.y = fenLvlUpCoY;
    fen.red = fenLvlUpCoRedColor;
    fen.blue = fenLvlUpCoBlueColor;
    fen.green = fenLvlUpCoGreenColor;
    if (checkPixelColor(display, fen))
        return true;
    else
        return false;
}

// fonction qui ferme toutes les fenetres genantes

void fermerToutesLesFenetresGenantes(Display* display, Window gameWindow)
{
    // si fenetre Défi/échange
    if (checkFenetreDefiEchange(display))
        mouseMoveAndLeftClick(display, gameWindow, fenDefiEchX, fenDefiEchY);
    // si nn si fenetre Lvl up Métier
    else if (checkFenetreLvlUpMetier(display))
        mouseMoveAndLeftClick(display, gameWindow, fenLvlUpMeX, fenLvlUpMeY);
    // si nn si fenetre Lvl up Combat
    else if (checkFenetreLvlUpCombat(display))
        mouseMoveAndLeftClick(display, gameWindow, fenLvlUpCoX, fenLvlUpCoY);

    // si fenetre succes
    if (checkFenetreSucces(display))
    {
        // on affiche la fenetre de succes complète
        mouseMoveAndLeftClick(display, gameWindow, fenSuccesX, fenSuccesY);
        wxSleep(1); // on attend que tt s'affiche bien
        // on ferme la fenetre de succes
        mouseMoveAndLeftClick(display, gameWindow, fermetureFenSuccesX, fermetureFenSuccesY);
    }
}
