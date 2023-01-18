#include "Vegetable.h"
#include <string>
#include <iostream>

using namespace std;

Vegetable::Vegetable(string category, string type, char letter, int gReq, int buy, int sell):Seed(category, type, letter, gReq, buy, sell) {
  remainingYields = 3;
  yieldNum = 2;
}

int Vegetable::getYieldNum() {
  return yieldNum;
}


int Vegetable::getRemainingYields() {
  return remainingYields;
}

void Vegetable::fertilise() {
  growthP = growthReq;
  updateLetter();
  fertilised = true;
}

void Vegetable::harvestReset() {
  if (remainingYields > 0) {
    growthP = 0;
    remainingYields--;
  }
  fertilised = false;
  updateLetter();
}
