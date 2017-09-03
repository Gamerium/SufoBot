/***************************************************************
 * Name:      SufoBotMain.h
 * Purpose:   Defines Application Frame
 * Author:    AXeL (axel.prog.25@gmail.com)
 * Created:   2015-07-20
 * Copyright: AXeL ()
 * License:
 **************************************************************/

#ifndef SUFOBOTMAIN_H
#define SUFOBOTMAIN_H

//(*Headers(SufoBotFrame)
#include <wx/bmpbuttn.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/statbox.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/listbox.h>
//*)

class SufoBotFrame: public wxFrame
{
    public:

        SufoBotFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SufoBotFrame();

    private:

        //(*Handlers(SufoBotFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnlisteFenetreSelected(wxCommandEvent& event);
        void OnrefreshFenetresBtnClick(wxCommandEvent& event);
        void OnLancerBtnClick(wxCommandEvent& event);
        void OnhautBtnClick(wxCommandEvent& event);
        void OndroiteBtnClick(wxCommandEvent& event);
        void OnbasBtnClick(wxCommandEvent& event);
        void OngaucheBtnClick(wxCommandEvent& event);
        void OnCombatBtnClick(wxCommandEvent& event);
        void OnMetierBtnClick(wxCommandEvent& event);
        void OnPosClickBtnClick(wxCommandEvent& event);
        void OnDeleteLastBtnClick(wxCommandEvent& event);
        void OnDeleteAllBtnClick(wxCommandEvent& event);
        void OnSaveTrajetBtnClick(wxCommandEvent& event);
        void OnGetMousePosCheckClick(wxCommandEvent& event);
        void OnresizeBtnClick(wxCommandEvent& event);
        void OnselectTrajetBtnClick(wxCommandEvent& event);
        void OnSleepBtnClick(wxCommandEvent& event);
        void OnhautSimulationBtnClick(wxCommandEvent& event);
        void OngaucheSimulationBtnClick(wxCommandEvent& event);
        void OndroiteSimulationBtnClick(wxCommandEvent& event);
        void OnbasSimulationBtnClick(wxCommandEvent& event);
        void OnclickSimulationBtnClick(wxCommandEvent& event);
        void OnkeyPressBtnClick(wxCommandEvent& event);
        void OnkeyPressSimulationBtnClick(wxCommandEvent& event);
        void OnStopBtnClick(wxCommandEvent& event);
        void OnrepriseAutoCheckClick(wxCommandEvent& event);
        void OnLaunchGameWindow(wxCommandEvent& event);
        void OnshowHideFenetreBtnClick(wxCommandEvent& event);
        void OnresteAttaqueBtnClick(wxCommandEvent& event);
        void OnEnregistrerOptionsCombatBtnClick(wxCommandEvent& event);
        void OnselectOptCoMeBtnClick(wxCommandEvent& event);
        void OnselectBanqueTrajetBtnClick(wxCommandEvent& event);
        void OnRessourceChoiceSelect(wxCommandEvent& event);
        void OnLancerJeuBtnClick(wxCommandEvent& event);
        void OnsimulerCombatBtnClick(wxCommandEvent& event);
        void OngetPixelColorBtnClick(wxCommandEvent& event);
        void OnpauseBtnClick(wxCommandEvent& event);
        void OnstopTrajetBtnClick(wxCommandEvent& event);
        void OnactualiserIALogBtnClick(wxCommandEvent& event);
        void OnresetIALogBtnClick(wxCommandEvent& event);
        void OnactiverLogIACheckClick(wxCommandEvent& event);
        void OngamePathTxtText(wxCommandEvent& event);
        //*)

