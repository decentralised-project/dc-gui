#include "dc_gui_logindialog.h"

dc_gui_logindialog::dc_gui_logindialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: LoginDialog(parent, id, title, pos, size, style)
{
	this->SetWindowStyle(wxCLOSE_BOX | wxCAPTION);
}

dc_gui_logindialog::~dc_gui_logindialog()
{
}

