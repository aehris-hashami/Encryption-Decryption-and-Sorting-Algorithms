#include <iostream>
#include <cstring>
using namespace std;

extern "C" void __fastcall SignUp_UI(char*);
extern "C" void __fastcall Login_UI();

// Cipher prototypes


int main(int argc, char** argv) {
	char* pass_str = new char[100];

	// Run Sign Up UI
	SignUp_UI(pass_str);

	string usr_password = pass_str;
	cout << usr_password << endl;

	// read configuration file


	// encrypt user password with cipher according to configuration file


	// write encrypted password to file

	
	// read encrypted password from file


	// decrypt read ciphertext


	// Run Login UI, passing decrypted plaintext as argument

	return 0;
} 


// Cipher definitions