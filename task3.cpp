#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main() {
        int passwordFile, maxPasswordLength;
        cout << "Enter password file (2 or 3): ";
        cin >> passwordFile;
        cout << endl << "Enter max password length (3-8): ";
        cin >> maxPasswordLength;
        cout << passwordFile << " " << maxPasswordLength << endl;
        
  return 0;
}
