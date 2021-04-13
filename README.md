# Monte Carlo Method for Breaking a Substitution Cipher

Implemented by Ethan Letourneau

About:
------
This is an implementation of the Monte Carlo Method for breaking a substitution cypher using bigram frequency analysis.
There are two programs here:

getbigrams - Gets the frequency of all bigrams (of only letters and spaces) from a specified text file on line 20 of the source code, and prints the data to a file "bigrams.txt". 

decryptsub - The main program. Takes in a text file that is encrypted with a substitution cipher (alphabet to alphabet) and outputs the decrypted plaintext.


How to Run:
-----------
Compile the getbigrams program with the following command: "g++ -std=c++11 -o getbigrams.exe getbigrams.cpp".

Compile decryptsub with the "make" command with the accompanying makefile in the same directory. Run by the following command:

decryptsub.exe <input filename>

NOTE: Need a "bigrams.txt" file in the same directory with the same format as the one provided.
If you un-comment the test output before compiling, I suggest doing something like this:

decryptsub.exe <input filename> > log.txt


