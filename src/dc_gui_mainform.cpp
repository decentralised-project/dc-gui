#include "dc_gui_mainform.h"

dc_gui_mainform::dc_gui_mainform(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainDcForm(parent, id, title, pos, size, style)
{
	login_dialog = NULL;
	settings_dialog = NULL;
	incoming_port = 6453;
}

dc_gui_mainform::~dc_gui_mainform()
{
	if (login_dialog)
		login_dialog->Destroy();

	if (settings_dialog)
		settings_dialog->Destroy();

	incoming_port = 0;
}

void dc_gui_mainform::Init()
{
#if WIN32
	SetIcon(wxICON(IDI_ICON1));
#endif

	txtMain->BeginTextColour(wxColour(0, 90, 0, 0));
	txtMain->WriteText("Decentralised GUI v1.0.0\r\n");
	txtMain->EndTextColour();

	incoming_port = 6453;
	data_dir = "data/";

	if (boost::filesystem::exists("config.json"))
	{
		config = dc_config::Create("config.json");
		incoming_port = config->GetInteger("incoming_port");
		data_dir = config->GetString("data_dir");

		txtMain->WriteText("Loaded configuration.\r\n");
	}
	else
		txtMain->WriteText("Couldn't find config.json, using defaults.\r\n");

	login_dialog = dc_gui_logindialog::Create(data_dir, this);
	login_dialog->Login.connect(boost::bind(&dc_gui_mainform::OnLoginClicked, this, _1));
	login_dialog->Show();
}

void dc_gui_mainform::OnNodeConnected(bool isIncoming, p2p_connection::pointer connection, std::string remoteId)
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

void dc_gui_mainform::OnNodeDisconnected(std::string remoteId)
{
	std::stringstream ss;
	ss << "Disconnected: " << remoteId;

	writeToRichText(std::string(ss.str()));
}

void dc_gui_mainform::OnLoginClicked(std::string name)
{
	writeToRichText(std::string("Connecting as ").append(name));

	_manager = crypt_network_manager::Create(data_dir);
	_manager->Log.connect(boost::bind(&dc_gui_mainform::OnLog, this, _1));
	_manager->NodeConnected.connect(boost::bind(&dc_gui_mainform::OnNodeConnected, this, _1, _2, _3));
	_manager->DataReceived.connect(boost::bind(&dc_gui_mainform::OnDataReceived, this, _1, _2));
	_manager->NodeDisconnected.connect(boost::bind(&dc_gui_mainform::OnNodeDisconnected, this, _1));
	_manager->Run(incoming_port, name);
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

void dc_gui_mainform::on_login_selected(wxCommandEvent& event)
{
	if (login_dialog)
		login_dialog->Destroy();

	login_dialog = dc_gui_logindialog::Create(data_dir, this);
	login_dialog->Login.connect(boost::bind(&dc_gui_mainform::OnLoginClicked, this, _1));
	login_dialog->Show();
}

void dc_gui_mainform::on_settings_selected(wxCommandEvent& event)
{
	settings_dialog = dc_gui_settingsdialog::Create(config, this);
	settings_dialog->Show();
}

void dc_gui_mainform::on_form_close(wxCommandEvent& event)
{
	if (_manager)
		_manager->Shutdown();

	if (login_dialog)
		login_dialog->Destroy();

	if (settings_dialog)
		settings_dialog->Destroy();
}