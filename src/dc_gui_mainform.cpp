#include "dc_gui_mainform.h"

dc_gui_mainform::dc_gui_mainform(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainDcForm(parent, id, title, pos, size, style)
{
}

dc_gui_mainform::~dc_gui_mainform()
{
}

void dc_gui_mainform::Init()
{
#if WIN32
	SetIcon(wxICON(IDI_ICON1));
#endif

	txtMain->BeginTextColour(wxColour(0, 90, 0, 0));
	txtMain->WriteText("Decentralised GUI v1.0.0\r\n");
	txtMain->EndTextColour();

	if (boost::filesystem::exists("config.json"))
	{
		config = new dc_config("config.json");
		txtMain->WriteText("Loaded configuration.\r\n");
	}
	else
		txtMain->WriteText("Couldn't find config.json, using defaults.\r\n");

	login_dialog = new dc_gui_logindialog(this);
	login_dialog->Show();

	int incoming_port = config->GetInteger("incoming_port");

	_manager = new p2p_manager();
	_manager->Log.connect(boost::bind(&dc_gui_mainform::OnLog, this, _1));
	_manager->NodeConnected.connect(boost::bind(&dc_gui_mainform::OnNodeConnected, this, _1, _2, _3));
	_manager->DataReceived.connect(boost::bind(&dc_gui_mainform::OnDataReceived, this, _1, _2));
	_manager->NodeDisconnected.connect(boost::bind(&dc_gui_mainform::OnNodeDisconnected, this, _1));
	_manager->Run(incoming_port);
}

void dc_gui_mainform::OnNodeConnected(bool isIncoming, p2p_connection::pointer connection, boost::uuids::uuid remoteId)
{
	std::string txt;
	if (isIncoming) {
		txt = "Incoming connection received from ";
	}
	else
	{
		txt = "Outgoing connection established to ";
	}

	std::stringstream ss;
	ss << connection->Socket().remote_endpoint();

	txt.append(ss.str());

	writeToRichText(txt);
}

void dc_gui_mainform::OnLog(std::string msg)
{
	std::string txt = msg;
	writeToRichText(txt);
}

void dc_gui_mainform::OnDataReceived(p2p_connection::pointer connection, p2p_packet packet)
{
	std::stringstream ss;
	ss << "Received from " << connection->Socket().remote_endpoint();
	std::string txt(ss.str());

	txt.append(" packet: ");

	std::string body(packet.body(), packet.body() + packet.body_length());
	txt.append(body);

	writeToRichText(txt);
}

void dc_gui_mainform::OnNodeDisconnected(boost::uuids::uuid remoteId)
{
	std::stringstream ss;
	ss << "Disconnected: " << remoteId;

	writeToRichText(std::string(ss.str()));
}

void dc_gui_mainform::writeToRichText(std::string txt)
{
	if (!wxIsMainThread())
		wxMutexGuiEnter();

	txtMain->Freeze();

	txtMain->SetCaretPosition(txtMain->GetLastPosition() - 1);
	size_t before_number_of_lines = txtMain->GetNumberOfLines();

	txtMain->WriteText(txt);
	txtMain->Newline();

	size_t after_number_of_lines = txtMain->GetNumberOfLines();
	txtMain->Thaw();

	txtMain->ScrollLines(txtMain->GetNumberOfLines());

	if (!wxIsMainThread())
		wxMutexGuiLeave();
}

void dc_gui_mainform::on_settings_selected(wxCommandEvent& event)
{
	settings_dialog = new dc_gui_settingsdialog(config, this);
	settings_dialog->Show();
}

void dc_gui_mainform::on_form_close(wxCommandEvent& event)
{
	if (_manager)
		delete _manager;

	if (login_dialog)
		delete login_dialog;

	if (config)
		delete config;
}