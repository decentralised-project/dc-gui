#include "dc_gui_logindialog.h"

dc_gui_logindialog::dc_gui_logindialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: LoginDialog(parent, id, title, pos, size, style)
{
	this->SetWindowStyle(wxCLOSE_BOX | wxCAPTION);
}

dc_gui_logindialog::~dc_gui_logindialog()
{
}

void dc_gui_logindialog::on_generate_click(wxCommandEvent& event)
{
	dccrypto::crypt_ec_helper ec;
	EC_KEY* key = ec.generate_key_pair();
	std::string pub_key = ec.get_public_key(key);
	ec.save_key_pair("user.pem", key);

	this->txtPublicKey->SetValue(pub_key);
}

void dc_gui_logindialog::on_login_click(wxCommandEvent& event)
{

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

	// TODO: save the keypair and username in a secure way.
}

