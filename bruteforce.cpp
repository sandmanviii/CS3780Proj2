//Libraries
#include <iostream>
#include <string>
#include<fstream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>


using namespace std;
//Generates alphanumeric strings of specified length
string gen_random(int len) {
	static string charset= "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string result;
	result.resize(len);
	for (int i = 0; i < len; i++) {
		result[i] = charset[rand() % charset.length()];
	}
	return result;
}

string hash(string pwd) {
	char path[1024];
	char pass[100];
	char command[1000];
	FILE *pipe;
	int status;
	string hashed;
//	string hashed;
	strcpy(pass, pwd.c_str());
	sprintf(command, "echo -n '%s' | md5sum", pass);
	pipe = popen(command, "r");
	if(pipe == NULL) {
		perror("Failed to open pipe");
	}
	while(fgets(path, 1024, pipe) != NULL) {
		printf("%s", path);
		}
	string temphash(path);
	hashed = temphash;
	for (int j = 0; j < 1024; j++) {
		path[j] = 0;
		}
 
	pclose(pipe);
	return hashed;
	}
int main(int argc, char **argv) {
	int numAccounts;
	int passLength;
	int saltLength;
	string userName;
	string passWord;
//	string hashedPass;
	int userLength = 8;
	srand(time(NULL));
//	FILE *pipe;
	string salt;
	string salthash;
	string hashedPass;
	fstream myfile, hashfile, saltfile;
	myfile.open("usernames.txt");
	hashfile.open("hashedpass.txt");
	saltfile.open("saltpass.txt");
	string saltyPass;
	char pass[100];	
	//User enter numbers of accounts to be created
	cout << "Enter a number for how many accounts will be created: " << endl;
	cin >> numAccounts;
	//Variables for popen
	int status;
//	char path[1024];
	//Main loop

	for(int i = 0; i < numAccounts; i++) {
		//Random password length between 3 and 8
		passLength = rand()%5 + 3;
		userName = gen_random(userLength);
		passWord = gen_random(passLength);
		salt = gen_random(saltLength);
		hashedPass = hash(passWord);
		saltyPass = passWord + salt;
		salthash = hash(saltyPass);
/*		
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
		//Turns entire array back to zero for next password hashing
		for(int j = 0; j < 1024; j++) {
			path[j] = 0;
			}
		pclose(pipe);
*/		
		if(myfile.is_open()) {
			myfile << "Username: " << userName << " " << "Password: " << passWord << endl;
			} else {
				cout << "unable to open file" << endl;
				return 0;
			}
		if(hashfile.is_open()) {
			hashfile << "Username: " << userName << " " << "Hashed Password: " << hashedPass << endl;
		}
	
		if(saltfile.is_open()) {
			saltfile << "Username: " << userName << " " << "Salt: " << salt << " " << "SaltHash: " << salthash << endl;
	
		}
		}

		myfile.close();
		hashfile.close();
		saltfile.close();
	return 0;
}
			
