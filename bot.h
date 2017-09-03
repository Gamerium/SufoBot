#ifndef BOT_H
#define BOT_H

#include "functions.h"

// Button Pret
#define pretBtnX                423
#define pretBtnY                725
#define pretBtnRedColor         226
#define pretBtnBlueColor        34
#define pretBtnGreenColor       109
// Button Mode Tactique
#define modTBtnX                397
#define modTBtnY                655
#define modTBtnRedColor         75
#define modTBtnBlueColor        5
#define modTBtnGreenColor       103
// Button Mode Miniature/Créature
#define modMBtnX                377
#define modMBtnY                670
#define modMBtnRedColor         117
#define modMBtnBlueColor        0
#define modMBtnGreenColor       170
// Button Fermer Combat
#define fermBtnX                403
#define fermBtnY                641
#define fermBtnRedColor         104
#define fermBtnBlueColor        88
#define fermBtnGreenColor       93
// Mode Spectateur
#define modSBtnX                383
#define modSBtnY                703
#define modSBtnRedColor         180
#define modSBtnBlueColor        47
#define modSBtnGreenColor       243
// Jauge Tour
#define jaugeTrX                445
#define jaugeTrY                646
#define jaugeTrRedColor         253
#define jaugeTrBlueColor        26
#define jaugeTrGreenColor       117
// Bot Jauge Vie Couleur (par défaut c'est le rouge)
#define botJaugeVieRedColor     255
#define botJaugeVieBlueColor    23
#define botJaugeVieGreenColor   23
// Mob Jauge Vie Couleur (par défaut c'est le bleu)
#define mobJaugeVieRedColor     21
#define mobJaugeVieBlueColor    255
#define mobJaugeVieGreenColor   220
// Mob Jauve Vie Bas Couleur (couleur du bas)
#define mobJaugeVieBasRedClr    14
#define mobJaugeVieBasBlueClr   178
#define mobJaugeVieBasGreenClr  154
// Maximum de différence d'une couleur par rapport à une autre (car parfois la couleur des jauge Vie des mob ou bot change)
#define couleurMaxDifference    30
// Nombre de case (à prendre en considération) dans la timeline
#define timelineCasesNumber     9 // 8 mob/monstre max + le bot/joueur
// Interdiction attaque relative position & color
#define interdictionX           15
#define interdictionY           14
#define interdictionRedColor    211
#define interdictionBlueColor   29
#define interdictionGreenColor  22
// Fenetre Succes
#define fenSuccesX              429
#define fenSuccesY              626
#define fermetureFenSuccesX     373
#define fermetureFenSuccesY     556
#define fenSuccesRedColor       241
#define fenSuccesBlueColor      16
#define fenSuccesGreenColor     92
// Fenetre Défi ou échange
#define fenDefiEchX             410
#define fenDefiEchY             435
#define fenDefiEchRedColor      241
#define fenDefiEchBlueColor     22
#define fenDefiEchGreenColor    99
// Fenetre Lvl up Métier
#define fenLvlUpMeX             420
#define fenLvlUpMeY             440
#define fenLvlUpMeRedColor      241
#define fenLvlUpMeBlueColor     31
#define fenLvlUpMeGreenColor    109
// Fenetre Lvl up Combat
#define fenLvlUpCoX             613
#define fenLvlUpCoY             313
#define fenLvlUpCoRedColor      241
#define fenLvlUpCoBlueColor     32
#define fenLvlUpCoGreenColor    110

// structures

struct timelineCase {
    int jaugeVieX;
    int jaugeVieY;
    int jaugeVieBasY;
    int clickX;
    int clickY;
    GameCase interdictionAttaque;
};

// prototypes

void simulateBotAction(wxString action, int gameWidth, int gameHeight, Display* display, Window gameWindow, bool keepMouse, wxString optionsCoMeFile = _(""));
// si j'ai ajouté optionsCoMeFile içi, c juste car moveBot() en depend, si nn j'en ai pas besoin içi, voila pq l'affectation d'une chaine vide, et au final tt ça pr ne pas devoir changer tt les appels de la fonction simulateBotAction dans tt le code
void moveBot(wxString action, int gameWidth, int gameHeight, Display* display, Window gameWindow, Window root, wxString optionsCoMeFile, wxTextCtrl* txtConsole = NULL);
bool checkCombat(Display* display);
bool checkFermetureCombat(Display* display);
bool checkModeTactique(Display* display);
bool checkModeMiniature(Display* display);
bool checkTour(Display* display);
void goCombat(Display* display, Window gameWindow, wxString optionsCoMeFile, wxTextCtrl* txtConsole);
void getCombatOptions(wxString optionsCoMeFile, short* PA, wxString* cac, short* cacPa, wxString* sortPrincipal, short* sortPrincipalPa, wxString* sortLigneDirecte, short* sortLigneDirectePa, wxString* sortDiagonale, short* sortDiagonalePa, wxString* sortBoost1, short* sortBoost1Pa, wxString* sortBoost2, short* sortBoost2Pa);
void initTimelineCases(timelineCase* caseTimeline);
int getBotPositionAndMonstersNumber(Display* display, timelineCase* caseTimeline, int* monstersNumber);
bool testerAttaqueOuSort(Display* display, Window root, Window gameWindow, wxString attaqueOuSort, short paRequis, timelineCase caseTimeline, short* PA, bool appliquerAttaqueOuSort, bool repeterAttaqueOuSort);
bool testerAttaqueOuSortSurToutLesMonstres(int* mobCount, int* botPosition, Display* display, Window root, Window gameWindow, wxString attaqueOuSort, short paRequis, timelineCase* caseTimeline, short* PA, bool appliquerAttaqueOuSort, bool repeterAttaqueOuSort, int* lastTouchedMobPosition);
int monstersNumberChanged(Display *display, timelineCase* caseTimeline, int currentMonstersNumber, int botPosition);

bool checkFenetreSucces(Display* display);
bool checkFenetreDefiEchange(Display* display);
bool checkFenetreLvlUpMetier(Display* display);
bool checkFenetreLvlUpCombat(Display* display);
void fermerToutesLesFenetresGenantes(Display* display, Window gameWindow);

#endif
