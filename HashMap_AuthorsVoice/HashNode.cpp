

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	values[currSize] = v;
	currSize += 1;
	if(currSize == valuesSize){
		dblArray();
	}

}
void hashNode::dblArray() {
	string *newValuesArr = new string[valuesSize + valuesSize];
	for(int i = 0; i<currSize;i++){
		newValuesArr[i] = values[i];
	}
	delete[] values;

	valuesSize = valuesSize + valuesSize;
	values = newValuesArr;
}

string hashNode::getRandValue() {
	string randString;
	randString = values[rand() % currSize];
	return randString;
}
