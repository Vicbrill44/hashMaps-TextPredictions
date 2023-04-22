

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	hashfn = hash1;	// either hash 1 or 2
	collfn = coll1; //either coll 1 or 2
	mapSize = 3463; //random large prime to start without problems
	numKeys = 0; //no keys yet so 0
	collisions = 0;	//no collisions to start so 0
	hashcoll = 0; //no hash collisions to start so 0

	//create the map
	map = new hashNode*[mapSize];
	int i = 0;
	//set everything in the map as NULL
	while(i<mapSize){
		map[i] = NULL;
		i++;
	}
}
void hashMap::addKeyValue(string k, string v) {
	int idx;
	idx = getIndex(k);
	//check index
	if(map[idx] == NULL){
		map[idx]->keyword = k;
		map[idx]->addValue(v);
		numKeys += 1;
	}
	else{
		map[idx]->addValue(v);
	}

	//load
	int load = (int)((mapSize*70)/100);
	if(numKeys>=load){
		reHash();
	}

}
int hashMap::getIndex(string k) {
	//we aint leaving this method without an index that works
	int idx;

	if(hashfn){
		idx = calcHash1(k);
	}
	else{
		idx = calcHash2(k);
	}

	if(map[idx] == NULL || map[idx]->keyword == k){
		return idx;
	}
	else{
		//we have a collision due to hash function
		hashcoll += 1;
		if(collfn){
			idx = coll1(0,idx,k);
		}
		else{
			idx = coll2(0,idx,k);
		}
	}
	return idx;

}

int hashMap::calcHash2(string k){
}
int hashMap::calcHash1(string k){
	//code this
	int stringSize = k.size();
	int h = 0;
	int prime = 11;
	for(int i = stringSize - 1; i > 0; i--){
		h = (h * prime + ((int)k[i])) % 3463;
	}
	return h;
}
void hashMap::getClosestPrime() {
}
void hashMap::reHash() {
}
int hashMap::coll1(int h, int i, string k) {
	int probing = i + 1;
	while(map[probing]!= NULL){
		if(map[probing]->keyword == k){
			collisions +=1;
			break;
		}
		probing +=1;
		collisions +=1;
	}

	return probing;
}
int hashMap::coll2(int h, int i, string k) {
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


