#include <iostream>
#include <string>
#include<fstream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>


using namespace std;
string gen_random(int len) {
	static string charset= "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string result;
	result.resize(len);
	for (int i = 0; i < len; i++) {
		result[i] = charset[rand() % charset.length()];
	}
	return result;
}
int main(int argc, char **argv) {
	int numAccounts;
	int passLength;
	string userName;
	string passWord;
//	string hashedPass;
	int userLength = 8;
	srand(time(NULL));
	FILE *pipe;
	string salt;
	fstream myfile, hashfile;
	myfile.open("usernames.txt");
	hashfile.open("hashedpass.txt");
	char command[1000];
	char pass[100];	
	
	cout << "Enter a number for how many accounts will be created: " << endl;
	cin >> numAccounts;

	cout << "Enter a number for password length between 3 and 8: " << endl;
	cin >> passLength;
	int status;
	char path[1024];
	for(int i = 0; i < numAccounts; i++) {
		passLength = rand()%5 + 3;
		userName = gen_random(userLength);
		passWord = gen_random(passLength);
	//	salt = gen_random(1);
		
		strcpy(pass, passWord.c_str());
		sprintf(command, "echo -n '%s' | md5sum", pass);
		pipe = popen(command, "r");
		if(pipe == NULL) {
			perror("Failed to open pipe");
		}
		while(fgets(path, 1024, pipe) != NULL){
			printf("%s", path);
			}
	//	status = pclose(pipe);
		string hashedPass(path);
		for(int j = 0; j < 1024; j++) {
			path[j] = 0;
			}
		pclose(pipe);
		
		if(myfile.is_open()) {
			myfile << "Username: " << userName << " " << "Password: " << passWord << endl;
			} else {
				cout << "unable to open file" << endl;
				return 0;
			}
		if(hashfile.is_open()) {
			hashfile << "Username: " << userName << " " << "Hashed Password: " << hashedPass << endl;
		}
	}
		myfile.close();
		hashfile.close();
	return 0;
}
			
