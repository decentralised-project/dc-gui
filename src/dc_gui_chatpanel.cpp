#include "dc_gui_chatpanel.h"

dc_gui_chatpanel::dc_gui_chatpanel(wxWindow *parent,
	wxString tabTitle,
	wxWindowID winid,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxPanel(parent, winid, pos, size, style, name)
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	txtMain = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL | wxTE_READONLY | wxNO_BORDER | wxVSCROLL | wxWANTS_CHARS);
	bSizer2->Add(txtMain, 1, wxEXPAND | wxALL, 1);

	txtMain->BeginTextColour(wxColour(0, 90, 0, 0));
	txtMain->WriteText(std::string("Joined channel ").append(tabTitle));
	txtMain->EndTextColour();

	m_listBox1 = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 | wxNO_BORDER);
	bSizer2->Add(m_listBox1, 0, wxALL | wxEXPAND, 1);

	this->SetSizer(bSizer2);
	this->Layout();
	bSizer2->Fit(this);
}

dc_gui_chatpanel::~dc_gui_chatpanel()
{
	txtMain->Destroy();
	m_listBox1->Destroy();
}