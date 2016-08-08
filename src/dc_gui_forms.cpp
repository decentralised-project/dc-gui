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
	
	tabsLogin = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnlExisting = new wxPanel( tabsLogin, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( pnlExisting, wxID_ANY, wxT("Select an existing user from the list"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 1, wxALL, 10 );
	
	m_listBox2 = new wxListBox( pnlExisting, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer5->Add( m_listBox2, 8, wxALL|wxEXPAND, 10 );
	
	m_button3 = new wxButton( pnlExisting, wxID_ANY, wxT("Login"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button3->Enable( false );
	
	bSizer5->Add( m_button3, 1, wxALIGN_RIGHT|wxALL, 10 );
	
	
	pnlExisting->SetSizer( bSizer5 );
	pnlExisting->Layout();
	bSizer5->Fit( pnlExisting );
	tabsLogin->AddPage( pnlExisting, wxT("Existing User"), true );
	pnlCreate = new wxPanel( tabsLogin, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	tabsLogin->AddPage( pnlCreate, wxT("Create User"), false );
	
	bSizer3->Add( tabsLogin, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

LoginDialog::~LoginDialog()
{
}
