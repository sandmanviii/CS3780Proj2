# CS3780Proj2

This is a project to simulate brute force hacking. Task1.cpp is used to "login" to the program. It is for testing if the brute force worked correctly. Task2.cpp generates random usernames and passwords across the 3 password files. There is a plaintext password file, a username + hashed password file, and a username + salt + salty hashed password file. We used openssl to generate hashed passwords and to randomly create usernames and passwords. Task3.cpp takes in what password file you want to try and crack, needs to be 2 or 3. It will then store the hashed passwords in a binary tree for quicker comparisons. It starts generating passwords, hashing them, and comparing to the binary tree. If a matching hash is found, that means a password was cracked. 

