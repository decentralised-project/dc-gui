#ifndef __DESKTOP_APP_H_INCLUDED__
#define __DESKTOP_APP_H_INCLUDED__

#include <boost/asio.hpp>
#include <wx/wx.h>

#include "DesktopFormOverriden.h"

class DesktopApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(DesktopApp, wxApp)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(DesktopApp)

#endif
