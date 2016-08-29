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
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>

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
		wxNotebook* m_notebook3;
		wxPanel* m_panel4;
		wxRichTextCtrl* txtMain;
		wxListBox* m_listBox1;
		wxTextCtrl* txtInput;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_form_close( wxCloseEvent& event ) { event.Skip(); }
		virtual void on_login_selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_settings_selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_input_enter_pressed( wxCommandEvent& event ) { event.Skip(); }
		
	
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
		wxNotebook* tabsLogin;
		wxPanel* pnlExisting;
		wxStaticText* m_staticText2;
		wxListBox* lstExistingUsers;
		wxButton* btnLogin;
		wxPanel* pnlCreate;
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText3;
		wxTextCtrl* txtUsername;
		wxStaticText* m_staticText5;
		wxButton* m_button2;
		wxTextCtrl* txtPublicKey;
		wxButton* m_button31;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_user_selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_login_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_generate_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void on_create_click( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		LoginDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 361,265 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU ); 
		~LoginDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SettingsDialog
///////////////////////////////////////////////////////////////////////////////
class SettingsDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook2;
		wxPanel* m_panel3;
		wxStaticText* m_staticText5;
		wxTextCtrl* txtIncomingPort;
		wxStaticText* m_staticText9;
		wxDirPickerCtrl* dirData;
		wxButton* m_button4;
		
		// Virtual event handlers, overide them in your derived class
		virtual void on_save_clicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SettingsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 317,228 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~SettingsDialog();
	
};

#endif //__DC_GUI_FORMS_H__
