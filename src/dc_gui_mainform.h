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
#include <iostream>

using namespace boost;
using namespace dcp2p;

class dc_gui_mainform : public MainDcForm
{

public:

	dc_gui_mainform(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Decentralised GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(586, 461), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~dc_gui_mainform();

	void Init();

private:
	p2p_manager* _manager;

	void OnNodeConnected(bool isIncoming, p2p_connection::pointer connection, boost::uuids::uuid remoteId);
	void OnLog(std::string msg);
	void OnDataReceived(p2p_connection::pointer connection, p2p_packet packet);
	void OnNodeDisconnected(boost::uuids::uuid remoteId);

	void writeToRichText(std::string txt);
};

#endif 
