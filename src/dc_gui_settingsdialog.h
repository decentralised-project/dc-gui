#ifndef __DC_GUI_SETTINGSDIALOG_H__
#define __DC_GUI_SETTINGSDIALOG_H__

#include <regex>
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
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <wx/msgdlg.h>
#include "crypt_ec_helper.hpp"
#include "dc_config.h"

using namespace boost;

class dc_gui_settingsdialog : public SettingsDialog
{

public:

	dc_gui_settingsdialog(dc_config* c, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(333, 265), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~dc_gui_settingsdialog();

private:

	dc_config* config;

	void on_save_clicked(wxCommandEvent& event);
};

#endif 
