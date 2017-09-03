/***************************************************************
 * Name:      SufoBotMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    AXeL (axel.prog.25@gmail.com)
 * Created:   2015-07-20
 * Copyright: AXeL ()
 * License:
 * Idées d'améliorations : - Gestion de Métier (Metier function)
                           - Auto XP (recherche de combat automatique)
                           - Command to close game after a "trajet"
                           - Si pas de vita s'aseoir (s'il n'y pas assez de vita, la detection de la position du bot dans un combat ne fonctionnera pas aussi)
                           - Fermeture des fenetres d'invitations aussi
                           - Utilisation de PM en combat
                           - Gestion d'elevage (Elevage function)
 **************************************************************/

#include "wx_pch.h"
#include "SufoBotMain.h"
#include <wx/msgdlg.h>

#include <wx/process.h>
//#include "bot.h" // we can remove this because thread.h contains it
#include "threads.h"
#include "globalOrCommon.h"

// variables globales
bool activerLogIA = true;

//(*InternalHeaders(SufoBotFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

// attributs
Window *winList;
Display *display = NULL;
int DesktopWidth, BotWidth, BotHeight, GameWidth, GameHeight;
MousePosition* mp;
BotThread* bt;
int autoRepriseIndex = -1;
wxString msgErreur[] = {
    _("Veuillez séléctionner la fenetre du jeu !"),
    _("X et Y ne doivent pas être vide !"),
    _("X ou Y n'est pas un nombre !"),
    _("Vous devez séléctionner une ligne pour la supprimer !"),
    _("rien à supprimer !"),
    _("rien à enregistrer !"),
    _("Vous devez séléctionner et redimensionner la fenetre du jeu dans l'onglet Bot !"),
    _("Veuillez séléctionner un trajet !"),
    _("Pas de connection à internet !"),
    _("Erreur lors du lancement de la fenetre du jeu !"),
    _("Veuillez séléctionner un fichier d'options Combat/Métier !"),
    _("Aucun fichier Log IA existant !")
};


//(*IdInit(SufoBotFrame)
const long SufoBotFrame::ID_STATICBOX1 = wxNewId();
const long SufoBotFrame::ID_BUTTON1 = wxNewId();
const long SufoBotFrame::ID_BUTTON2 = wxNewId();
const long SufoBotFrame::ID_STATICBOX2 = wxNewId();
const long SufoBotFrame::ID_TEXTCTRL1 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON1 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX1 = wxNewId();
const long SufoBotFrame::ID_COMBOBOX1 = wxNewId();
const long SufoBotFrame::ID_BUTTON9 = wxNewId();
const long SufoBotFrame::ID_STATICBOX5 = wxNewId();
const long SufoBotFrame::ID_COMBOBOX2 = wxNewId();
const long SufoBotFrame::ID_BUTTON10 = wxNewId();
const long SufoBotFrame::ID_STATICBOX9 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX5 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX6 = wxNewId();
const long SufoBotFrame::ID_BUTTON15 = wxNewId();
const long SufoBotFrame::ID_STATICBOX16 = wxNewId();
const long SufoBotFrame::ID_COMBOBOX4 = wxNewId();
const long SufoBotFrame::ID_BUTTON18 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX11 = wxNewId();
const long SufoBotFrame::ID_PANEL1 = wxNewId();
const long SufoBotFrame::ID_STATICBOX3 = wxNewId();
const long SufoBotFrame::ID_LISTBOX1 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON2 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON3 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON4 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON5 = wxNewId();
const long SufoBotFrame::ID_BUTTON3 = wxNewId();
const long SufoBotFrame::ID_BUTTON4 = wxNewId();
const long SufoBotFrame::ID_STATICBOX4 = wxNewId();
const long SufoBotFrame::ID_BUTTON5 = wxNewId();
const long SufoBotFrame::ID_TEXTCTRL2 = wxNewId();
const long SufoBotFrame::ID_TEXTCTRL3 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX2 = wxNewId();
const long SufoBotFrame::ID_BUTTON6 = wxNewId();
const long SufoBotFrame::ID_BUTTON7 = wxNewId();
const long SufoBotFrame::ID_BUTTON8 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT1 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT2 = wxNewId();
const long SufoBotFrame::ID_STATICBOX6 = wxNewId();
const long SufoBotFrame::ID_BUTTON11 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL1 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX3 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT3 = wxNewId();
const long SufoBotFrame::ID_STATICBOX7 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON6 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON7 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON8 = wxNewId();
const long SufoBotFrame::ID_BITMAPBUTTON9 = wxNewId();
const long SufoBotFrame::ID_BUTTON12 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX4 = wxNewId();
const long SufoBotFrame::ID_BUTTON13 = wxNewId();
const long SufoBotFrame::ID_CHOICE1 = wxNewId();
const long SufoBotFrame::ID_STATICBOX8 = wxNewId();
const long SufoBotFrame::ID_CHOICE2 = wxNewId();
const long SufoBotFrame::ID_BUTTON14 = wxNewId();
const long SufoBotFrame::ID_STATICBOX19 = wxNewId();
const long SufoBotFrame::ID_BUTTON21 = wxNewId();
const long SufoBotFrame::ID_BUTTON22 = wxNewId();
const long SufoBotFrame::ID_PANEL2 = wxNewId();
const long SufoBotFrame::ID_STATICBOX12 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX7 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX8 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX9 = wxNewId();
const long SufoBotFrame::ID_STATICBOX13 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL2 = wxNewId();
const long SufoBotFrame::ID_STATICBOX14 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT4 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT5 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT6 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT7 = wxNewId();
const long SufoBotFrame::ID_CHOICE3 = wxNewId();
const long SufoBotFrame::ID_CHOICE4 = wxNewId();
const long SufoBotFrame::ID_CHOICE5 = wxNewId();
const long SufoBotFrame::ID_CHOICE6 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT8 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT9 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT10 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT11 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL3 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL4 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL5 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL6 = wxNewId();
const long SufoBotFrame::ID_STATICBOX15 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT12 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT13 = wxNewId();
const long SufoBotFrame::ID_CHOICE7 = wxNewId();
const long SufoBotFrame::ID_CHOICE8 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT14 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT15 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL7 = wxNewId();
const long SufoBotFrame::ID_SPINCTRL8 = wxNewId();
const long SufoBotFrame::ID_BUTTON16 = wxNewId();
const long SufoBotFrame::ID_BUTTON17 = wxNewId();
const long SufoBotFrame::ID_STATICBOX17 = wxNewId();
const long SufoBotFrame::ID_STATICTEXT16 = wxNewId();
const long SufoBotFrame::ID_CHOICE9 = wxNewId();
const long SufoBotFrame::ID_STATICBOX18 = wxNewId();
const long SufoBotFrame::ID_COMBOBOX5 = wxNewId();
const long SufoBotFrame::ID_BUTTON19 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX10 = wxNewId();
const long SufoBotFrame::ID_COLOURPICKERCTRL1 = wxNewId();
const long SufoBotFrame::ID_COLOURPICKERCTRL2 = wxNewId();
const long SufoBotFrame::ID_COLOURPICKERCTRL3 = wxNewId();
const long SufoBotFrame::ID_COLOURPICKERCTRL4 = wxNewId();
const long SufoBotFrame::ID_PANEL3 = wxNewId();
const long SufoBotFrame::ID_STATICBOX20 = wxNewId();
const long SufoBotFrame::ID_TEXTCTRL5 = wxNewId();
const long SufoBotFrame::ID_BUTTON23 = wxNewId();
const long SufoBotFrame::ID_BUTTON24 = wxNewId();
const long SufoBotFrame::ID_CHECKBOX12 = wxNewId();
const long SufoBotFrame::ID_STATICBOX21 = wxNewId();
const long SufoBotFrame::ID_PANEL4 = wxNewId();
const long SufoBotFrame::ID_STATICBOX10 = wxNewId();
const long SufoBotFrame::ID_TEXTCTRL4 = wxNewId();
const long SufoBotFrame::ID_STATICBOX11 = wxNewId();
const long SufoBotFrame::ID_COMBOBOX3 = wxNewId();
const long SufoBotFrame::ID_BUTTON20 = wxNewId();
const long SufoBotFrame::ID_PANEL5 = wxNewId();
const long SufoBotFrame::ID_NOTEBOOK1 = wxNewId();
const long SufoBotFrame::ID_MENUITEM2 = wxNewId();
const long SufoBotFrame::ID_MENUITEM1 = wxNewId();
const long SufoBotFrame::idMenuAbout = wxNewId();
const long SufoBotFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SufoBotFrame,wxFrame)
    //(*EventTable(SufoBotFrame)
    //*)
