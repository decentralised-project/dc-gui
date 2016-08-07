#include "DesktopApp.h"

bool DesktopApp::OnInit()
{
	DesktopFormOveridden *frame = new DesktopFormOveridden(NULL);
	frame->Show(true);
	frame->Init();
	return true;
}
