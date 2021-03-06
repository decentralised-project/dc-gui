#include "dc_gui_mainform.h"

dc_gui_mainform::dc_gui_mainform(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainDcForm(parent, id, title, pos, size, style)
{
	login_dialog = NULL;
	settings_dialog = NULL;
	incoming_port = 6453;
	logged_in_name = "";
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

	txtMain->BeginTextColour(wxColour(0, 90, 0, 255));
	txtMain->WriteText("Decentralised GUI v1.0.0");
	txtMain->EndTextColour();

	incoming_port = 6453;
	data_dir = "data/";

	if (boost::filesystem::exists("config.json"))
	{
		config = dc_config::Create("config.json");
		incoming_port = config->GetInteger("incoming_port");
		data_dir = config->GetString("data_dir");

		txtMain->Newline();
		txtMain->WriteText("Loaded configuration.");
	}
	else
	{
		txtMain->Newline();
		txtMain->WriteText("Couldn't find config.json, using defaults.");
	}

	login_dialog = dc_gui_logindialog::Create(data_dir, this);
	login_dialog->Login.connect(boost::bind(&dc_gui_mainform::OnLoginClicked, this, _1));
	login_dialog->Log.connect(boost::bind(&dc_gui_mainform::OnLog, this, _1));
	login_dialog->LoadUsers();
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
	ss << connection->Socket().remote_endpoint() << " " << remoteId;

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

//	writeToRichText(txt);

	unsigned char* cmd;
	unsigned int cmdLength = 0;

	size_t offset = 0;
 	memcpy(&cmdLength, packet.body(), sizeof(unsigned int));
	offset += sizeof(unsigned int);

	cmd = new unsigned char[cmdLength];

	memcpy(cmd, packet.body() + offset, cmdLength);
	offset += cmdLength;

	if (std::string(cmd, cmd + cmdLength) == "MSG")
	{
		unsigned char* channel;
		unsigned int channelLength = 0;

		unsigned char* name;
		unsigned int nameLength = 0;

		unsigned char* msg;
		unsigned int msgLength = 0;

		memcpy(&channelLength, packet.body() + offset, sizeof(unsigned int));
		offset += sizeof(unsigned int);

		channel = new unsigned char[channelLength];

		memcpy(channel, packet.body() + offset, channelLength);
		offset += channelLength;

		memcpy(&nameLength, packet.body() + offset, sizeof(unsigned int));
		offset += sizeof(unsigned int);

		name = new unsigned char[nameLength];

		memcpy(name, packet.body() + offset, nameLength);
		offset += nameLength;

		memcpy(&msgLength, packet.body() + offset, sizeof(unsigned int));
		offset += sizeof(unsigned int);

		msg = new unsigned char[msgLength];

		memcpy(msg, packet.body() + offset, msgLength);
		offset += msgLength;

		writeToPanel(std::string(channel, channel + channelLength), std::string(name, name + nameLength).append(": ").append(std::string(msg, msg + msgLength)), wxColour(0, 0, 0));

		free(msg);
		free(name);
		free(channel);
	}

	free(cmd);
}

void dc_gui_mainform::OnNodeDisconnected(std::string remoteId, std::string error)
{
	std::stringstream ss;
	ss << "Disconnected: " << remoteId << " - " << error;

	// TODO: if(connections.size() == 0)
	writeToPanel("", "Disconnected", wxColour(0,0,127));

	writeToRichText(std::string(ss.str()));
}

void dc_gui_mainform::OnLoginClicked(std::string name)
{
	logged_in_name = name;
	writeToRichText(std::string("Connecting as ").append(logged_in_name));

	_manager = crypt_network_manager::Create(data_dir);
	_manager->Log.connect(boost::bind(&dc_gui_mainform::OnLog, this, _1));
	_manager->NodeConnected.connect(boost::bind(&dc_gui_mainform::OnNodeConnected, this, _1, _2, _3));
	_manager->DataReceived.connect(boost::bind(&dc_gui_mainform::OnDataReceived, this, _1, _2));
	_manager->NodeDisconnected.connect(boost::bind(&dc_gui_mainform::OnNodeDisconnected, this, _1, _2));
	_manager->Run(incoming_port, name);
}

void dc_gui_mainform::writeToRichText(std::string txt)
{
	if (!wxIsMainThread())
		wxMutexGuiEnter();

	txtMain->Freeze();

	txtMain->SetCaretPosition(txtMain->GetLastPosition() - 1);
	size_t before_number_of_lines = txtMain->GetNumberOfLines();

	txtMain->Newline();
	txtMain->WriteText(txt);

	size_t after_number_of_lines = txtMain->GetNumberOfLines();
	txtMain->Thaw();

	txtMain->ScrollLines(txtMain->GetNumberOfLines());

	if (!wxIsMainThread())
		wxMutexGuiLeave();
}

void dc_gui_mainform::writeToPanel(std::string panelTitle, std::string txt, wxColour col)
{
	size_t numPages = tabsMain->GetPageCount();
	for (int i = 0; i < numPages; ++i)
	{
		wxString pageTitle = tabsMain->GetPageText(i);
		if (pageTitle != "Terminal" && (pageTitle == panelTitle || panelTitle == ""))
		{
			dc_gui_chatpanel* page = (dc_gui_chatpanel*)tabsMain->GetPage(i);
			page->WriteToRichText(txt, col);
		}
	}
}

void dc_gui_mainform::on_login_selected(wxCommandEvent& event)
{
	if (login_dialog)
		login_dialog->Destroy();

	login_dialog = dc_gui_logindialog::Create(data_dir, this);
	login_dialog->Login.connect(boost::bind(&dc_gui_mainform::OnLoginClicked, this, _1));
	login_dialog->Log.connect(boost::bind(&dc_gui_mainform::OnLog, this, _1));
	login_dialog->LoadUsers();
	login_dialog->Show();
}

void dc_gui_mainform::on_settings_selected(wxCommandEvent& event)
{
	settings_dialog = dc_gui_settingsdialog::Create(config, this);
	settings_dialog->Show();
}

void dc_gui_mainform::on_input_enter_pressed(wxCommandEvent& event)
{
	// get the currently selected tab.
	int selectedIndex = tabsMain->GetSelection();
	wxString selectedPanelTitle = tabsMain->GetPageText(selectedIndex);

	// get the input text.
	wxString input = txtInput->GetValue();

	// if this is a command (starting with forward slash)
	if (input.StartsWith("/") && input.Length() > 4)
	{
		wxString cmd = input.Lower().SubString(1, 4);
		if (cmd == "join") // join a channel
		{
			wxString name = input.SubString(6, input.Length());
			writeToRichText(std::string("Joining channel ").append(name));
			dc_gui_chatpanel* panel = new dc_gui_chatpanel(tabsMain, name);
			tabsMain->AddPage(panel, name, false);
			tabsMain->SetSelection(tabsMain->GetPageCount() - 1);
			txtInput->SetFocus();
		}
		else if (cmd == "help") // get some help
		{
			writeToRichText(std::string("/help\t\tShows this help text.\r\n")
				.append("/join #public\tJoins a chat channel."));
		}
	}
	else if (selectedPanelTitle != "Terminal") // can't send messages to the terminal tab
	{
		// SIZE - CMD - SIZE - CHANNEL - SIZE - USERNAME - SIZE - INPUT

		std::string cmd = "MSG";
		unsigned char* packet = new unsigned char[sizeof(size_t) + cmd.size() + sizeof(size_t) + selectedPanelTitle.size() + sizeof(size_t) + logged_in_name.size() + sizeof(size_t) + input.size()];
		size_t offset = 0;

		size_t cmdSize = cmd.size();
		memcpy(packet, &cmdSize, sizeof(size_t));
		offset += sizeof(size_t);

		memcpy(packet + offset, cmd.c_str(), cmdSize);
		offset += cmdSize;

		size_t channelSize = selectedPanelTitle.size();
		memcpy(packet + offset, &channelSize, sizeof(size_t));
		offset += sizeof(size_t);

		memcpy(packet + offset, selectedPanelTitle.c_str(), channelSize);
		offset += channelSize;

		size_t nameSize = logged_in_name.size();
		memcpy(packet + offset, &nameSize, sizeof(size_t));
		offset += sizeof(size_t);

		memcpy(packet + offset, logged_in_name.c_str(), nameSize);
		offset += nameSize;

		size_t inputSize = input.Length();
		memcpy(packet + offset, &inputSize, sizeof(size_t));
		offset += sizeof(size_t);

		memcpy(packet + offset, input.data().AsChar(), inputSize);
		offset += inputSize;

		_manager->Send(packet, offset);
		free(packet);
	}

	// clear the input textbox.
	txtInput->SetValue("");
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

void dc_gui_mainform::on_tab_changed(wxNotebookEvent& event)
{
	txtInput->SetFocus();
}

void dc_gui_mainform::on_richtext_focus(wxFocusEvent& event)
{
	txtInput->SetFocus();
}
