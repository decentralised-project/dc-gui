///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DESKTOPFORM_H__
#define __DESKTOPFORM_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DesktopForm
///////////////////////////////////////////////////////////////////////////////
class DesktopForm : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxRichTextCtrl* txtMain;
		wxListBox* m_listBox1;
		wxTextCtrl* txtInput;
	
	public:
		
		DesktopForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ChatTest"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 586,461 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~DesktopForm();
	
};

#endif //__DESKTOPFORM_H__
