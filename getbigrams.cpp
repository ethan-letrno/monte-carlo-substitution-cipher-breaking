#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <list>
#include <stdio.h>
#include <ctype.h>
#include <array>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std; 
  
// driver code 
int main() 
{ 
    std::map<string,double> bigrams;
    std::map<string,double>::iterator it;

    ifstream file("war-and-peace.txt"); 
    char char1, char2;

    string tempstring;
    int counter = 0;

    file.get(char1);
    // extracting words from the file 
    while (!file.eof()) 
    { 

        file.get(char2);

        if(isalpha(char2) || isspace(char2)){

            if(isspace(char2))
                char2 = 0x20;

            tempstring = "";
            tempstring += char1;
            tempstring += char2;

            if(isspace(char2) && isspace(char1))
                continue;

            it = bigrams.find(tempstring);
            if(it == bigrams.end()){
                bigrams.insert(std::pair<string,double>(tempstring,1));
            }
            else{
                bigrams[tempstring] += 1;
            }

            counter++;
            char1 = char2;
        }

    }

    file.close();
    ofstream file2;
    file2.open ("bigrams.txt");

    it = bigrams.begin();

    while(it != bigrams.end()){
        file2 << it->first << " " << ((it->second)/counter) << setprecision(10) << std::fixed<< endl;
        it++;
    }

    return 0; 
} 
