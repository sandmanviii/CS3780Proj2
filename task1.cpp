#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdlib>


using namespace std;

int main(int argc, char ** argv) {
			
	//Variables
	string username, pwd, line;
	ifstream if1;
	ofstream of1;

	//Get username
	cout << "Enter username: ";
	getline(cin, username);
	
	//Open first password file for reading
	if1.open("pwd1.txt");
		
	//search through file to find username given by user
	bool isFound = false;	
	while (getline(if1, line)) {
		size_t found = line.find(username);
		if (found != string::npos)  { //if username exists
			isFound = true;
			break;
		}
	}
	//close the file reading
	if1.close();
	
	if (isFound) { //username exists so logging in
		
		//get password from user
		cout << "Enter password: ";
		getline(cin, pwd);	
		
		if (pwd.compare(line.substr(line.find(" ") + 1)) == 0)
			cout << "Password correct!" << endl;
		else
			cout << "Password incorrect!" << endl;
	}
	else { //username doesn't exist, so creating new account	
		/*
		of1.open("pwd1.txt", ios::app);
		of1 << username << " " << pwd << "\n";	
		cout << "Account " << username << " was created." << endl;
		*/
		cout << "Username does not exist..." << endl;
	}
	
	//close writing to the file	
	//of1.close();
	
	
	
	
	return 0;
}
