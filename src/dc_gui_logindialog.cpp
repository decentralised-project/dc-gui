#include "dc_gui_logindialog.h"

dc_gui_logindialog::dc_gui_logindialog(std::string dataDirPath, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: LoginDialog(parent, id, title, pos, size, style)
{
	this->SetWindowStyle(wxCLOSE_BOX | wxCAPTION);
	data_dir = dataDirPath;
	ec = dccrypto::crypt_ec_helper::Create();
}

void dc_gui_logindialog::on_generate_click(wxCommandEvent& event)
{
	EC_KEY* key = ec->generate_key_pair();
	std::string pub_key = ec->get_public_key(key);

	this->txtPublicKey->SetValue(pub_key);
}

void dc_gui_logindialog::on_login_click(wxCommandEvent& event)
{
	int selectedIndex = lstExistingUsers->GetSelection();
	if (selectedIndex > -1)
	{
		Login(std::string(lstExistingUsers->GetString(selectedIndex)));

		// clear the form and close
		txtUsername->SetValue("");
		txtPublicKey->SetValue("");
		shared_from_this()->Close();
	}
}

void dc_gui_logindialog::on_create_click(wxCommandEvent& event)
{
	wxString username = txtUsername->GetValue();
	if (username.IsEmpty())
	{
		wxMessageBox("You must choose a username.", "AFFF!", wxICON_ERROR);
		return;
	}

	wxString publicKey = txtPublicKey->GetValue();
	if (publicKey.IsEmpty())
	{
		wxMessageBox("You must generate an encryption key pair.", "AFFF!", wxICON_ERROR);
		return;
	}

	std::string filename = data_dir;
	filename.append("private_keys/");
	filename.append(username);
	filename.append(".pem");

	// save the keypair and username in a secure way.
	EC_KEY* key = ec->get_key_pair();
	ec->save_key_pair(filename, key);

	Login(std::string(username));

	// clear the form and close
	txtUsername->SetValue("");
	txtPublicKey->SetValue("");
	shared_from_this()->Close();
}

void dc_gui_logindialog::on_user_selected(wxCommandEvent& event)
{
	btnLogin->Enable(true);
}

void dc_gui_logindialog::LoadUsers()
{
	try
	{
		getFilenamesInDirectory(std::string(data_dir).append("private_keys"));
	}
	catch (std::exception ex)
	{
		Log(ex.what());
	}
}

void dc_gui_logindialog::getFilenamesInDirectory(std::string dir_path)
{
	if (exists(dir_path))    // does p actually exist?
	{
		if (is_directory(dir_path))      // is p a directory?
		{
			directory_iterator end_itr; // default construction yields past-the-end
			for (directory_iterator itr(dir_path);
				itr != end_itr;
				++itr)
			{
				if (itr->path().extension().string() == ".pem")
					this->lstExistingUsers->Append(itr->path().stem().string());
			}
		}

		else
			throw std::runtime_error("Error reading the private_key directory.\n");
	}
	else
		throw std::runtime_error("Error private_key directory doesn't exist.\n");
}
