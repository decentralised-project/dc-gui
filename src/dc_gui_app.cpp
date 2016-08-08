#include "dc_gui_app.h"

bool dc_gui_app::OnInit()
{
	dc_gui_mainform *frame = new dc_gui_mainform(NULL);
	frame->Show(true);
	frame->Init();
	return true;
}
