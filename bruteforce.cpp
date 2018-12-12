#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <openssl/md5.h>
#include <openssl/rand.h>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
using namespace std;
string crackPassword(string pass);
long long int attempt;
clock_t start_t, end_t;
string  alphaNum = "abcdefghijklmnopqrstuvwxyz0123456789";
struct Node {
	string str;
	Node * left;
	Node * right;
};
Node * head = new Node;

string hashFunction(unsigned char *);
bool insertNode(Node *, string);
void inOrder(Node *);
bool findNode(Node *, string);
void deleteTree(Node *);

//Recursive function to generate strings until length is reached
void generate(unsigned int len, string s) {
	string result;
	
	unsigned char temp[len];
	for(int j = 0; j != sizeof(s); j++) {
		temp[j] = s[j];
	}
	result = hashFunction(temp);
	if(len == 0){
		if(findNode(head, result) == true) {
			cout << "The hash: " << result << " correlates to " << s << endl;
			return;
		}
	}
/*	if(len == 0) {
		for (int i = 0; i < sizeof(hashes); i++) {
			if(result == hashes[i]) {
			       cout << "Match! " << result << " correlates to " << s << endl;
			}
		}
		return;
	}
*/
	for(int i = 0; i < 37; i++) {
		string appended = s + alphaNum[i];
		generate(len-1, appended);
	}
}
//Function to keep growing until make size reached
void crack(int passWordLengthLB, int passWordLengthUB) {
	while(1) {
		static unsigned int stringLen = passWordLengthLB;
		generate(stringLen, "");
		stringLen++;
		if(stringLen == passWordLengthUB){
			return;
		}
	}
}
int main(){
	//Variables
    	string password;
//    	Node * head = new Node;
    	head -> left = NULL;
   	head -> right = NULL;
    	head -> str = "";
    	ifstream infile;
    	string line;
    	int passwordFile, passWordLengthLB, lineCount = 0, passWordLengthUB;
    	cout << "\nEnter password file for brute force (2 for hash, 3 for saltedhash): ";
    	cin >> passwordFile;
	
//    	cout << "\nEnter the password to crack : ";
  //  	cin >> password;
    	cout << "\nEnter lower bound of password length: ";
    	cin >> passWordLengthLB;
	
    	cout << "\nEnter upper bound of password length: ";
    	cin >> passWordLengthUB;   
    	
    	if(passwordFile == 2) {
	   	infile.open("pwd2.txt");
	} else if (passwordFile == 3) {
		infile.open("pwd3.txt");
	} else {
		cout <<"Error\n";
	}
	while (getline(infile, line))
		lineCount++;
	infile.close();

	if(passwordFile == 2) {
		infile.open("pwd2.txt");
	} else if(passwordFile == 3) {
		infile.open("pwd3.txt");
	} else {
		cout << "Error\n";
	}
	//Stores hashes from file in to array f
	string hashes[lineCount];
	int count = 0;
	while (getline(infile, line)) {
    	int pos;
    	for(int i = line.length() - 1; i >= 0; i--) 
		if(line[i] == ' ') {
	    		pos = i;
    	    		break;
		}
		hashes[count] = line.substr(pos + 1);
		count++;
	}
	//bubble sort to make BST balanced
	bool swap = false;
	do {
		for(int i = 0; i != sizeof(hashes)/sizeof(hashes[0]) - 1; i++) {
			swap = false;

			if(hashes[i] > hashes[i + 1]) {
				string tmp = hashes[i + 1];
				hashes[i + 1] = hashes[i];
				hashes[i] = tmp;
				swap = true;

			}
		}
	}
	while(swap);
	//Add middle element of array of hashes to first elemnet of BST
	if(!insertNode(head, hashes[sizeof(hashes)/sizeof(hashes[0])/2])){
		cout << "Error adding to tree" << endl;
	}
	//Add all elements except middle element to tree
	for(int i = 0; i != sizeof(hashes)/sizeof(hashes)/sizeof(hashes[0]); i++) {
		if(i != sizeof(hashes)/sizeof(hashes[0])/2) {
			if(!insertNode(head, hashes[i])) {
				cout << "error adding to tree" << endl;
			}
		}
	}
	//Sends bounds to function for testing
	crack(passWordLengthLB, passWordLengthUB);
  	
	infile.close();
	return 0;

}


string hashFunction(unsigned char * pwd) {
	unsigned char digest[16];
	int i;
	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, pwd, sizeof(pwd));
	MD5_Final(digest, &ctx);


	//final result stored in this
	char hashedPass[33];
	for(i = 0; i < 16; i++) {
		sprintf(&hashedPass[i*2], "%02x", (unsigned int)digest[i]);
	}
	return hashedPass;
}

bool insertNode(Node * head, string str) {
	bool success = false;
	//If tree is empty
	if((head->str =="") && (head->left == NULL) && (head->right == NULL)) {
		head->str = str;
		head->left = NULL;
		head->right = NULL;
		success = true;
		}
	//Going to the left
	else if(str < head->str) {
		if(head->left == NULL) {
			Node * n = new Node;
			n->left = NULL;
			n->right = NULL;
			n->str = str;
			head ->left = n;
			success = true;
			}
		//else recursively move through array
		else {
			insertNode(head->left, str);
			success = true;
			}
	}
	else if(str > head -> str) {
		if(head -> right == NULL) {
			Node * n = new Node;
			n -> left = NULL;
			n -> right = NULL;
			n -> str = str;
			head -> right = n;
			success = true;
		}
		else {
			insertNode (head->right, str);
			success = true;
		}
	}
	return success;
}

void inOrder(Node * head) {
	if(head != NULL) {
		inOrder(head->left);
		cout << head->str << endl;
		inOrder(head->right);
	}
}

bool findNode(Node * head, string str) {
	while (head != NULL) {
		if(str > head-> str) {
			head = head->right;
		}else if (str < head-> str) {
			head = head -> left;
		} else {
			return true;
		}
	}
}
void deleteTree(Node * head) {
	if(head == NULL)
		return;
	deleteTree(head->left);
	deleteTree(head->right);
	delete head;
}
