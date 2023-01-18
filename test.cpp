#include "Farm.h"
#include "Seed.h"
#include "Vegetable.h"
#include "Grain.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

using namespace std;

string grainType = "wheat";
string grain = "grain";
char grainLetter = 'w';
int grainGReq = 1;
int grainBuyPrice = 20;
int grainSellPrice = 4;

string vegType = "radish";
string vegetable = "vegetable";
char vegLetter = 'r';
int vegGReq = 3;
int vegBuyPrice = 6;
int vegSellPrice = 15;



string checkString(string output, string expecting){
	if (output.compare(expecting) == 0){
		return "Passed";
	} else {
		return "expecting: " + expecting + "   but got: " + output;
	}
}

string checkInt(int output, int expecting){
	if (output == expecting){
		return "Passed";
	} else {
		return "expecting: " + to_string(expecting) + "   but got: " + to_string(output);
	}
}

string checkChar(char output, char expecting){
	if (output == expecting){
		return "Passed";
	} else {
		string output = "expecting: ";
		output += expecting;
		output += "   but got: ";
		output += output;
		return output;
	}
}

string doublePtrToString(Seed** doublePtr, int n){
	string str = "";
	for (int i = 0; i < n; i++){
		if (doublePtr[i] == NULL){
			str += " ";
		} else {
			str += doublePtr[i]->getFieldLetter();
		}
	}
	return str;
}

void testSeed(){

	// Test grain
	Grain* testGrain = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);

	cout << "--------------- TESTING SEED.CPP (GRAIN) ---------------" <<  endl;
	cout << "Test getType: " << checkString(testGrain->getType(), grainType) << endl;
	cout << "Test getFieldLetter: " << checkChar(testGrain->getFieldLetter(), grainLetter) << endl;
	cout << "Test getGrowthReq: " << checkInt(testGrain->getGrowthReq(), grainGReq) << endl;
	cout << "Test getBuyPrice: " << checkInt(testGrain->getBuyPrice(), grainBuyPrice) << endl;
	cout << "Test getSellPrice: " << checkInt(testGrain->getSellPrice(), grainSellPrice) << endl;
	cout << "Test getCategory: " << checkString(testGrain->getCategory(), grain) << endl;


	cout << "Test getGrowthP: " << checkInt(testGrain->getGrowthP(), 0) << endl;

	testGrain->grow();
	cout << "Test growth: " << checkInt(testGrain->getGrowthP(), 1) << endl;

	testGrain->grow();
	cout << "Test updateLetter(grown): " << checkChar(testGrain->getFieldLetter(), toupper(grainLetter)) << endl;

	testGrain->grow();
	testGrain->grow();
	cout << "Test growth (part 2): " << checkInt(testGrain->getGrowthP(), 4) << endl;
	cout << "Test updateLetter(rotten): " << checkChar(testGrain->getFieldLetter(), 'X') << endl;

	testGrain = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);
	cout << "Test fertilise (before): " << checkInt(testGrain->getGrowthP(), 0) << endl;
	testGrain -> fertilise();
	cout << "Test fertilise (after): " << checkInt(testGrain->getGrowthP(), grainGReq) << endl;


	// Test vegetable
	Vegetable* testVeg = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);

	cout << endl << endl;
	cout << "--------------- TESTING SEED.CPP (VEGETABLE) ---------------" <<  endl;
	cout << "Test getType: " << checkString(testVeg->getType(), vegType) << endl;
	cout << "Test getFieldLetter: " << checkChar(testVeg->getFieldLetter(), vegLetter) << endl;
	cout << "Test getGrowthReq: " << checkInt(testVeg->getGrowthReq(), vegGReq) << endl;
	cout << "Test getBuyPrice: " << checkInt(testVeg->getBuyPrice(), vegBuyPrice) << endl;
	cout << "Test getSellPrice: " << checkInt(testVeg->getSellPrice(), vegSellPrice) << endl;
	cout << "Test getCategory: " << checkString(testVeg->getCategory(), vegetable) << endl;


	cout << "Test getGrowthP: " << checkInt(testVeg->getGrowthP(), 0) << endl;

	int remainingYields = 3;
	cout << "Test getRemainingYields: " << checkInt(testVeg->getRemainingYields(), remainingYields) << endl;
	testVeg->fertilise();
	cout << "Test fertilise: " << checkInt( testVeg->getGrowthP(), vegGReq) << endl;
	cout << "Test updateLetter(fertilised): " << checkChar(testVeg->getFieldLetter(), toupper(vegLetter)) << endl;

	testVeg->harvestReset();
	cout << "Test harvestReset (growth points): " << checkInt( testVeg->getGrowthP(), 0) << endl;
	cout << "Test harvestReset (remaining yields): " << checkInt( testVeg->getRemainingYields(), remainingYields-1) << endl;

	for (int i = 0; i < remainingYields-1; i++){
		testVeg->fertilise();
		testVeg->harvestReset();
	}
	cout << "Test remainingYields: " << checkInt( testVeg->getRemainingYields(), 0) << endl;
}




void testFarm(){
	Farm *testfarm = new Farm();
	int initialFunds = 50;

	cout << endl << endl << endl;
	cout << "--------------- TESTING FARM.CPP ---------------" <<  endl;
	cout << "Test getMoney: " << checkInt(testfarm->getMoney(), initialFunds) << endl;

	int initialFertiliser = 0;
	cout << "Test getFertiliser: " << checkInt(testfarm->getFertiliser(), initialFertiliser) << endl;

	int fieldLength = 16;
	int seedLength = 16;
	int harvestLength = 20;

	Grain* c1 = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);
	Grain* c2 = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);
	Grain* c3 = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);
	Vegetable* c4 = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);
	Vegetable* c5 = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);
	Grain* c6 = new Grain(grain, grainType, grainLetter, grainGReq, grainBuyPrice, grainSellPrice);
	Vegetable* c7 = new Vegetable(vegetable, vegType, vegLetter, vegGReq, vegBuyPrice, vegSellPrice);

	testfarm->plantSeed(c1);
	testfarm->plantSeed(c2);
	testfarm->plantSeed(c3);
	testfarm->plantSeed(c4);
	testfarm->plantSeed(c5);
	testfarm->plantSeed(c6);
	testfarm->plantSeed(c7);

	string expectingField = "wwwrrwr         ";
	string currentField = doublePtrToString(testfarm->getField(), fieldLength);
	cout << "Test plantSeed: " << checkString( currentField, expectingField ) << endl;
}


int main() {
	testSeed();
	testFarm();
	return 0;
}
