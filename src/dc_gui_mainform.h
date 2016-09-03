#ifndef __DESKTOPFORM_OVERIDDEN_H__
#define __DESKTOPFORM_OVERIDDEN_H__

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
#include "p2p_manager.hpp"
#include "p2p_host.hpp"
#include "p2p_listener.hpp"
#include "p2p_connection.hpp"
#include "p2p_packet.hpp"
#include <sstream>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include "dc_gui_logindialog.h"
#include "dc_gui_settingsdialog.h"
#include "dc_gui_chatpanel.h"
#include "dc_config.h"
#include "crypt_network_manager.hpp"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#if WIN32
#include "Win32/resource.h"
#endif

using namespace boost;
using namespace dcp2p;
using namespace dccrypto;

class dc_gui_mainform : public MainDcForm
{
public:

	dc_gui_mainform(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Decentralised GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(586, 461), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~dc_gui_mainform();

	void Init();

private:
	crypt_network_manager::pointer _manager;
	dc_gui_logindialog::pointer login_dialog;
	dc_gui_settingsdialog::pointer settings_dialog;
	dc_config::pointer config;
	std::string data_dir;
	int incoming_port;

	void OnNodeConnected(bool isIncoming, p2p_connection::pointer connection, std::string remoteId);
	void OnLog(std::string msg);
	void OnDataReceived(p2p_connection::pointer connection, p2p_packet packet);
	void OnNodeDisconnected(std::string remoteId);
	void OnLoginClicked(std::string name);

	void on_login_selected(wxCommandEvent& event);
	void on_settings_selected(wxCommandEvent& event);
	void on_form_close(wxCommandEvent& event);
	void on_input_enter_pressed(wxCommandEvent& event);
	void on_tab_changed(wxNotebookEvent& event);
	void on_richtext_focus(wxFocusEvent& event);

	void writeToRichText(std::string txt);
	void writeToPanel(std::string panelTitle, std::string txt, wxColour col);
};

#endif 
