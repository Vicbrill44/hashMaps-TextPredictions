

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
		map[idx] = new hashNode(k,v);
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
	int stringSize = k.size();
	int h = 0;
	int prime = 11;
	if(stringSize == 1){
		h = ((int)k[0]) % mapSize;
	}
	else if(stringSize == 2){
		h = (((int)k[0]) + ((int)k[1])*prime) % mapSize;
	}
	else{
		h = (((int)k[0]) + ((int)k[1])*prime + ((int)k[2])*(prime*prime)) % mapSize;

	}
	return h;

}
int hashMap::calcHash1(string k){
	//code this
	int stringSize = k.size();
	int h = 0;
	int prime = 11;
	for(int i = stringSize - 1; i > 0; i--){
		h = (h * prime + ((int)k[i])) % mapSize;
	}
	return h;
}
void hashMap::getClosestPrime() {
	int primesList[122] = {
			31, 61, 97, 131, 173, 211, 251, 293, 337, 379, 419, 457, 499, 541, 577,
			619, 661, 701, 739, 773, 811, 853, 887, 929, 967, 1009, 1049, 1091, 1129,
			1169, 1201, 1249, 1291, 1327, 1367, 1409, 1451, 1487, 1523, 1567, 1607,
			1657, 1693, 1733, 1777, 1811, 1847, 1889, 1931, 1979, 2017, 2053, 2099,
			2137, 2179, 2221, 2267, 2309, 2347, 2381, 2417, 2459, 2503, 2539, 2591,
			2633, 2683, 2719, 2767, 2803, 2843, 2887, 2939, 2971, 3011, 3049, 3089,
			3137, 3181, 3221, 3259, 3299, 3343, 3389, 3433, 3469, 3511, 3557, 3593,
			3631, 3671, 3709, 3761, 3803, 3847, 3881, 3919, 3967, 4007, 4051, 4091,
			4127, 4177, 4217, 4259, 4297, 4339, 4373, 4421, 4463, 4507, 4547, 4591,
			4639, 4679, 4721, 4759, 4801, 4831, 4877, 4919, 4951
	};
	int primeToFind = mapSize*2;
	int primeLstLen = 122; //length of primes list
	//binary search
	int low = 0;
	int high = primeLstLen - 1;
	int mid = 0;
	int foundPrime;
	while(low<=high){
		mid = low + (high - low) / 2;
		if(primesList[mid]>primeToFind){
			foundPrime = mid;
			high = mid -1;
		}
		else{
			low = mid + 1;
		}
	}
	foundPrime = primesList[foundPrime];
	mapSize = foundPrime;

}
void hashMap::reHash() {
	//double size of mapSize
	int oldMapSize = mapSize;
	getClosestPrime();
	int newIdx;


	//initiialize a new map with the new size doubled
	hashNode **newMap = new hashNode*[mapSize];
	numKeys = 0;
	int j = 0;
	//set everything in the map as NULL
	while(j<mapSize){
		newMap[j] = NULL;
		j++;
	}

	for(int i = 0; i<oldMapSize;i++){
		hashNode *node = map[i];
		if(node!=NULL){
			hashNode *temp = node;
			newIdx = getIndex(temp->keyword);
			newMap[newIdx] = temp;
			numKeys += 1;

			delete temp;
		}
	}
	//set map to be this newMap we created
	map = newMap;

}
int hashMap::coll1(int h, int i, string k) {
	int probing = i + 1;
	while(map[probing]!= NULL){
		if(map[probing]->keyword == k){
			collisions +=1;
			break;
		}
		probing +=1;
		if(probing == mapSize){
			probing = 0;
		}
		collisions +=1;
	}

	return probing;
}
int hashMap::coll2(int h, int i, string k) {
	int counter = 0;
	int probing = i;
	while(map[probing]!= NULL){
		if(map[probing]->keyword == k){
			collisions +=1;
			break;
		}
		probing = (probing +((int)pow(counter, counter))) % mapSize;
		counter +=1;
		if(probing > mapSize){
			probing = 0;
		}
		collisions += 1;
	}
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
	cout << "There are: "<<numKeys<<" keys filled in the hashMap"<<endl;
}

