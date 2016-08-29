#ifndef __DC_GUI_CHATPANEL_H__
#define __DC_GUI_CHATPANEL_H__

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
#include <wx/panel.h>

class dc_gui_chatpanel : public wxPanel
{
public:
	dc_gui_chatpanel(wxWindow *parent,
					 wxString tabTitle,
 					 wxWindowID winid = wxID_ANY,
					 const wxPoint& pos = wxDefaultPosition,
					 const wxSize& size = wxDefaultSize,
					 long style = wxTAB_TRAVERSAL | wxNO_BORDER,
					 const wxString& name = wxPanelNameStr);
	~dc_gui_chatpanel();

private:
	wxRichTextCtrl* txtMain;
	wxListBox* m_listBox1;
};

#endif