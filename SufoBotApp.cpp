/***************************************************************
 * Name:      SufoBotApp.cpp
 * Purpose:   Code for Application Class
 * Author:    AXeL (axel.prog.25@gmail.com)
 * Created:   2015-07-20
 * Copyright: AXeL ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SufoBotApp.h"

//(*AppHeaders
#include "SufoBotMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SufoBotApp);

bool SufoBotApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SufoBotFrame* Frame = new SufoBotFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
