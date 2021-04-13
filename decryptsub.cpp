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
#include <string>
#include <math.h>
#include <cmath>
using namespace std; 

const char ALPHABET[26] = {'a','b','c','d','e','f','g',
                    'h','i','j','k','l','m','n',
                    'o','p','q','r','s','t','u',
                    'v','w','x','y','z'};
 

//This program takes an argument for the input file name. 
int main(int argc, char *argv[]) 
{ 
    std::string input_string(argv[1]);

    std::map<string,double> bigrams;
    
    int iteration_limit = 10000; //Manually set how many iterations we'll do for the MCMC
    int iteration_count = 0;

    double previous_score = -1;
    double score = -1;

    ifstream input_b("bigrams.txt");
    ifstream input; 
    ofstream output;

    double prob;
    double random_number;

    int ind1, ind2;
    char temp_char1, temp_char2;

    //The keys will work such that each index i is representative of the i'th letter of the alphabet.
    //E.G.: if the key starts {'v', 't', 'a'...} then the encryption is that 'v' maps to 'a', 't' maps to 'b', 'a' maps to 'c'.
    char key[26];
    std::copy(std::begin(ALPHABET), std::end(ALPHABET), std::begin(key));
    char previous_key[26];
    std::copy(std::begin(ALPHABET), std::end(ALPHABET), std::begin(previous_key));

    char char1, char2;
    int punctuation_flag = 0;

    //Read in data from bigrams.txt, store into the map.
    string temp_string;
    string temp_percent_string;
    int linecount = 0;
     srand((unsigned) time(NULL));

    while(!input_b.eof()){
        input_b >> temp_string;
        if(strlen(temp_string.c_str()) == 1){
            if(linecount < 25)
                temp_string = " "+temp_string;
            else
                temp_string = temp_string+" ";
        }
        input_b >> temp_percent_string;
        bigrams.insert(std::pair<string,double>(temp_string,(atof(temp_percent_string.c_str())*1000)));
        linecount++;
    }

    //Keep track of iteration...
    while(iteration_limit > iteration_count){

        input.open(input_string);
        output.open("output.txt");

        //Traverse the encrypted input file letter by letter, applying the key to every non-punctuation char.
        //Output each "decrypted" letter (and punctuation unchanged) to output.txt
        while(!input.eof()){
            input.get(char1);
            
            if(isalpha(char1)){
                for(int i = 0; i < 26; i++){
                    if(key[i] == char1){
                        output<<ALPHABET[i];
                        break;
                    }
                }
            }
            else{ output<<char1; }
                
        }

        input.close();
        input.clear();
        input.open("output.txt");
 
        //Read output file
        input.get(char1);

        //Compute the multiplcation of all bigram frequencies on the "decrypted" file. 
        while(!input.eof()){
            input.get(char2);

            if(isalpha(char2) || isspace(char2)){
                
                if(isspace(char2))
                    char2 = 0x20;

                temp_string = "";
                temp_string += char1;
                temp_string += char2;
                
                if(bigrams[temp_string] != 0){
                    if(score == -1)
                        score = log(bigrams[temp_string]);
                    else
                        score += log(bigrams[temp_string]);

                    /* TEST: Make sure individual scores being counted right. */
                    //cout<<"Score for "<<temp_string<<" = "<<log(bigrams[temp_string])<<" (originally "<<bigrams[temp_string]<<"), key score so far = "<<score<<endl;
                }

                char1 = char2;

            }
          
        }

        //Compare score to previous key's score. If higher, we take this key by making it the previous key.
            //If lower, take with probablility n/(p+n).

        if(previous_score == -1 || previous_score < score){
            //cout<<"Previous score lower, taking the new key."<<endl;
            previous_score = score;
            std::copy(std::begin(key), std::end(key), std::begin(previous_key));
        }
        else if (previous_score != -1 && previous_score >= score){
            
            prob = (1/(1 + pow(2, (previous_score - score))))*100;
           // cout<<"Previous score higher, taking the new key with "<<prob<<" percent chance."<<endl;
            
           
            random_number = (rand() % 100) + 1;
            if(random_number < prob){
                //cout<<"Key taken because"<<random_number<<" < "<<prob<<endl;
                previous_score = score;
                std::copy(std::begin(key), std::end(key), std::begin(previous_key));
            }
            //No need to assign anything for the "else" because we're just not taking the key.
        }
    
        //Finally, make new neighbor key by swapping random indexes in previous_key;
        ind1 = (rand() % 26) ;
        ind2 = (rand() % 26) ;

        while(ind1 == ind2){ ind2 = (rand() % 26) ; } //ensure they won't be the same number for the indexes.

        //cout<<"Next key will swap "<<key[ind1]<<" and "<<key[ind2]<<endl;
        std::copy(std::begin(previous_key), std::end(previous_key), std::begin(key));
        temp_char1 = key[ind1];
        temp_char2 = key[ind2];
        key[ind1] = temp_char2;
        key[ind2] = temp_char1;

        score = -1;

        if(iteration_count+1 != iteration_limit)
            remove("output.txt");
        else{
            output<<"\n\nEncryption Key: ";
            for(int x = 0; x < 26; x++)
                output<<previous_key[x];
             
        }

        iteration_count++;
        
        /*TEST: Keep track of keys

        if(iteration_count%100){
            cout<<"Iteration ["<<iteration_count<<"/"<<iteration_limit<<"]: Score = "<<previous_score<<"."<<endl;
            cout<<"Key = ";
            for(int x = 0; x < 26; x++)
                cout<<previous_key[x];
            cout<<endl;
        }

        */

        output.close();
        output.clear();
        input.close();
        input.clear();

    }

    return 0; 

} 
