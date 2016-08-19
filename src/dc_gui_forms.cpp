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
	
	bSizer5->Add( m_button3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 10 );
	
	
	pnlExisting->SetSizer( bSizer5 );
	pnlExisting->Layout();
	bSizer5->Fit( pnlExisting );
	tabsLogin->AddPage( pnlExisting, wxT("Existing User"), true );
	pnlCreate = new wxPanel( tabsLogin, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( pnlCreate, wxID_ANY, wxT("Enter a username and generate a key pair"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer51->Add( m_staticText4, 0, wxALL, 10 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( pnlCreate, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	txtUsername = new wxTextCtrl( pnlCreate, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( txtUsername, 9, wxALL|wxEXPAND, 5 );
	
	
	bSizer51->Add( fgSizer1, 1, wxEXPAND, 10 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( pnlCreate, wxID_ANY, wxT("Public Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer9->Add( m_staticText5, 9, wxALIGN_BOTTOM|wxALL, 5 );
	
	m_button2 = new wxButton( pnlCreate, wxID_ANY, wxT("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button2, 1, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 2 );
	
	
	bSizer7->Add( bSizer9, 1, 0, 5 );
	
	txtPublicKey = new wxTextCtrl( pnlCreate, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtPublicKey->Enable( false );
	
	bSizer7->Add( txtPublicKey, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer51->Add( bSizer7, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_button31 = new wxButton( pnlCreate, wxID_ANY, wxT("Save and Login"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_button31, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer51->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	pnlCreate->SetSizer( bSizer51 );
	pnlCreate->Layout();
	bSizer51->Fit( pnlCreate );
	tabsLogin->AddPage( pnlCreate, wxT("Create User"), false );
	
	bSizer3->Add( tabsLogin, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_login_click ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_generate_click ), NULL, this );
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_create_click ), NULL, this );
}

LoginDialog::~LoginDialog()
{
	// Disconnect Events
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_login_click ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_generate_click ), NULL, this );
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginDialog::on_create_click ), NULL, this );
	
}

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText5 = new wxStaticText( m_panel3, wxID_ANY, wxT("Incoming Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer11->Add( m_staticText5, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_textCtrl4 = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_textCtrl4, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	m_panel3->SetSizer( bSizer10 );
	m_panel3->Layout();
	bSizer10->Fit( m_panel3 );
	m_notebook2->AddPage( m_panel3, wxT("Connection"), false );
	
	bSizer9->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button4, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

SettingsDialog::~SettingsDialog()
{
}