END_EVENT_TABLE()

// constr.

SufoBotFrame::SufoBotFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SufoBotFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("SufoBot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(480,694));
    SetMinSize(wxSize(480,694));
    SetMaxSize(wxSize(480,694));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("icons/Sad_robot.png"))));
    	SetIcon(FrameIcon);
    }
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(312,104), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticBox1 = new wxStaticBox(Panel1, ID_STATICBOX1, _("Fenetre du jeu"), wxPoint(8,8), wxSize(464,64), 0, _T("ID_STATICBOX1"));
    LancerBtn = new wxButton(Panel1, ID_BUTTON1, _("Lancer le bot"), wxPoint(320,256), wxSize(128,27), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StopBtn = new wxButton(Panel1, ID_BUTTON2, _("Stop"), wxPoint(320,296), wxSize(128,27), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StopBtn->Disable();
    StaticBox2 = new wxStaticBox(Panel1, ID_STATICBOX2, _("Console"), wxPoint(8,336), wxSize(464,264), 0, _T("ID_STATICBOX2"));
    txtConsole = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxPoint(16,360), wxSize(448,232), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    txtConsole->SetForegroundColour(wxColour(255,255,255));
    txtConsole->SetBackgroundColour(wxColour(0,0,0));
    refreshFenetresBtn = new wxBitmapButton(Panel1, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("icons/updateup.ico"))), wxPoint(200,32), wxSize(30,27), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    refreshFenetresBtn->SetToolTip(_("Refresh"));
    resizeFenetreCheck = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Redimensionner la fenetre"), wxPoint(16,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    resizeFenetreCheck->SetValue(true);
    listeFenetre = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxPoint(16,32), wxSize(176,27), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
    resizeBtn = new wxButton(Panel1, ID_BUTTON9, _("Redimensionner"), wxPoint(240,32), wxSize(136,27), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    StaticBox5 = new wxStaticBox(Panel1, ID_STATICBOX5, _("Trajet du bot"), wxPoint(8,80), wxSize(464,88), 0, _T("ID_STATICBOX5"));
    selectedTrajet = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxPoint(16,104), wxSize(304,27), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
    selectTrajetBtn = new wxButton(Panel1, ID_BUTTON10, _("Séléctionner"), wxPoint(328,104), wxSize(136,27), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    StaticBox9 = new wxStaticBox(Panel1, ID_STATICBOX9, _("Paramètres"), wxPoint(8,248), wxSize(288,80), 0, _T("ID_STATICBOX9"));
    laisserSourieCheck = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Laisser la sourie"), wxPoint(16,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    laisserSourieCheck->SetValue(true);
    repriseAutoCheck = new wxCheckBox(Panel1, ID_CHECKBOX6, _("Reprise automatique du trajet si arret forcé du bot"), wxPoint(16,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    repriseAutoCheck->SetValue(true);
    showHideFenetreBtn = new wxButton(Panel1, ID_BUTTON15, _("Afficher"), wxPoint(384,32), wxSize(77,27), 0, wxDefaultValidator, _T("ID_BUTTON15"));
    StaticBox16 = new wxStaticBox(Panel1, ID_STATICBOX16, _("Options de Combat/Métier"), wxPoint(8,176), wxSize(464,64), 0, _T("ID_STATICBOX16"));
    selectedOptCoMe = new wxComboBox(Panel1, ID_COMBOBOX4, wxEmptyString, wxPoint(16,200), wxSize(304,27), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX4"));
    selectOptCoMeBtn = new wxButton(Panel1, ID_BUTTON18, _("Séléctionner"), wxPoint(328,200), wxSize(136,27), 0, wxDefaultValidator, _T("ID_BUTTON18"));
    repeterTrajetCheck = new wxCheckBox(Panel1, ID_CHECKBOX11, _("Répeter le trajet"), wxPoint(152,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    repeterTrajetCheck->SetValue(false);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    StaticBox3 = new wxStaticBox(Panel2, ID_STATICBOX3, _("Nouveau Trajet (le début doit être fixe, ex : utilisation de potion)"), wxPoint(8,8), wxSize(464,280), 0, _T("ID_STATICBOX3"));
    listeTrajet = new wxListBox(Panel2, ID_LISTBOX1, wxPoint(280,24), wxSize(184,216), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    hautBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON2, wxBitmap(wxImage(_T("icons/up_arrow.png"))), wxPoint(64,32), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    droiteBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("icons/right_arrow.png"))), wxPoint(104,72), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    gaucheBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("icons/left_arrow.png"))), wxPoint(24,72), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    basBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON5, wxBitmap(wxImage(_T("icons/down_arrow.png"))), wxPoint(64,112), wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
    CombatBtn = new wxButton(Panel2, ID_BUTTON3, _("Combat"), wxPoint(176,32), wxSize(88,27), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    MetierBtn = new wxButton(Panel2, ID_BUTTON4, _("Métier"), wxPoint(176,64), wxSize(88,27), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StaticBox4 = new wxStaticBox(Panel2, ID_STATICBOX4, _("Mouse Position"), wxPoint(8,296), wxSize(464,88), 0, _T("ID_STATICBOX4"));
    PosClickBtn = new wxButton(Panel2, ID_BUTTON5, _("Click"), wxPoint(176,96), wxSize(88,27), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    txtX = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxPoint(48,320), wxSize(50,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    txtY = new wxTextCtrl(Panel2, ID_TEXTCTRL3, wxEmptyString, wxPoint(136,320), wxSize(50,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    GetMousePosCheck = new wxCheckBox(Panel2, ID_CHECKBOX2, _("Get Next Mouse Click Position"), wxPoint(16,352), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    GetMousePosCheck->SetValue(false);
    DeleteBtn = new wxButton(Panel2, ID_BUTTON6, _("Supprimer"), wxPoint(16,248), wxSize(112,27), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    DeleteAllBtn = new wxButton(Panel2, ID_BUTTON7, _("Tout supprimer"), wxPoint(136,248), wxSize(137,27), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    SaveTrajetBtn = new wxButton(Panel2, ID_BUTTON8, _("Enregistrer le trajet"), wxPoint(280,248), wxSize(184,27), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Y"), wxPoint(112,328), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("X"), wxPoint(24,328), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticBox6 = new wxStaticBox(Panel2, ID_STATICBOX6, _("Sleep/Stop"), wxPoint(16,152), wxSize(256,88), 0, _T("ID_STATICBOX6"));
    SleepBtn = new wxButton(Panel2, ID_BUTTON11, _("Sleep"), wxPoint(176,176), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    SleepSpinBox = new wxSpinCtrl(Panel2, ID_SPINCTRL1, _T("5"), wxPoint(24,176), wxSize(80,27), 0, 1, 60, 5, _T("ID_SPINCTRL1"));
    SleepSpinBox->SetValue(_T("5"));
    AutoAddSleepCheck = new wxCheckBox(Panel2, ID_CHECKBOX3, _("Auto Add Sleep"), wxPoint(24,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    AutoAddSleepCheck->SetValue(true);
    StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("seconds"), wxPoint(112,184), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticBox7 = new wxStaticBox(Panel2, ID_STATICBOX7, _("Simulation"), wxPoint(8,392), wxSize(464,208), 0, _T("ID_STATICBOX7"));
    hautSimulationBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON6, wxBitmap(wxImage(_T("icons/up_arrow.png"))), wxPoint(104,416), wxSize(40,40), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
    gaucheSimulationBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON7, wxBitmap(wxImage(_T("icons/left_arrow.png"))), wxPoint(40,464), wxSize(40,40), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
    droiteSimulationBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON8, wxBitmap(wxImage(_T("icons/right_arrow.png"))), wxPoint(168,464), wxSize(40,40), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
    basSimulationBtn = new wxBitmapButton(Panel2, ID_BITMAPBUTTON9, wxBitmap(wxImage(_T("icons/down_arrow.png"))), wxPoint(104,512), wxSize(40,40), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
    clickSimulationBtn = new wxButton(Panel2, ID_BUTTON12, _("Click"), wxPoint(96,472), wxSize(56,27), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    keepMouseCheck = new wxCheckBox(Panel2, ID_CHECKBOX4, _("Keep Mouse Here"), wxPoint(16,568), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    keepMouseCheck->SetValue(true);
    keyPressBtn = new wxButton(Panel2, ID_BUTTON13, _("KeyPress"), wxPoint(176,128), wxSize(88,27), 0, wxDefaultValidator, _T("ID_BUTTON13"));
    keyPressChoiceBox = new wxChoice(Panel2, ID_CHOICE1, wxPoint(120,128), wxSize(48,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    keyPressChoiceBox->SetSelection( keyPressChoiceBox->Append(_("1")) );
    keyPressChoiceBox->Append(_("2"));
    keyPressChoiceBox->Append(_("3"));
    keyPressChoiceBox->Append(_("4"));
    keyPressChoiceBox->Append(_("5"));
    keyPressChoiceBox->Append(_("6"));
    keyPressChoiceBox->Append(_("7"));
    keyPressChoiceBox->Append(_("8"));
    keyPressChoiceBox->Append(_("9"));
    keyPressChoiceBox->Append(_("0"));
    keyPressChoiceBox->Append(_("CTRL+1"));
    keyPressChoiceBox->Append(_("CTRL+2"));
    keyPressChoiceBox->Append(_("CTRL+3"));
    keyPressChoiceBox->Append(_("CTRL+4"));
    keyPressChoiceBox->Append(_("CTRL+5"));
    keyPressChoiceBox->Append(_("CTRL+6"));
    keyPressChoiceBox->Append(_("CTRL+7"));
    keyPressChoiceBox->Append(_("CTRL+8"));
    keyPressChoiceBox->Append(_("CTRL+9"));
    keyPressChoiceBox->Append(_("CTRL+0"));
    StaticBox8 = new wxStaticBox(Panel2, ID_STATICBOX8, _("KeyPress Simulation"), wxPoint(256,456), wxSize(184,64), 0, _T("ID_STATICBOX8"));
    keyPressSimulationChoiceBox = new wxChoice(Panel2, ID_CHOICE2, wxPoint(264,480), wxSize(64,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    keyPressSimulationChoiceBox->SetSelection( keyPressSimulationChoiceBox->Append(_("c")) );
    keyPressSimulationChoiceBox->Append(_("s"));
    keyPressSimulationChoiceBox->Append(_("i"));
    keyPressSimulationChoiceBox->Append(_("q"));
    keyPressSimulationChoiceBox->Append(_("m"));
    keyPressSimulationChoiceBox->Append(_("f"));
    keyPressSimulationChoiceBox->Append(_("e"));
    keyPressSimulationChoiceBox->Append(_("u"));
    keyPressSimulationChoiceBox->Append(_("x"));
    keyPressSimulationChoiceBox->Append(_("h"));
    keyPressSimulationChoiceBox->Append(_("j"));
    keyPressSimulationChoiceBox->Append(_("+"));
    keyPressSimulationChoiceBox->Append(_("ALT+-"));
    keyPressSimulationBtn = new wxButton(Panel2, ID_BUTTON14, _("KeyPress"), wxPoint(336,480), wxSize(93,27), 0, wxDefaultValidator, _T("ID_BUTTON14"));
    StaticBox19 = new wxStaticBox(Panel2, ID_STATICBOX19, _("Pixel Color using X,Y Position"), wxPoint(248,312), wxSize(216,64), 0, _T("ID_STATICBOX19"));
    getPixelColorBtn = new wxButton(Panel2, ID_BUTTON21, _("Get Pixel Color"), wxPoint(264,336), wxSize(184,27), 0, wxDefaultValidator, _T("ID_BUTTON21"));
    stopTrajetBtn = new wxButton(Panel2, ID_BUTTON22, _("Stop"), wxPoint(176,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON22"));
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    StaticBox12 = new wxStaticBox(Panel3, ID_STATICBOX12, _("Options générales"), wxPoint(8,8), wxSize(464,104), 0, _T("ID_STATICBOX12"));
    CheckBox1 = new wxCheckBox(Panel3, ID_CHECKBOX7, _("Activer le mode tactique si désactivé"), wxPoint(16,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox1->SetValue(true);
    CheckBox1->Disable();
    CheckBox2 = new wxCheckBox(Panel3, ID_CHECKBOX8, _("Activer le mode miniature si désactivé"), wxPoint(16,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox2->SetValue(true);
    CheckBox2->Disable();
    CheckBox3 = new wxCheckBox(Panel3, ID_CHECKBOX9, _("Fermer le combat et le mode spectateur"), wxPoint(16,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBox3->SetValue(true);
    CheckBox3->Disable();
    StaticBox13 = new wxStaticBox(Panel3, ID_STATICBOX13, _("Points d\'action"), wxPoint(328,32), wxSize(120,64), 0, _T("ID_STATICBOX13"));
    nombreDePA = new wxSpinCtrl(Panel3, ID_SPINCTRL2, _T("6"), wxPoint(336,56), wxDefaultSize, 0, 6, 12, 6, _T("ID_SPINCTRL2"));
    nombreDePA->SetValue(_T("6"));
    StaticBox14 = new wxStaticBox(Panel3, ID_STATICBOX14, _("Attaque"), wxPoint(8,120), wxSize(464,160), 0, _T("ID_STATICBOX14"));
    StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT4, _("Corps à corps (*)"), wxPoint(16,152), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(Panel3, ID_STATICTEXT5, _("Sort d\'attaque principal (*)"), wxPoint(16,184), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(Panel3, ID_STATICTEXT6, _("Sort d\'attaque en ligne droite"), wxPoint(16,216), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText7 = new wxStaticText(Panel3, ID_STATICTEXT7, _("Sort d\'attaque en diagonale"), wxPoint(16,248), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    attaqueCaC = new wxChoice(Panel3, ID_CHOICE3, wxPoint(224,144), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    attaqueCaC->SetSelection( attaqueCaC->Append(_("1")) );
    attaqueCaC->Append(_("2"));
    attaqueCaC->Append(_("3"));
    attaqueCaC->Append(_("4"));
    attaqueCaC->Append(_("5"));
    attaqueCaC->Append(_("6"));
    attaqueCaC->Append(_("7"));
    attaqueCaC->Append(_("8"));
    attaqueCaC->Append(_("9"));
    attaqueCaC->Append(_("0"));
    attaqueCaC->Append(_("CTRL+1"));
    attaqueCaC->Append(_("CTRL+2"));
    attaqueCaC->Append(_("CTRL+3"));
    attaqueCaC->Append(_("CTRL+4"));
    attaqueCaC->Append(_("CTRL+5"));
    attaqueCaC->Append(_("CTRL+6"));
    attaqueCaC->Append(_("CTRL+7"));
    attaqueCaC->Append(_("CTRL+8"));
    attaqueCaC->Append(_("CTRL+9"));
    attaqueCaC->Append(_("CTRL+0"));
    attaquePrincipale = new wxChoice(Panel3, ID_CHOICE4, wxPoint(224,176), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    attaquePrincipale->Append(_("1"));
    attaquePrincipale->Append(_("2"));
    attaquePrincipale->Append(_("3"));
    attaquePrincipale->Append(_("4"));
    attaquePrincipale->SetSelection( attaquePrincipale->Append(_("5")) );
    attaquePrincipale->Append(_("6"));
    attaquePrincipale->Append(_("7"));
    attaquePrincipale->Append(_("8"));
    attaquePrincipale->Append(_("9"));
    attaquePrincipale->Append(_("0"));
    attaquePrincipale->Append(_("CTRL+1"));
    attaquePrincipale->Append(_("CTRL+2"));
    attaquePrincipale->Append(_("CTRL+3"));
    attaquePrincipale->Append(_("CTRL+4"));
    attaquePrincipale->Append(_("CTRL+5"));
    attaquePrincipale->Append(_("CTRL+6"));
    attaquePrincipale->Append(_("CTRL+7"));
    attaquePrincipale->Append(_("CTRL+8"));
    attaquePrincipale->Append(_("CTRL+9"));
    attaquePrincipale->Append(_("CTRL+0"));
    attaqueLigneDroite = new wxChoice(Panel3, ID_CHOICE5, wxPoint(224,208), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    attaqueLigneDroite->Append(_("None"));
    attaqueLigneDroite->Append(_("1"));
    attaqueLigneDroite->Append(_("2"));
    attaqueLigneDroite->Append(_("3"));
    attaqueLigneDroite->Append(_("4"));
    attaqueLigneDroite->Append(_("5"));
    attaqueLigneDroite->SetSelection( attaqueLigneDroite->Append(_("6")) );
    attaqueLigneDroite->Append(_("7"));
    attaqueLigneDroite->Append(_("8"));
    attaqueLigneDroite->Append(_("9"));
    attaqueLigneDroite->Append(_("0"));
    attaqueLigneDroite->Append(_("CTRL+1"));
    attaqueLigneDroite->Append(_("CTRL+2"));
    attaqueLigneDroite->Append(_("CTRL+3"));
    attaqueLigneDroite->Append(_("CTRL+4"));
    attaqueLigneDroite->Append(_("CTRL+5"));
    attaqueLigneDroite->Append(_("CTRL+6"));
    attaqueLigneDroite->Append(_("CTRL+7"));
    attaqueLigneDroite->Append(_("CTRL+8"));
    attaqueLigneDroite->Append(_("CTRL+9"));
    attaqueLigneDroite->Append(_("CTRL+0"));
    attaqueDiagonale = new wxChoice(Panel3, ID_CHOICE6, wxPoint(224,240), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
    attaqueDiagonale->Append(_("None"));
    attaqueDiagonale->Append(_("1"));
    attaqueDiagonale->SetSelection( attaqueDiagonale->Append(_("2")) );
    attaqueDiagonale->Append(_("3"));
    attaqueDiagonale->Append(_("4"));
    attaqueDiagonale->Append(_("5"));
    attaqueDiagonale->Append(_("6"));
    attaqueDiagonale->Append(_("7"));
    attaqueDiagonale->Append(_("8"));
    attaqueDiagonale->Append(_("9"));
    attaqueDiagonale->Append(_("0"));
    attaqueDiagonale->Append(_("CTRL+1"));
    attaqueDiagonale->Append(_("CTRL+2"));
    attaqueDiagonale->Append(_("CTRL+3"));
    attaqueDiagonale->Append(_("CTRL+4"));
    attaqueDiagonale->Append(_("CTRL+5"));
    attaqueDiagonale->Append(_("CTRL+6"));
    attaqueDiagonale->Append(_("CTRL+7"));
    attaqueDiagonale->Append(_("CTRL+8"));
    attaqueDiagonale->Append(_("CTRL+9"));
    attaqueDiagonale->Append(_("CTRL+0"));
    StaticText8 = new wxStaticText(Panel3, ID_STATICTEXT8, _("PA requis"), wxPoint(320,152), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText9 = new wxStaticText(Panel3, ID_STATICTEXT9, _("PA requis"), wxPoint(320,184), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText10 = new wxStaticText(Panel3, ID_STATICTEXT10, _("PA requis"), wxPoint(320,216), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText11 = new wxStaticText(Panel3, ID_STATICTEXT11, _("PA requis"), wxPoint(320,248), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    attaqueCaCPA = new wxSpinCtrl(Panel3, ID_SPINCTRL3, _T("3"), wxPoint(392,144), wxSize(64,27), 0, 1, 10, 3, _T("ID_SPINCTRL3"));
    attaqueCaCPA->SetValue(_T("3"));
    attaquePrincipalePA = new wxSpinCtrl(Panel3, ID_SPINCTRL4, _T("3"), wxPoint(392,176), wxSize(63,27), 0, 1, 10, 3, _T("ID_SPINCTRL4"));
    attaquePrincipalePA->SetValue(_T("3"));
    attaqueLigneDroitePA = new wxSpinCtrl(Panel3, ID_SPINCTRL5, _T("4"), wxPoint(392,208), wxSize(63,27), 0, 1, 10, 4, _T("ID_SPINCTRL5"));
    attaqueLigneDroitePA->SetValue(_T("4"));
    attaqueDiagonalePA = new wxSpinCtrl(Panel3, ID_SPINCTRL6, _T("4"), wxPoint(392,240), wxSize(63,27), 0, 1, 10, 4, _T("ID_SPINCTRL6"));
    attaqueDiagonalePA->SetValue(_T("4"));
    StaticBox15 = new wxStaticBox(Panel3, ID_STATICBOX15, _("Boost"), wxPoint(8,288), wxSize(464,96), 0, _T("ID_STATICBOX15"));
    StaticText12 = new wxStaticText(Panel3, ID_STATICTEXT12, _("Sort de boost 1"), wxPoint(16,320), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    StaticText13 = new wxStaticText(Panel3, ID_STATICTEXT13, _("Sort de boost 2"), wxPoint(16,352), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    boost1 = new wxChoice(Panel3, ID_CHOICE7, wxPoint(224,312), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
    boost1->Append(_("None"));
    boost1->Append(_("1"));
    boost1->Append(_("2"));
    boost1->Append(_("3"));
    boost1->Append(_("4"));
    boost1->Append(_("5"));
    boost1->Append(_("6"));
    boost1->SetSelection( boost1->Append(_("7")) );
    boost1->Append(_("8"));
    boost1->Append(_("9"));
    boost1->Append(_("0"));
    boost1->Append(_("CTRL+1"));
    boost1->Append(_("CTRL+2"));
    boost1->Append(_("CTRL+3"));
    boost1->Append(_("CTRL+4"));
    boost1->Append(_("CTRL+5"));
    boost1->Append(_("CTRL+6"));
    boost1->Append(_("CTRL+7"));
    boost1->Append(_("CTRL+8"));
    boost1->Append(_("CTRL+9"));
    boost1->Append(_("CTRL+0"));
    boost2 = new wxChoice(Panel3, ID_CHOICE8, wxPoint(224,344), wxSize(88,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE8"));
    boost2->SetSelection( boost2->Append(_("None")) );
    boost2->Append(_("1"));
    boost2->Append(_("2"));
    boost2->Append(_("3"));
    boost2->Append(_("4"));
    boost2->Append(_("5"));
    boost2->Append(_("6"));
    boost2->Append(_("7"));
    boost2->Append(_("8"));
    boost2->Append(_("9"));
    boost2->Append(_("0"));
    boost2->Append(_("CTRL+1"));
    boost2->Append(_("CTRL+2"));
    boost2->Append(_("CTRL+3"));
    boost2->Append(_("CTRL+4"));
    boost2->Append(_("CTRL+5"));
    boost2->Append(_("CTRL+6"));
    boost2->Append(_("CTRL+7"));
    boost2->Append(_("CTRL+8"));
    boost2->Append(_("CTRL+9"));
    boost2->Append(_("CTRL+0"));
    StaticText14 = new wxStaticText(Panel3, ID_STATICTEXT14, _("PA requis"), wxPoint(320,320), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    StaticText15 = new wxStaticText(Panel3, ID_STATICTEXT15, _("PA requis"), wxPoint(320,352), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    boost1PA = new wxSpinCtrl(Panel3, ID_SPINCTRL7, _T("3"), wxPoint(392,312), wxSize(63,27), 0, 1, 10, 3, _T("ID_SPINCTRL7"));
    boost1PA->SetValue(_T("3"));
    boost2PA = new wxSpinCtrl(Panel3, ID_SPINCTRL8, _T("2"), wxPoint(392,344), wxSize(63,27), 0, 1, 10, 2, _T("ID_SPINCTRL8"));
    boost2PA->SetValue(_T("2"));
    simulerCombatBtn = new wxButton(Panel3, ID_BUTTON16, _("Simuler Combat"), wxPoint(8,560), wxSize(144,27), 0, wxDefaultValidator, _T("ID_BUTTON16"));
    EnregistrerOptionsCoMeBtn = new wxButton(Panel3, ID_BUTTON17, _("Enregistrer les options de combat/métier"), wxPoint(160,560), wxSize(309,27), 0, wxDefaultValidator, _T("ID_BUTTON17"));
    StaticBox17 = new wxStaticBox(Panel3, ID_STATICBOX17, _("Métier"), wxPoint(8,392), wxSize(464,128), 0, _T("ID_STATICBOX17"));
    StaticText16 = new wxStaticText(Panel3, ID_STATICTEXT16, _("Ressource à récolter"), wxPoint(16,424), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    RessourceChoice = new wxChoice(Panel3, ID_CHOICE9, wxPoint(160,416), wxSize(144,27), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE9"));
    RessourceChoice->SetSelection( RessourceChoice->Append(_("Blé")) );
    RessourceChoice->Append(_("Avoine"));
    RessourceChoice->Append(_("Bois de frêne"));
    StaticBox18 = new wxStaticBox(Panel3, ID_STATICBOX18, _("Trajet banque"), wxPoint(16,448), wxSize(448,64), 0, _T("ID_STATICBOX18"));
    selectedTrajetBanque = new wxComboBox(Panel3, ID_COMBOBOX5, wxEmptyString, wxPoint(24,472), wxSize(280,27), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
    selectBanqueTrajetBtn = new wxButton(Panel3, ID_BUTTON19, _("Séléctionner"), wxPoint(312,472), wxSize(144,27), 0, wxDefaultValidator, _T("ID_BUTTON19"));
    CheckBox4 = new wxCheckBox(Panel3, ID_CHECKBOX10, _("Détection automatique des aggressions au cours d\'un trajet"), wxPoint(8,528), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    CheckBox4->SetValue(true);
    CheckBox4->Disable();
    ressourceColor1 = new wxColourPickerCtrl(Panel3, ID_COLOURPICKERCTRL1, wxColour(255,223,0), wxPoint(312,416), wxSize(32,27), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    ressourceColor2 = new wxColourPickerCtrl(Panel3, ID_COLOURPICKERCTRL2, wxColour(246,222,86), wxPoint(352,416), wxSize(32,27), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL2"));
    ressourceColor3 = new wxColourPickerCtrl(Panel3, ID_COLOURPICKERCTRL3, wxColour(220,207,36), wxPoint(392,416), wxSize(32,27), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL3"));
    ressourceColor4 = new wxColourPickerCtrl(Panel3, ID_COLOURPICKERCTRL4, wxColour(190,181,40), wxPoint(432,416), wxSize(32,27), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL4"));
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    StaticBox20 = new wxStaticBox(Panel4, ID_STATICBOX20, _("Log Combat"), wxPoint(8,72), wxSize(464,520), 0, _T("ID_STATICBOX20"));
    txtIALog = new wxTextCtrl(Panel4, ID_TEXTCTRL5, wxEmptyString, wxPoint(16,96), wxSize(448,488), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    txtIALog->SetForegroundColour(wxColour(255,255,255));
    txtIALog->SetBackgroundColour(wxColour(0,0,0));
    actualiserIALogBtn = new wxButton(Panel4, ID_BUTTON23, _("Actualiser"), wxPoint(104,72), wxSize(85,19), 0, wxDefaultValidator, _T("ID_BUTTON23"));
    actualiserIALogBtn->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    resetIALogBtn = new wxButton(Panel4, ID_BUTTON24, _("Reset"), wxPoint(376,72), wxSize(85,19), 0, wxDefaultValidator, _T("ID_BUTTON24"));
    activerLogIACheck = new wxCheckBox(Panel4, ID_CHECKBOX12, _("Activer Log IA (peut ralentir l\'IA)"), wxPoint(16,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    activerLogIACheck->SetValue(true);
    StaticBox21 = new wxStaticBox(Panel4, ID_STATICBOX21, _("Options"), wxPoint(8,8), wxSize(464,56), 0, _T("ID_STATICBOX21"));
    Panel5 = new wxPanel(Notebook1, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    StaticBox10 = new wxStaticBox(Panel5, ID_STATICBOX10, _("Chemin du jeu"), wxPoint(8,8), wxSize(464,64), 0, _T("ID_STATICBOX10"));
    gamePathTxt = new wxTextCtrl(Panel5, ID_TEXTCTRL4, _("/home/dev/[Fav]/Dofus/bin/Dofus"), wxPoint(16,32), wxSize(352,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    StaticBox11 = new wxStaticBox(Panel5, ID_STATICBOX11, _("Personnage par défaut"), wxPoint(8,80), wxSize(208,64), 0, _T("ID_STATICBOX11"));
    defaultPersoCombo = new wxComboBox(Panel5, ID_COMBOBOX3, wxEmptyString, wxPoint(16,104), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    defaultPersoCombo->SetSelection( defaultPersoCombo->Append(_("Nom_Perso")) );
    LancerJeuBtn = new wxButton(Panel5, ID_BUTTON20, _("Lancer"), wxPoint(376,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON20"));
    Notebook1->AddPage(Panel1, _("Bot"), false);
    Notebook1->AddPage(Panel2, _("Trajet"), false);
    Notebook1->AddPage(Panel3, _("Combat/Métier"), false);
    Notebook1->AddPage(Panel4, _("IA"), false);
    Notebook1->AddPage(Panel5, _("Jeu"), false);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM2, _("Launch Game Window"), _("Launch the game window"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnLancerBtnClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnStopBtnClick);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnrefreshFenetresBtnClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnresizeBtnClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnselectTrajetBtnClick);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnrepriseAutoCheckClick);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnshowHideFenetreBtnClick);
    Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnselectOptCoMeBtnClick);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnhautBtnClick);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OndroiteBtnClick);
    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OngaucheBtnClick);
    Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnbasBtnClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnCombatBtnClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnMetierBtnClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnPosClickBtnClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnGetMousePosCheckClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnDeleteLastBtnClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnDeleteAllBtnClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnSaveTrajetBtnClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnSleepBtnClick);
    Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnhautSimulationBtnClick);
    Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OngaucheSimulationBtnClick);
    Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OndroiteSimulationBtnClick);
    Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnbasSimulationBtnClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnclickSimulationBtnClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnkeyPressBtnClick);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnkeyPressSimulationBtnClick);
    Connect(ID_BUTTON21,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OngetPixelColorBtnClick);
    Connect(ID_BUTTON22,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnstopTrajetBtnClick);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnsimulerCombatBtnClick);
    Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnEnregistrerOptionsCombatBtnClick);
    Connect(ID_CHOICE9,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SufoBotFrame::OnRessourceChoiceSelect);
    Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnselectBanqueTrajetBtnClick);
    Connect(ID_BUTTON23,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnactualiserIALogBtnClick);
    Connect(ID_BUTTON24,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnresetIALogBtnClick);
    Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnactiverLogIACheckClick);
    Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SufoBotFrame::OnLancerJeuBtnClick);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SufoBotFrame::OnLaunchGameWindow);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SufoBotFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SufoBotFrame::OnAbout);
    //*)

    // after drawing GUI

    // 1 - moving Bot window to right
    DesktopWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    //GetClientSize(&BotWidth, &BotHeight);
    BotWidth = 480;
    GameWidth = DesktopWidth - BotWidth; // == Bot X Position
    GameHeight = BotHeight = 694;
    Move(wxPoint(GameWidth, -1));

    // 2 - getting all running windows name
    display = XOpenDisplay(NULL); // display declared global
    if(display == NULL)
    {
        fprintf(stderr, "Error cannot open display !\n");
        exit(EXIT_FAILURE);
    }

    unsigned long len;
    char *curWinName;

    winList = list(display, &len); // get all windows list (winList declared global)

    for (int i = 0; i < (int)len; i++)
    {
        curWinName = name(display, winList[i]); // get window name

        wxString mystring(curWinName, wxConvUTF8); // convert to wxstring format

        listeFenetre->Append(mystring); // add to combobox
        if (mystring == defaultPersoCombo->GetValue()) // Selection par défaut si trouvé
            listeFenetre->Select(i);

        XFree(curWinName);
    }

    // 3 - Start Bot log
    AppendToLogAndConsole(_("Démarrage"), txtConsole);
}

// destr.

SufoBotFrame::~SufoBotFrame()
{
    //(*Destroy(SufoBotFrame)
    //*)
}

// Menu events

void SufoBotFrame::OnQuit(wxCommandEvent& event)
{
    // delete pointers (may crash the app)
    //delete mp;
    //delete bt;
    // free all windows liste
    XFree(winList);

    if (display != NULL)
        XCloseDisplay(display); // closing display
    Close();
}

void SufoBotFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(_("\tSufoBot v1.0 by AXeL\n\n") + msg, _("About SufoBot"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnLaunchGameWindow(wxCommandEvent& event)
{
    wxProcess* process = wxProcess::Open(gamePathTxt->GetValue());
    if (process == NULL)
        wxMessageBox(msgErreur[9], _("Erreur"), wxOK | wxCENTER, this);
}

// Bot (Onglet)

void SufoBotFrame::OnrefreshFenetresBtnClick(wxCommandEvent& event)
{
    // Clear
    listeFenetre->Clear();
    XFree(winList);

    // get new one
    unsigned long len;
    char *curWinName;

    // get all windows list
    winList = list(display, &len); // winList declared global

    for (int i = 0; i < (int)len; i++)
    {
        curWinName = name(display, winList[i]); // get window name

        wxString mystring(curWinName, wxConvUTF8); // convert to wxstring format

        listeFenetre->Append(mystring); // add to combobox

        if (mystring == defaultPersoCombo->GetValue()) // Selection par défaut si trouvé
            listeFenetre->Select(i);

        XFree(curWinName);
    }
}

// << Lancer Bot Button >>

void SufoBotFrame::OnLancerBtnClick(wxCommandEvent& event)
{
    // si fenetre du jeu non séléctionnée
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[0], _("Erreur"), wxOK | wxCENTER, this);
    else if (selectedTrajet->GetSelection() == -1) // si nn si trajet non séléctionné
        wxMessageBox(msgErreur[7], _("Erreur"), wxOK | wxCENTER, this);
    else if (selectedOptCoMe->GetSelection() == -1) // si nn si fichier d'options Combat/Métier non séléctionné
        wxMessageBox(msgErreur[10], _("Erreur"), wxOK | wxCENTER, this);
    else if (!checkInternetConnection()) // si pas de connection à internet
        wxMessageBox(msgErreur[8], _("Erreur"), wxOK | wxCENTER, this);
    else
    {
        Window w = winList[listeFenetre->GetSelection()];

        if (resizeFenetreCheck->GetValue()) // if resize game window checked
        {
            // resizing game window
            XMoveResizeWindow(display, w, 0, 0, GameWidth, GameHeight);
            XFlush(display);

            // uncheck checkbox 'redimensionner la fenetre'
            resizeFenetreCheck->SetValue(false);
        }

        // raise window on top
        //XRaiseWindow (display, w);
        //XFlush(display);

        // set focus
        //XSetInputFocus (display, w, RevertToParent, CurrentTime);
        //XFlush(display);

        bool reprendre = repriseAutoCheck->GetValue();
        // log message
        if (autoRepriseIndex == -1) // si aucune reprise possible
            AppendToLogAndConsole(_("Lancement du bot '") + listeFenetre->GetValue() + _("'"), txtConsole);
        else
        {
            if (reprendre) // si on veux reprendre
                AppendToLogAndConsole(_("Reprise du bot '") + listeFenetre->GetValue() + _("'"), txtConsole);
            else // si nn si on ne veux pas reprendre
            {
                autoRepriseIndex = -1; // on ignore/rénitialise l'index de reprise alors
                AppendToLogAndConsole(_("Lancement du bot '") + listeFenetre->GetValue() + _("'"), txtConsole);
            }
        }
        // Launch bot thread
        bt = new BotThread(selectedTrajet->GetValue(), display, winList[listeFenetre->GetSelection()], GameWidth, GameHeight, LancerBtn, StopBtn, txtConsole, laisserSourieCheck->GetValue(), &autoRepriseIndex, repeterTrajetCheck->GetValue(), selectedOptCoMe->GetValue()); // construct our thread
        bt->Create(); // we have to create a thread before we can run it
        bt->Run(); // run our thread

        // Disable Lancer Button & Enable Stop Button
        LancerBtn->Enable(false);
        StopBtn->Enable(true);

        // set statusbar message
        //StatusBar1->SetStatusText(_("Bot en marche..."));
    }
}

void SufoBotFrame::OnresizeBtnClick(wxCommandEvent& event)
{
    int selected = listeFenetre->GetSelection();

    if (selected != -1)
    {
        Window w = winList[selected];

        // resizing game window
        XMoveResizeWindow(display, w, 0, 0, GameWidth, GameHeight);
        XFlush(display);

        // uncheck checkbox 'redimensionner la fenetre'
        resizeFenetreCheck->SetValue(false);
    }
    else
        wxMessageBox(msgErreur[0], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnselectTrajetBtnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(this, _("Séléctionner un trajet"), wxEmptyString, wxEmptyString, _("Text Files (*.txt)|*.txt"), wxFD_OPEN, wxDefaultPosition);

    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
        if (selectedTrajet->FindString(OpenDialog->GetPath()) == wxNOT_FOUND)
        {
            selectedTrajet->Append(OpenDialog->GetPath()); // add to combobox
            selectedTrajet->SetSelection(selectedTrajet->GetCount() - 1); // select last
            //wxMessageBox(_("Trajet ajouté et séléctionné !"), _("SufoBot"), wxOK | wxCENTER, this);
        }
        else
            wxMessageBox(_("Trajet existant !"), _("Erreur"), wxOK | wxCENTER, this);
    }

    // Clean up after ourselves
    OpenDialog->Destroy();
}

void SufoBotFrame::OnStopBtnClick(wxCommandEvent& event)
{
    if (bt->IsRunning())
    {
        StopBtn->Enable(false);
        bt->Delete();
        bt->Wait();
    }
}

void SufoBotFrame::OnrepriseAutoCheckClick(wxCommandEvent& event)
{
    if (!repriseAutoCheck->GetValue()) // if unchecked
    {
        wxMessageDialog *dial = new wxMessageDialog(this, _("Vous ne pourriez plus reprendre votre trajet !\n\t\tVoulez-vous continuer ?"), _("SufoBot"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION | wxCENTER);
        if (dial->ShowModal() == wxID_NO)
            repriseAutoCheck->SetValue(true);
    }
}

void SufoBotFrame::OnshowHideFenetreBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() != -1)
    {
        Window w = winList[listeFenetre->GetSelection()];
        //setWindowOntop(display, w, _NET_WM_STATE_TOGGLE);
        //showHideFenetreBtn->GetLabel() == _("Afficher") ? showHideFenetreBtn->SetLabel(_("Cacher")) : showHideFenetreBtn->SetLabel(_("Afficher"));
        if (showHideFenetreBtn->GetLabel() == _("Afficher"))
        {
            setWindowOntop(display, w, _NET_WM_STATE_ADD);
            showHideFenetreBtn->SetLabel(_("Cacher"));
        }
        else
        {
            setWindowOntop(display, w, _NET_WM_STATE_REMOVE);
            showHideFenetreBtn->SetLabel(_("Afficher"));
        }
    }
    else
        wxMessageBox(msgErreur[0], _("Erreur"), wxOK | wxCENTER, this);
}

// Trajet (Onglet)

void SufoBotFrame::OnhautBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[HAUT]"));
    if (AutoAddSleepCheck->GetValue()) // if 'Auto Add Sleep' checked
        OnSleepBtnClick(event); // we add Sleep
}

void SufoBotFrame::OndroiteBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[DROITE]"));
    if (AutoAddSleepCheck->GetValue())
        OnSleepBtnClick(event);
}

void SufoBotFrame::OnbasBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[BAS]"));
    if (AutoAddSleepCheck->GetValue())
        OnSleepBtnClick(event);
}

void SufoBotFrame::OngaucheBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[GAUCHE]"));
    if (AutoAddSleepCheck->GetValue())
        OnSleepBtnClick(event);
}

void SufoBotFrame::OnCombatBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[COMBAT]"));
}

void SufoBotFrame::OnMetierBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[METIER]"));
}

void SufoBotFrame::OnPosClickBtnClick(wxCommandEvent& event)
{
    if (txtX->GetValue().empty() || txtY->GetValue().empty())
    {
        wxMessageBox(msgErreur[1], _("Erreur"), wxOK | wxCENTER, this);
        txtX->SetFocus();
    }
    else if (!txtX->GetValue().IsNumber() || !txtY->GetValue().IsNumber())
    {
        wxMessageBox(msgErreur[2], _("Erreur"), wxOK | wxCENTER, this);
        txtX->SetFocus();
    }
    else
    {
        wxString str = _("[CLICK ") + txtX->GetValue() + _(",") + txtY->GetValue() + _("]");
        listeTrajet->AppendAndEnsureVisible(str);
        if (AutoAddSleepCheck->GetValue())
            OnSleepBtnClick(event);
    }
}

void SufoBotFrame::OnDeleteLastBtnClick(wxCommandEvent& event)
{
    int sel = listeTrajet->GetSelection();
    if (sel != -1)
        listeTrajet->Delete(sel);
    else
        wxMessageBox(msgErreur[3], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnDeleteAllBtnClick(wxCommandEvent& event)
{
    if (listeTrajet->GetCount() > 0)
        listeTrajet->Clear();
    else
        wxMessageBox(msgErreur[4], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnSaveTrajetBtnClick(wxCommandEvent& event)
{
    if (listeTrajet->GetCount() > 0)
    {
        wxFileDialog* OpenDialog = new wxFileDialog(this, _("Enregistrer le trajet sous..."), wxEmptyString, _("Trajet - ") + wxNow() + _(".txt"), _("Text Files (*.txt)|*.txt"), wxFD_SAVE, wxDefaultPosition);

        if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Save" instead of "Cancel"
        {
            // enregistrement/save
            wxArrayString list = listeTrajet->GetStrings();
            wxTextFile file(OpenDialog->GetPath());
            file.Create();

            size_t count = list.Count();
            for( size_t i = 0 ; i < count ; ++i )
                file.AddLine( list[ i ] );

            file.Write();
            file.Close();

            wxMessageBox(_("Trajet enregistré !"), _("SufoBot"), wxOK | wxCENTER, this);
        }

        // Clean up after ourselves
        OpenDialog->Destroy();
    }
    else
        wxMessageBox(msgErreur[5], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnGetMousePosCheckClick(wxCommandEvent& event)
{
    if (GetMousePosCheck->GetValue())
    {
        GetMousePosCheck->Enable(false); // disable checkbox
        mp = new MousePosition(txtX, txtY, GetMousePosCheck); // construct our thread
        mp->Create(); // we have to create a thread before we can run it
        mp->Run(); // run our thread
    }
}

void SufoBotFrame::OnSleepBtnClick(wxCommandEvent& event)
{
    wxString sleepTime;
    sleepTime << SleepSpinBox->GetValue();
    listeTrajet->AppendAndEnsureVisible(_("[SLEEP ") + sleepTime + _("]"));
}

void SufoBotFrame::OnstopTrajetBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[STOP]"));
}

void SufoBotFrame::OnhautSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
        simulateBotAction(_("[HAUT]"), GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], keepMouseCheck->GetValue());
}

void SufoBotFrame::OngaucheSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
        simulateBotAction(_("[GAUCHE]"), GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], keepMouseCheck->GetValue());
}

void SufoBotFrame::OndroiteSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
        simulateBotAction(_("[DROITE]"), GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], keepMouseCheck->GetValue());
}

void SufoBotFrame::OnbasSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
        simulateBotAction(_("[BAS]"), GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], keepMouseCheck->GetValue());
}

void SufoBotFrame::OnclickSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
    {
        // vérification des positions de la sourie X et Y
        if (txtX->GetValue().empty() || txtY->GetValue().empty())
        {
            wxMessageBox(msgErreur[1], _("Erreur"), wxOK | wxCENTER, this);
            txtX->SetFocus();
        }
        else if (!txtX->GetValue().IsNumber() || !txtY->GetValue().IsNumber())
        {
            wxMessageBox(msgErreur[2], _("Erreur"), wxOK | wxCENTER, this);
            txtX->SetFocus();
        }
        else
        {
            wxString str = _("[CLICK ") + txtX->GetValue() + _(",") + txtY->GetValue() + _("]");
            // simulation du click
            simulateBotAction(str, GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], keepMouseCheck->GetValue());
        }
    }
}

void SufoBotFrame::OnkeyPressBtnClick(wxCommandEvent& event)
{
    listeTrajet->AppendAndEnsureVisible(_("[KEYPRESS ") + keyPressChoiceBox->GetStringSelection() + _("]"));
    if (AutoAddSleepCheck->GetValue())
        OnSleepBtnClick(event);
}

void SufoBotFrame::OnkeyPressSimulationBtnClick(wxCommandEvent& event)
{
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[6], _("Erreur"), wxOK | wxCENTER, this);
    else
    {
        wxString str =_("[KEYPRESS ") + keyPressSimulationChoiceBox->GetStringSelection() + _("]");
        simulateBotAction(str, GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], false);
    }
}

// Combat/Métier (Onglet)

void SufoBotFrame::OnEnregistrerOptionsCombatBtnClick(wxCommandEvent& event)
{
    if (selectedTrajetBanque->GetSelection() == -1)
    {
        wxMessageBox(msgErreur[7], _("Erreur"), wxOK | wxCENTER, this);
        selectBanqueTrajetBtn->SetFocus();
    }
    else
    {
        wxFileDialog* OpenDialog = new wxFileDialog(this, _("Enregistrer sous..."), wxEmptyString, _("Options - ") + wxNow() + _(".sufo"), _("SufoBot Files (*.sufo)|*.sufo"), wxFD_SAVE, wxDefaultPosition);

        if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Save" instead of "Cancel"
        {
            // enregistrement/save
            wxTextFile file(OpenDialog->GetPath());
            file.Create();

            wxString s;

            // first line
            file.AddLine(_("[COMBAT OPTIONS]"));
            // second line [nombre de PA]
            s << nombreDePA->GetValue();
            file.AddLine(s);
            // line 3 [attaque CAC]
            s.Clear();
            s << attaqueCaCPA->GetValue();
            file.AddLine(attaqueCaC->GetStringSelection() + _("|") + s);
            // line 4 [attaque Principale]
            s.Clear();
            s << attaquePrincipalePA->GetValue();
            file.AddLine(attaquePrincipale->GetStringSelection() + _("|") + s);
            // line 5 [attaque en ligne droite]
            s.Clear();
            s << attaqueLigneDroitePA->GetValue();
            file.AddLine(attaqueLigneDroite->GetStringSelection() + _("|") + s);
            // line 6 [attaque en diagonale]
            s.Clear();
            s << attaqueDiagonalePA->GetValue();
            file.AddLine(attaqueDiagonale->GetStringSelection() + _("|") + s);
            // line 7 [boost 1]
            s.Clear();
            s << boost1PA->GetValue();
            file.AddLine(boost1->GetStringSelection() + _("|") + s);
            // line 8 [boost 2]
            s.Clear();
            s << boost2PA->GetValue();
            file.AddLine(boost2->GetStringSelection() + _("|") + s);
            // line 9
            file.AddLine(_("[METIER OPTIONS]"));
            // line 10 [Ressource + 4 couleur]
            wxColour ressourceColor[4];
            ressourceColor[0] = ressourceColor1->GetColour();
            ressourceColor[1] = ressourceColor2->GetColour();
            ressourceColor[2] = ressourceColor3->GetColour();
            ressourceColor[3] = ressourceColor4->GetColour();

            file.AddLine(RessourceChoice->GetStringSelection() + _("|") + ressourceColor[0].GetAsString(wxC2S_HTML_SYNTAX) + _("|") + ressourceColor[1].GetAsString(wxC2S_HTML_SYNTAX) + _("|") + ressourceColor[2].GetAsString(wxC2S_HTML_SYNTAX) + _("|") + ressourceColor[3].GetAsString(wxC2S_HTML_SYNTAX));
            // line 11 [Fichier Trajet Banque]
            file.AddLine(selectedTrajetBanque->GetValue());

            file.Write();
            file.Close();

            wxMessageBox(_("Options enregistré !"), _("SufoBot"), wxOK | wxCENTER, this);
        }
        // Clean up after ourselves
        OpenDialog->Destroy();
    }

}

void SufoBotFrame::OnselectOptCoMeBtnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(this, _("Séléctionner un fichier d'options"), wxEmptyString, wxEmptyString, _("Sufo Files (*.sufo)|*.sufo"), wxFD_OPEN, wxDefaultPosition);

    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
        if (selectedOptCoMe->FindString(OpenDialog->GetPath()) == wxNOT_FOUND)
        {
            selectedOptCoMe->Append(OpenDialog->GetPath()); // add to combobox
            selectedOptCoMe->SetSelection(selectedOptCoMe->GetCount() - 1); // select last
        }
        else
            wxMessageBox(_("Fichier d'options existant !"), _("Erreur"), wxOK | wxCENTER, this);
    }

    // Clean up after ourselves
    OpenDialog->Destroy();
}

void SufoBotFrame::OnselectBanqueTrajetBtnClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog(this, _("Séléctionner un trajet banque"), wxEmptyString, wxEmptyString, _("Text Files (*.txt)|*.txt"), wxFD_OPEN, wxDefaultPosition);

    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
    {
        if (selectedTrajetBanque->FindString(OpenDialog->GetPath()) == wxNOT_FOUND)
        {
            selectedTrajetBanque->Append(OpenDialog->GetPath()); // add to combobox
            selectedTrajetBanque->SetSelection(selectedTrajetBanque->GetCount() - 1); // select last
            //wxMessageBox(_("Trajet ajouté et séléctionné !"), _("SufoBot"), wxOK | wxCENTER, this);
        }
        else
            wxMessageBox(_("Trajet banque existant !"), _("Erreur"), wxOK | wxCENTER, this);
    }

    // Clean up after ourselves
    OpenDialog->Destroy();
}

void SufoBotFrame::OnRessourceChoiceSelect(wxCommandEvent& event)
{
    switch (RessourceChoice->GetSelection())
    {
        case 0: // Blé
            ressourceColor1->SetColour(wxColour(253, 232, 52));
            ressourceColor2->SetColour(wxColour(247, 192, 29));
            ressourceColor3->SetColour(wxColour(252, 241, 59));
            ressourceColor4->SetColour(wxColour(249, 222, 56));
            break;
        case 1: // Avoine
            ressourceColor1->SetColour(wxColour(251, 235, 187));
            ressourceColor2->SetColour(wxColour(244, 237, 128));
            ressourceColor3->SetColour(wxColour(209, 163, 94));
            ressourceColor4->SetColour(wxColour(208, 174, 93));
            break;
        case 2: // Bois Frêne
            ressourceColor1->SetColour(wxColour(158, 137, 63));
            ressourceColor2->SetColour(wxColour(109, 96, 44));
            ressourceColor3->SetColour(wxColour(196, 227, 23));
            ressourceColor4->SetColour(wxColour(213, 227, 25));
            break;
    }
}

void SufoBotFrame::OnsimulerCombatBtnClick(wxCommandEvent& event)
{
    // affichage de l'onglet Bot
    Notebook1->SetSelection(0);
    // si fenetre du jeu non séléctionné
    if (listeFenetre->GetSelection() == -1)
        wxMessageBox(msgErreur[0], _("Erreur"), wxOK | wxCENTER, this);
    else if (selectedOptCoMe->GetSelection() == -1) // si nn si fichier d'options Combat/Métier non séléctionné
        wxMessageBox(msgErreur[10], _("Erreur"), wxOK | wxCENTER, this);
    else
    {
        // Désactivation du boutton de simulation de combat
        simulerCombatBtn->Enable(false);
        // Launch Combat thread
        SimulerCombatThread* ct = new SimulerCombatThread(simulerCombatBtn, GameWidth, GameHeight, display, winList[listeFenetre->GetSelection()], DefaultRootWindow(display), selectedOptCoMe->GetValue(), txtConsole); // construct our thread
        ct->Create(); // we have to create a thread before we can run it
        ct->Run(); // run our thread
    }
}

void SufoBotFrame::OngetPixelColorBtnClick(wxCommandEvent& event)
{
    // vérification des positions de la sourie X et Y
    if (txtX->GetValue().empty() || txtY->GetValue().empty())
    {
        wxMessageBox(msgErreur[1], _("Erreur"), wxOK | wxCENTER, this);
        txtX->SetFocus();
    }
    else if (!txtX->GetValue().IsNumber() || !txtY->GetValue().IsNumber())
    {
        wxMessageBox(msgErreur[2], _("Erreur"), wxOK | wxCENTER, this);
        txtX->SetFocus();
    }
    else
    {
        XColor c;
        getPixelColor(display, wxAtoi(txtX->GetValue()), wxAtoi(txtY->GetValue()), &c);
        wxString s;
        s << _("Red : ") << c.red/256 << _(" Blue : ") << c.blue/256 << _(" Green : ") << c.green/256;
        wxMessageBox(s, _("SufoBot"), wxOK | wxCENTER, this);
    }
}

// IA (Onglet)

void SufoBotFrame::OnactualiserIALogBtnClick(wxCommandEvent& event)
{
    // get date & time
    wxDateTime dt = wxDateTime::Now();
    // open Log File
    wxTextFile file(dt.FormatISODate() + _("_IA.txt"));
    if (file.Exists()) // si le fichier existe
    {
        file.Open();
        // on récupère le nombre de ligne
        int line = 0, lastLine = file.GetLineCount() - 1; // -1 car line commence de 0
        // on efface les anciens log (s'ils existent deja)
        txtIALog->Clear();
        // on récupère le contenu du fichier Log
        txtIALog->AppendText(file.GetFirstLine() + _("\n")); // 1ère ligne
        while(!file.Eof())
        {
            txtIALog->AppendText(file.GetNextLine() + (line == lastLine ? _("") : _("\n"))); // si c la dernière ligne on n'ajoute pas de retour à la ligne
            line++;
        }
        file.Close();
    }
    else
        wxMessageBox(msgErreur[11], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnresetIALogBtnClick(wxCommandEvent& event)
{
    // get date & time
    wxDateTime dt = wxDateTime::Now();
    // open Log File & reset it
    wxTextFile file(dt.FormatISODate() + _("_IA.txt"));
    if (file.Exists())
    {
        file.Create();
        file.AddLine(_("[IA Log]"));
        file.Write();
        file.Close();
        // on actualise la zone d'affichage du log
        OnactualiserIALogBtnClick(event);
    }
    else
        wxMessageBox(msgErreur[11], _("Erreur"), wxOK | wxCENTER, this);
}

void SufoBotFrame::OnactiverLogIACheckClick(wxCommandEvent& event)
{
    if (activerLogIACheck->GetValue()) // si activé/checked
    {
        actualiserIALogBtn->Enable(true);
        resetIALogBtn->Enable(true);
        activerLogIA = true;
    }
    else
    {
        actualiserIALogBtn->Enable(false);
        resetIALogBtn->Enable(false);
        activerLogIA = false;
    }
}

// Jeu (Onglet)

void SufoBotFrame::OnLancerJeuBtnClick(wxCommandEvent& event)
{
    OnLaunchGameWindow(event); // Exécution du meme even. que 'Launch Game Window' du Menu
}
