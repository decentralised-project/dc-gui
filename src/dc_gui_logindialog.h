#ifndef __DC_GUI_LOGINDIALOG_H__
#define __DC_GUI_LOGINDIALOG_H__

#include "dc_gui_forms.h"
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <sstream>
#include <boost/bind.hpp>
#include <iostream>
#include <wx/msgdlg.h>
#include "crypt_ec_helper.hpp"

using namespace boost;

class dc_gui_logindialog : public LoginDialog
{

public:

	dc_gui_logindialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(333, 265), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~dc_gui_logindialog();

	void on_generate_click(wxCommandEvent& event);
	void on_login_click(wxCommandEvent& event);
	void on_create_click(wxCommandEvent& event);

private:
};

#endif 
