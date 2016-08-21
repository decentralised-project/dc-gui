#include "dc_gui_settingsdialog.h"

dc_gui_settingsdialog::dc_gui_settingsdialog(dc_config::pointer c, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: SettingsDialog(parent, id, title, pos, size, style)
{
	this->SetWindowStyle(wxCLOSE_BOX | wxCAPTION);

	config = c;

	int p = c->GetInteger("incoming_port");

	std::stringstream incoming_port_str;
	incoming_port_str << p;
	std::string incoming_port(incoming_port_str.str());

	txtIncomingPort->SetValue(incoming_port);

	dirData->SetPath(c->GetString("data_dir"));
}

void dc_gui_settingsdialog::on_save_clicked(wxCommandEvent& event)
{
	// get the value as a string
	std::string incoming_port_str = txtIncomingPort->GetValue();

	// check to see if the string is an integer
	if (!std::regex_match(incoming_port_str, std::regex("[(-|+)|][0-9]+")))
	{
		wxMessageBox("Incoming Port must be a number between 0 and 65535.", "AFFF!", wxICON_ERROR);
		return;
	}

	// cast the port string to an integer
	int incoming_port = boost::lexical_cast<int>(incoming_port_str);

	// is the port in range?
	if (incoming_port < 1 || incoming_port > 65534)
	{
		wxMessageBox("Incoming Port must be a number between 0 and 65535.", "AFFF!", wxICON_ERROR);
		return;
	}

	config->SetInteger("incoming_port", incoming_port);
	config->SetString("data_dir", std::string(dirData->GetPath().c_str()));
	config->Save("config.json");

	this->Close(true);
}