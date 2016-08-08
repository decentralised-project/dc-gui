#ifndef __DC_GUI_APP_H_INCLUDED__
#define __DC_GUI_APP_H_INCLUDED__

#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
#include <wx/wx.h>

#include "dc_gui_mainform.h"

class dc_gui_app : public wxApp
{
public:
	virtual bool OnInit();
private:
	
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(dc_gui_app, wxApp)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(dc_gui_app)

#endif
