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
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <wx/msgdlg.h>
#include "crypt_ec_helper.hpp"

using namespace boost;

class dc_gui_logindialog : public LoginDialog, public boost::enable_shared_from_this<dc_gui_logindialog>
{

public:
	typedef boost::shared_ptr<dc_gui_logindialog> pointer;

	static pointer Create(std::string dataDirPath, wxWindow* parent)
	{
		return pointer(new dc_gui_logindialog(dataDirPath, parent));
	}

	void on_generate_click(wxCommandEvent& event);
	void on_login_click(wxCommandEvent& event);
	void on_create_click(wxCommandEvent& event);

private:
	dc_gui_logindialog(std::string dataDirPath, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(333, 265), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	dccrypto::crypt_ec_helper::pointer ec;
	std::string data_dir;
};

#endif 
