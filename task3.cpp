#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <cstdlib>
#include <ctime>
#include <openssl/rand.h>
#include <cmath>
#include <unistd.h>

using namespace std;

struct Node {
	
        string str;
        Node * left; Node * right;

};


string hashFunction(unsigned char *);

bool insertNode(Node *, string);
void inOrder(Node *);
bool findNode(Node *, string);
void deleteTree(Node *);

int main() {
	
	//initialize head node
	Node * head = new Node;
	head->left = NULL;
	head->right = NULL;
	head->str = "";

	//user input variables
        int passwordFile, passwordLengthLB, passwordLengthUB;
        cout << "Enter password file (2 or 3): ";
        cin >> passwordFile;
        
	cout << "\nEnter lower bound of password length: ";
	cin >> passwordLengthLB;

	cout << "\nEnter upper bound of password length: ";
	cin >> passwordLengthUB;
	
	//couldn't figure out how to find line count and read from the stream without 
	//closing and reopening the stream. I am sure there is a better way to do this	
	ifstream infile;

	string line;

	//choosing what password file to try and break
  	if (passwordFile == 2)
		infile.open("pwd2.txt");
	else if (passwordFile == 3)
		infile.open("pwd3.txt");
	else
		cout << "Error\n";
	
	//get line count
	int lineCount = 0;	
	while (getline(infile, line))
		lineCount++;
	
	infile.close();

	if (passwordFile == 2)
                infile.open("pwd2.txt");
        else if (passwordFile == 3)
                infile.open("pwd3.txt");
        else
                cout << "Error\n";	

	//storing hashes into array for creating BST
	string hashes[lineCount];
	int count = 0;
	while (getline(infile, line)) {
		
		int pos; 

		//reverse find, getting position of last space character in each line
		for (int i = line.length() - 1; i >= 0; i--)
			if (line[i] == ' ') {
				pos = i;
				break;
			}
		//substring line to store hash
		hashes[count] = line.substr(pos + 1);

		count += 1;

	}
	
	

	//sorting with bubble sort to make BST balanced
	bool swap = false;
	do {
		//sizeof(hashes)/sizeof(hashes[0] is the amount of elements in the array	
		for (int i = 0; i != sizeof(hashes)/sizeof(hashes[0]) - 1; i++) {
			
			swap = false;

			if (hashes[i] > hashes[i+1]) {
				string tmp = hashes[i+1];
				hashes[i+1] = hashes[i];
				hashes[i] = tmp;
				swap = true;
			}
				
		}
	}
	while (swap);
	
	//add middle element of array of hashes to first element of BST
	//hashes[sizeof(hashes)/sizeof(hashes[0])/2] should be the middle element 
        if (!insertNode(head, hashes[sizeof(hashes)/sizeof(hashes[0])/2]))
        	cout << "Error adding to tree" << endl;
	
	//add all elements except middle element to tree
	for (int i = 0; i != sizeof(hashes)/sizeof(hashes[0]); i++)
		if (i != sizeof(hashes)/sizeof(hashes[0])/2)
				if (!insertNode(head, hashes[i]))
					cout << "Error adding to tree" << endl;

	
	

	//brute force section
	//
	//generating passwords by creating strings incrementally and
	//hashing them and comparing to BST
	
	useconds_t usec = 1000;

	//holds the original random string
	string randomString = "a";	
	
	//append values depending on what lower bound of password length is set to
	for (int i = 0; i != passwordLengthLB - 1; i++)
		randomString += "a";

	//holds the hashed string
	string randomHashString;
	
	/*
	//loops up to max possible different passwords 
	for (long i = 0; i != pow(26, passwordLengthUB); i++) {
		
		usleep(usec);

		//stores data in cstring to pass to hash function
		unsigned char randomCString[randomString.length()];
		
		for (int j = 0; j != randomString.length(); j++) {
			randomCString[j] = randomString[j];
		}
		
		randomHashString = hashFunction(randomCString);
		
		cout << randomString << endl;

		//search bst for same hash string
		if (findNode(head, randomHashString)) {
			cout << "password cracked after " << i << " tries!" << endl;
			break;
		}


		

		for (int j = 0; j != randomString.length(); j++) {
		
			if ()
		
		} 	
	

	}
	*/


	cout << "password found: " << randomString << endl;
	
	deleteTree(head);
	
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

bool insertNode (Node * head, string str) {
	
	bool success = false;

	//if tree is empty
	if ((head->str == "") && (head->left == NULL) && (head->right == NULL)) {
		head->str = str;
		head->left = NULL;
		head->right = NULL;
		//cout << "first node entered into BST" << endl;
		success = true;
	}

	//first need to see if we are looking to left or right
	
	//if we are going to the left
	else if (str < head->str) {
		
		//if parent node doesn't have the child allocated
		//then set it
		if (head->left == NULL) {
			Node * n = new Node;
			n->left = NULL;
			n->right = NULL;
			n->str = str;
			head->left = n;
			//cout << "Node added to tree with str " << str << endl;
			success = true;
		}
		//else recursively move through arr
		else {
			insertNode(head->left, str);
			success = true;
		}
		

	}
	//if we are going to the right
	else if (str > head->str) {
	
		if (head->right == NULL) {
			Node * n = new Node;
                        n->left = NULL;
                        n->right = NULL;
                        n->str = str;
			head->right = n;
			//cout << "Node added to tree with str " << str << endl;
			success = true;
		}
		else {
			insertNode(head->right, str);
			success = true;
		}
	
	}
	return success;
	

	

}

//print inorder traversal of tree
void inOrder(Node * head) {
	
	if (head != NULL) {
	
		inOrder(head->left);
		cout << head->str << endl;
		inOrder(head->right);

	}

}
//returns true if node with str found
bool findNode(Node * head, string str) {
	
	while (head != NULL) {
	
		if (str > head->str)
			head = head->right;

		else if (str < head->str)
			head = head->left;
		else
			return true;
	
	}


}

void deleteTree(Node * head) {

	if (head == NULL)
		return;

	deleteTree(head->left);
	deleteTree(head->right);

	//cout << "deleting node: " << head->str << endl;
	delete head;

}
