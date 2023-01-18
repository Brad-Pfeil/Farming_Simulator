
#include "Seed.h"
#include <string>
#include <cctype>

using namespace std;

Seed::Seed() {
  seedType = "?";
}

Seed::Seed(string category, string type, char letter, int gReq, int buy, int sell) {
  seedCategory = category;
  seedType = type;
  fieldLetter = letter;
  growthReq = gReq;
  growthP = 0;
  fertilised = false;
  buyPrice = buy;
  sellPrice = sell;
}

string Seed::getCategory() {
  return seedCategory;
}


string Seed::getType() {
  return seedType;
}

void Seed::updateLetter() {
  if (growthP < growthReq) {
    fieldLetter = tolower(fieldLetter); 
  }
  if (growthP == growthReq) {
    fieldLetter = toupper(fieldLetter); 
  }
  if (growthP == growthReq+2) {
    fieldLetter = 'X';
  }
}

char Seed::getFieldLetter() {
  return fieldLetter;
}

int Seed::getGrowthReq() {
  return growthReq;
}

int Seed::getGrowthP() {
  return growthP;
}

void Seed::grow() {
  growthP++;
  updateLetter();
}

int Seed::getBuyPrice() {
  return buyPrice;
}

int Seed::getSellPrice() {
  return sellPrice;
}

bool Seed::isFertilised() {
  return fertilised;
}

Seed::~Seed() {
}
