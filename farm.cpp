#include "Farm.h"
#include "Seed.h"
#include "Grain.h"
#include "Vegetable.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
 
extern void winGame();
extern void bankrupt();

Farm::Farm() {

  money = 50;
  fertiliser = 0;

  Seed **fieldptr = new Seed*[16];
  Seed **seedptr = new Seed*[16];
  vector<Seed*> harvested;

  for (int i=0; i<16; i++) {
    fieldptr[i] = NULL;
    seedptr[i] = NULL;
  }

  field = fieldptr;
  seeds = seedptr;

}


// money functions

int Farm::getMoney() {
  return money;
}

void Farm::AddMoney(int addThis) {
  money = money + addThis;
}

void Farm::TakeMoney(int takeThis) {
  money = money - takeThis;
}

bool Farm::checkIfBankrupt(int takeThis) {
  if (money - takeThis >= 0) {
    return false;
  } else {
    return true;
  }
}


//fertiliser functions

int Farm::getFertiliser() {
  return fertiliser;
}

void Farm::addFertiliser() {
  fertiliser++;
}

void Farm::takeFertiliser() {
  fertiliser--;
}


//array functions

Seed **Farm::getField() {
  return field;
}

Seed **Farm::getSeeds() {
  return seeds;
}

vector<Seed*> Farm::getHarvested() {
  return harvested;
}


//Seed functions

bool Farm::addSeed(Seed *addThis, Seed **array) {
  for (int i=0; i<16; i++) {
    if (array[i] == NULL) {
      array[i] = addThis;
      return true;
    }
  }
  return false;
}

void Farm::removeSeed(Seed *removeThis, Seed **array) {
  for (int i=0; i<16; i++) {
    if (array[i]->getType() == removeThis->getType()) {
      array[i] = NULL;
      break;
    }
    break;
  }
}

void Farm::waterCrops() {
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) {
      TakeMoney(1);
      field[i]->grow();
    }
  }
}

void Farm::harvestCrops() {
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) { 

      if (field[i]->getGrowthP() == field[i]->getGrowthReq() || field[i]->getGrowthP() == field[i]->getGrowthReq()+1) {

        if (field[i]->getCategory() == "grain") {
          AddMoney(field[i]->getSellPrice());
          harvested.push_back(field[i]);
          field[i]->harvestReset();
          continue;
        }

        if (field[i]->getCategory() == "vegetable") {
            if (field[i]->getRemainingYields() > 0) {
              harvested.push_back(field[i]);
              AddMoney(field[i]->getYieldNum()*field[i]->getSellPrice());
              field[i]->harvestReset();
            } else if (field[i]->getRemainingYields() == 0){
              AddMoney(field[i]->getSellPrice());
              harvested.push_back(field[i]);
              field[i] = NULL;
              continue;
            }
          }
      } else if (field[i]->getGrowthP() == field[i]->getGrowthReq()+2) {
          harvested.push_back(field[i]);
          field[i] = NULL;
          fertiliser++;
      }
    }
  }
}

void Farm::plantSeed(Seed *plantSeed) {
  addSeed(plantSeed, field);
}

void Farm::fertiliseCrop(Seed *needFertiliser) {
  for (int i=0; i<16; i++) {
    if (field[i]->getType() == needFertiliser->getType()) {
      field[i]->fertilise();
      fertiliser--;
      break;
    }
  }
}

void Farm::clearHarvested() {
  harvested.clear();
}

Farm::~Farm() {
  delete[] field;
  delete[] seeds;
}