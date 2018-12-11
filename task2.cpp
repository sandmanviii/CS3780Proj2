#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <cstdlib>
#include <ctime>
#include <openssl/rand.h>


using namespace std;

string hashFunction(unsigned char *);

int main() {
	
	//seed random
	srand(time(NULL));

	//line is for reading each line from file
	string line; 

	//fstream variables
	ofstream outfile1, outfile2, outfile3;
	

	//open files for writing
	
	outfile1.open("pwd1.txt");
	outfile2.open("pwd2.txt");
	outfile3.open("pwd3.txt");

	//get bound of password length and amount of usernames to generate from user
	int passwordLengthLB, passwordLengthUB, amountOfPasswords;
	while (true) {
		cout << "Enter password length lower bound followed by password length "
			"upper bound followed by amount of usernames to generate: \n";
		cin >> passwordLengthLB; cin >> passwordLengthUB; cin >> amountOfPasswords;

		if ((passwordLengthLB > 0) && (passwordLengthLB < 10))
			if ((passwordLengthUB > passwordLengthLB) && (passwordLengthUB < 100))
				if ((amountOfPasswords > 0) && (amountOfPasswords < 1000))
					break;
		
		cout << "Error with input \n";
	}	
	
	int i, j;
	for (i = 0; i != amountOfPasswords; i++) {
		
		//
		//generate random set of bytes for username and password
		//
		
		//seeding the random
        	const RAND_METHOD* rm = RAND_get_rand_method();
        	RAND_poll();

		//randomly determine password and username length
		int passwordSize = rand() % (passwordLengthUB - passwordLengthLB + 1) + passwordLengthLB; 
		int usernameSize = rand() % 8 + 1; 
		
		//to make process quicker, username is set to a max of 8 alphanumeric characters	
		unsigned char username[usernameSize], pwd[passwordSize];
		
		//randomly fill buffers
		int rc = RAND_bytes(pwd, sizeof(pwd));
		if (rc != 1)
			cout << "Error generating random values\n";

		rc = RAND_bytes(username, sizeof(username));
		if (rc != 1)
                        cout << "Error generating random values\n";

		//iterate through ascii values and set value to be in domain: [48,57]U[65,90]U[97,122] aka alphanumeric
		for (j = 0; j != usernameSize; j++) {
			

			//use modulo to get ascii value to be from [48,109]
			username[j] = (username[j] % 62) + 48;
			
			//avoid characters between alphanumeric characters
			if (username[j] > 57 && username[j] < 84)
				username[j] += 7;
			else if (username[j] > 83 && username[j] < 110)
				username[j] += 13;

			

			
		}
		
		//same goes for password but password can only be lowercase letters so ascii values from [97,122]
		for (j = 0; j != passwordSize; j++) {
			pwd[j] = (pwd[j] % 26) + 97;
			
		}
		
		//write to first password file (plaintext)
		for (j = 0; j != sizeof(username); j++)
		       outfile1 << username[j];
		outfile1 << " ";
		for (j = 0; j != sizeof(pwd); j++)
                       outfile1 << pwd[j];
		outfile1 << "\n";

		//write to second file (username + hashed pass)
		for (j = 0; j != sizeof(username); j++)
			outfile2 << username[j];
		outfile2 << " ";
		string hashedPass = hashFunction(pwd);
		for (j = 0; j != sizeof(hashedPass); j++)
			outfile2 << hashedPass[j];
		outfile2 << "\n";
	
		//randomly generate 1 byte of salt
		unsigned char salt[1];
		rc = RAND_bytes(salt, sizeof(salt));
		if (rc != 1)
			cout << "Error generating random values\n";

		//create new variable to hold pwd and salt appended to end
		//has 1 more byte than pwd for salt
		unsigned char pwdWithSalt[passwordSize + 1];
		for (j = 0; j != passwordSize; j++)
			pwdWithSalt[j] = pwd[j];
		//put salt on end
		pwdWithSalt[passwordSize] = salt[0];
		string hashedPassWithSalt = hashFunction(pwdWithSalt);
		
		//write to third file (username + salt + salty hash)	
		for (j = 0; j != sizeof(username); j++)
                       outfile3 << username[j];
		outfile3 << " ";
		outfile3 << salt[0] << " ";
		for (j = 0; j != sizeof(hashedPassWithSalt); j++)
			outfile3 << hashedPassWithSalt[j];
		outfile3 << "\n";		
	}

	

	//close file streams	
	outfile1.close();
	outfile2.close();
	outfile3.close();
	
	
	return 0;
}

string hashFunction(unsigned char * pwd) {
	
	//all for doing the MD5 hash. Found all this here: http://www.askyb.com/cpp/openssl-md5-hashing-example-in-cpp/
	//used for hash process
	unsigned char digest[16];	
	int i;

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, pwd, sizeof(pwd));
	MD5_Final(digest, &ctx);

	//final result is stored in this
	char hashedPass[33];
	for (i = 0; i < 16; i++)
		sprintf(&hashedPass[i*2], "%02x", (unsigned int)digest[i]);

	return hashedPass;

}