        //(*Identifiers(SufoBotFrame)
        static const long ID_STATICBOX1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_STATICBOX2;
        static const long ID_TEXTCTRL1;
        static const long ID_BITMAPBUTTON1;
        static const long ID_CHECKBOX1;
        static const long ID_COMBOBOX1;
        static const long ID_BUTTON9;
        static const long ID_STATICBOX5;
        static const long ID_COMBOBOX2;
        static const long ID_BUTTON10;
        static const long ID_STATICBOX9;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_BUTTON15;
        static const long ID_STATICBOX16;
        static const long ID_COMBOBOX4;
        static const long ID_BUTTON18;
        static const long ID_CHECKBOX11;
        static const long ID_PANEL1;
        static const long ID_STATICBOX3;
        static const long ID_LISTBOX1;
        static const long ID_BITMAPBUTTON2;
        static const long ID_BITMAPBUTTON3;
        static const long ID_BITMAPBUTTON4;
        static const long ID_BITMAPBUTTON5;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_STATICBOX4;
        static const long ID_BUTTON5;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_CHECKBOX2;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICBOX6;
        static const long ID_BUTTON11;
        static const long ID_SPINCTRL1;
        static const long ID_CHECKBOX3;
        static const long ID_STATICTEXT3;
        static const long ID_STATICBOX7;
        static const long ID_BITMAPBUTTON6;
        static const long ID_BITMAPBUTTON7;
        static const long ID_BITMAPBUTTON8;
        static const long ID_BITMAPBUTTON9;
        static const long ID_BUTTON12;
        static const long ID_CHECKBOX4;
        static const long ID_BUTTON13;
        static const long ID_CHOICE1;
        static const long ID_STATICBOX8;
        static const long ID_CHOICE2;
        static const long ID_BUTTON14;
        static const long ID_STATICBOX19;
        static const long ID_BUTTON21;
        static const long ID_BUTTON22;
        static const long ID_PANEL2;
        static const long ID_STATICBOX12;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX9;
        static const long ID_STATICBOX13;
        static const long ID_SPINCTRL2;
        static const long ID_STATICBOX14;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_CHOICE3;
        static const long ID_CHOICE4;
        static const long ID_CHOICE5;
        static const long ID_CHOICE6;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT11;
        static const long ID_SPINCTRL3;
        static const long ID_SPINCTRL4;
        static const long ID_SPINCTRL5;
        static const long ID_SPINCTRL6;
        static const long ID_STATICBOX15;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT13;
        static const long ID_CHOICE7;
        static const long ID_CHOICE8;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT15;
        static const long ID_SPINCTRL7;
        static const long ID_SPINCTRL8;
        static const long ID_BUTTON16;
        static const long ID_BUTTON17;
        static const long ID_STATICBOX17;
        static const long ID_STATICTEXT16;
        static const long ID_CHOICE9;
        static const long ID_STATICBOX18;
        static const long ID_COMBOBOX5;
        static const long ID_BUTTON19;
        static const long ID_CHECKBOX10;
        static const long ID_COLOURPICKERCTRL1;
        static const long ID_COLOURPICKERCTRL2;
        static const long ID_COLOURPICKERCTRL3;
        static const long ID_COLOURPICKERCTRL4;
        static const long ID_PANEL3;
        static const long ID_STATICBOX20;
        static const long ID_TEXTCTRL5;
        static const long ID_BUTTON23;
        static const long ID_BUTTON24;
        static const long ID_CHECKBOX12;
        static const long ID_STATICBOX21;
        static const long ID_PANEL4;
        static const long ID_STATICBOX10;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICBOX11;
        static const long ID_COMBOBOX3;
        static const long ID_BUTTON20;
        static const long ID_PANEL5;
        static const long ID_NOTEBOOK1;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SufoBotFrame)
        wxComboBox* selectedOptCoMe;
        wxButton* DeleteAllBtn;
        wxSpinCtrl* attaqueCaCPA;
        wxButton* resetIALogBtn;
        wxButton* selectTrajetBtn;
        wxBitmapButton* hautSimulationBtn;
        wxBitmapButton* gaucheSimulationBtn;
        wxPanel* Panel1;
        wxBitmapButton* refreshFenetresBtn;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticBox* StaticBox8;
        wxStaticBox* StaticBox7;
        wxButton* DeleteBtn;
        wxTextCtrl* txtY;
        wxStatusBar* StatusBar1;
        wxChoice* attaquePrincipale;
        wxChoice* attaqueCaC;
        wxSpinCtrl* boost2PA;
        wxStaticBox* StaticBox11;
        wxTextCtrl* gamePathTxt;
        wxButton* keyPressSimulationBtn;
        wxChoice* keyPressChoiceBox;
        wxCheckBox* activerLogIACheck;
        wxButton* LancerBtn;
        wxTextCtrl* txtIALog;
        wxCheckBox* CheckBox1;
        wxButton* selectBanqueTrajetBtn;
        wxBitmapButton* droiteSimulationBtn;
        wxChoice* boost1;
        wxButton* showHideFenetreBtn;
        wxSpinCtrl* boost1PA;
        wxChoice* boost2;
        wxStaticBox* StaticBox12;
        wxButton* resizeBtn;
        wxSpinCtrl* attaqueLigneDroitePA;
        wxStaticText* StaticText1;
        wxStaticBox* StaticBox9;
        wxStaticText* StaticText10;
        wxStaticBox* StaticBox20;
        wxStaticBox* StaticBox18;
        wxStaticText* StaticText16;
        wxBitmapButton* gaucheBtn;
        wxCheckBox* keepMouseCheck;
        wxChoice* keyPressSimulationChoiceBox;
        wxPanel* Panel2;
        wxCheckBox* repriseAutoCheck;
        wxStaticBox* StaticBox2;
        wxStaticBox* StaticBox16;
        wxBitmapButton* basBtn;
        wxChoice* attaqueLigneDroite;
        wxStaticText* StaticText3;
        wxButton* LancerJeuBtn;
        wxColourPickerCtrl* ressourceColor4;
        wxTextCtrl* txtConsole;
        wxPanel* Panel4;
        wxComboBox* selectedTrajetBanque;
        wxCheckBox* repeterTrajetCheck;
        wxButton* CombatBtn;
        wxComboBox* selectedTrajet;
        wxMenuItem* MenuItem3;
        wxCheckBox* CheckBox4;
        wxPanel* Panel5;
        wxButton* MetierBtn;
        wxStaticText* StaticText8;
        wxCheckBox* CheckBox2;
        wxStaticText* StaticText12;
        wxTextCtrl* txtX;
        wxButton* SaveTrajetBtn;
        wxColourPickerCtrl* ressourceColor3;
        wxPanel* Panel3;
        wxStaticBox* StaticBox1;
        wxStaticText* StaticText7;
        wxButton* SleepBtn;
        wxSpinCtrl* attaquePrincipalePA;
        wxStaticBox* StaticBox3;
        wxStaticBox* StaticBox10;
        wxSpinCtrl* attaqueDiagonalePA;
        wxComboBox* defaultPersoCombo;
        wxButton* PosClickBtn;
        wxStaticBox* StaticBox14;
        wxStaticBox* StaticBox13;
        wxBitmapButton* basSimulationBtn;
        wxStaticText* StaticText4;
        wxBitmapButton* hautBtn;
        wxColourPickerCtrl* ressourceColor2;
        wxSpinCtrl* nombreDePA;
        wxButton* stopTrajetBtn;
        wxStaticText* StaticText5;
        wxButton* keyPressBtn;
        wxButton* StopBtn;
        wxStaticText* StaticText2;
        wxNotebook* Notebook1;
        wxButton* simulerCombatBtn;
        wxCheckBox* laisserSourieCheck;
        wxChoice* attaqueDiagonale;
        wxCheckBox* AutoAddSleepCheck;
        wxCheckBox* CheckBox3;
        wxStaticBox* StaticBox4;
        wxStaticText* StaticText6;
        wxStaticBox* StaticBox19;
        wxCheckBox* GetMousePosCheck;
        wxButton* EnregistrerOptionsCoMeBtn;
        wxStaticBox* StaticBox5;
        wxStaticBox* StaticBox21;
        wxStaticBox* StaticBox17;
        wxButton* clickSimulationBtn;
        wxColourPickerCtrl* ressourceColor1;
        wxButton* getPixelColorBtn;
        wxCheckBox* resizeFenetreCheck;
        wxStaticBox* StaticBox15;
        wxStaticText* StaticText9;
        wxButton* selectOptCoMeBtn;
        wxStaticBox* StaticBox6;
        wxBitmapButton* droiteBtn;
        wxStaticText* StaticText11;
        wxSpinCtrl* SleepSpinBox;
        wxComboBox* listeFenetre;
        wxChoice* RessourceChoice;
        wxButton* actualiserIALogBtn;
        wxListBox* listeTrajet;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SUFOBOTMAIN_H
