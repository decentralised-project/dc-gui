///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DC_GUI_FORMS_H__
#define __DC_GUI_FORMS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainDcForm
///////////////////////////////////////////////////////////////////////////////
class MainDcForm : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxRichTextCtrl* txtMain;
		wxListBox* m_listBox1;
		wxTextCtrl* txtInput;
	
	public:
		
		MainDcForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Decentralised GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 586,461 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainDcForm();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class LoginDialog
///////////////////////////////////////////////////////////////////////////////
class LoginDialog : public wxDialog 
{
	private:
	
	protected:
		wxButton* m_button2;
		wxButton* m_button3;
	
	public:
		
		LoginDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 333,265 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~LoginDialog();
	
};

#endif //__DC_GUI_FORMS_H__
