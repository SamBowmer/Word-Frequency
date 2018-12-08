#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

/*******************************************************************************
									Sam Bowmer
*******************************************************************************/
//~~~~~~~~~~~~~~~~~~~~~~~ GLOBAL VARIABLES & CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~~~
struct word {
	int count;
	string contents;
};
const int maxSize = 50000;
char fileName[maxSize];
word  words[maxSize];
int wordsIndex = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTION PROTOTYPES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void insert(string toInsert);
void print();
void printFirst(int toPrint);
void printLast(int toPrint);
void removePunct(string &str);
void siftUp(int i);
void swap(word *left, word *right);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(int argc, char** argv) {
	string temp;
	cout << "File name: ";
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);
	if(!fin.good()) {
		cout<<"File not good"<<endl;
		return 1;
	}

	while(!fin.eof()){
		fin >> temp;
		removePunct(temp);														//remove punction from the string
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);			//turn all characters in temp to lowercase
		if (temp != "") {														//only insert temp if it isn't empty (removePunc may have done this)	
			insert(temp);
		}
	}
	cout << "\n10 Most Frequent Words:\n";
	printFirst(10);

	return 0;
}

void insert(string toInsert) {
	for (int i=0; i < wordsIndex; i++) {										//loop through words to see if any match
		if(toInsert.compare(words[i].contents) == 0) {							//	if toInsert matches
			words[i].count++;													//		add one to the word's count	
			siftUp(i);															//		sift the word up												
			return;																//		exit function
		}
	}
	
	if (wordsIndex < maxSize) {													//if we haven't filled words
		word tempWord;															//	create a new word
		tempWord.contents = toInsert;											//
		tempWord.count = 1;														//
		words[wordsIndex] = tempWord;											//	append new word to words
		siftUp(wordsIndex);														//	move the word to its correct place
		wordsIndex++;							
	}
}

void printFirst(int toPrint) {
	for (int i = 0; i < toPrint && i < wordsIndex; i++) {
		cout << words[i].contents 
			 << setw(20 - words[i].contents.length()) 
			 << words[i].count << endl;
	}
}

void removePunct(string &str) {
	signed int i = 0;
	while ((signed)i < (signed)str.size()) {
		if (ispunct((signed)str[(signed)i])) {
			str.erase((signed)i);
		}
		i++;
	}
}

void siftUp(int i) {	//sifts the word at position i to its correct spot in the array
	if (i > 0) {																//if we haven't reached the beginning of the array
		if (words[i].count > words[i-1].count) {								//	if this word's count > next word's count
			swap(words[i], words[i-1]);											//		swap them
			siftUp(i-1);														//		run siftUp with the next word
		}																		//
		else if (words[i].count == words[i-1].count){							//	if both words have the same count	
			if (words[i].contents.compare(words[i-1].contents) < 0) {			//		if this word comes before next word in alphabet
				swap(words[i], words[i-1]);										//			swap them
				siftUp(i-1);													//			run siftUp with the next word
			}
		}
	}
}

void swap(word *left, word *right) {
	word temp = *left;
	*left = *right;
	*right = temp;
}
