#include "Grain.h"
#include <iostream>

using namespace std;

Grain::Grain(string category, string type, char letter, int gReq, int buy, int sell):Seed(category, type, letter, gReq, buy, sell) {
}

void Grain::fertilise() {
  growthP = growthReq;
  fertilised = true;
  updateLetter();
}

void Grain::harvestReset() {
  growthP = 0;
  fertilised = false;
  if (seedType == "barley") {
    growthReq = 2;
  } else if (seedType == "wheat") {
    growthReq = 4;
  }
  updateLetter();
}

int Grain::getRemainingYields() {
  return 1;
}

int Grain::getYieldNum() {
  return 1;
}
