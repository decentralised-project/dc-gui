///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dc_gui_forms.h"

///////////////////////////////////////////////////////////////////////////

MainDcForm::MainDcForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* menuSettings;
	menuSettings = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuSettings );
	
	m_menu1->AppendSeparator();
	
	wxMenuItem* menuExit;
	menuExit = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuExit );
	
	m_menubar1->Append( m_menu1, wxT("File") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	txtMain = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer2->Add( txtMain, 1, wxEXPAND | wxALL, 1 );
	
	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxNO_BORDER ); 
	bSizer2->Add( m_listBox1, 0, wxALL|wxEXPAND, 1 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	txtInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( txtInput, 0, wxALL|wxEXPAND, 0 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

MainDcForm::~MainDcForm()
{
}

LoginDialog::LoginDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_button2 = new wxButton( this, wxID_ANY, wxT("Login with Existing User"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button2, 5, wxALIGN_CENTER|wxALL, 5 );
	
	m_button3 = new wxButton( this, wxID_ANY, wxT("Create a New User"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button3, 5, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer3->Add( bSizer9, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

LoginDialog::~LoginDialog()
{
}
