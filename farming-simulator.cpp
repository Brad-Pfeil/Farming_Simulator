#include <cctype>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <stdio.h>
#include "Farm.h"
#include "Seed.h"
#include "Vegetable.h"
#include "Grain.h"

using namespace std;

//forward declating functions for later
void visit();
void goField();
void fieldoption();
void goShop();
void goMarket();
void plantMenu();
void harvestPrint();
void noHarvest();
void buySeeds(string cropName, char symbol, int growth, int buy, int sell, string cropCategory);
void winGame();
int checkAnyMatureCrops();

Farm *farmingSimulator = new Farm();
Seed **field = farmingSimulator->getField();
Seed **seeds = farmingSimulator->getSeeds();

void clearScreen() {
  cout << "\033[2J\033[1;1H";
}

bool checkEmptyArr(Seed **checkArray) {

  int empty = 0;

  for (int i=0; i<16; i++) {
    if (checkArray[i] == NULL) {
      empty++;
    }
  }

  if (empty == 16) {
    return true;
  } else {
    return false;
  }
}

bool checkFullArr(Seed **checkArray) {

  int full = 0;

  for (int i=0; i<16; i++) {
    if (checkArray[i] != NULL) {
      full++;
    }
  }

  if (full == 16) {
    return true;
  } else {
    return false;
  }

}

int countArr(Seed **countArray) {
  int count = 0;
  for (int i=0; i<16; i++) {
    if (countArray[i] != NULL) {
      count++;
    }
  }
  return count;
}

void printField() {
  cout << endl;
  cout << "    FUNDS: $" << farmingSimulator->getMoney() << endl;
  cout << endl;
  for (int i=0; i<16; i++) {
    cout << "  ";
    if (field[i] == NULL) {
      cout << " @";
    } else {
      field[i]->updateLetter();
      cout << " " << field[i]->getFieldLetter();
    }
    if ((i+1) % 4 == 0) {
    cout << endl;
    }
  }
  cout << endl;
}

void bankrupt() {
  clearScreen();
  cout << "You don't have enough money left to complete this action." << endl;
}

void invalidOption() {
  cout << endl;
  cout << "Invalid input option." <<  endl;
  cout << "Please enter one of the numbers above." << endl;
}

void invalidNumber() {
  cout << endl;
  cout << "You can't purchase a negative number of items" << endl;
  cout << "Please enter a number greater than zero." << endl;
  cout << endl;
}

void switchCinContinue() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void endGame() {
  cout << endl;
  cout << "- - - - -  Thanks for playing our game  - - - - -" << endl;
  cout << endl;
  delete farmingSimulator;
}

void startMenu() {

  bool loop = true;
  int option;
  cin >> option;

  while (loop == true) {
    switch (option) {
      case 1:
              visit();
              loop = false;
              break;
      case 2:
              clearScreen();
              endGame();
              loop = false;
              break;
      default:
              invalidOption();
              switchCinContinue();
              cin >> option;
              break;
    }
  }
}

void start() {

  clearScreen();

  cout << endl;

  cout << "- - - - -  WELCOME TO OUR OOP GAME  - - - - -" << endl;

  cout << endl;

  cout << "Your goal is to reach funds of $500 by selling crops you've grown." << endl;
  cout << endl;
  cout << "Crops can only be harvested once fully grown," << endl;
  cout << "Each time you water a crop, it gains +1 growth." << endl;
  cout << endl;
  cout << "When mature, a crop's signifier will go from lowercase to uppercase." << endl;
  cout << endl;
  cout << "Don't let your plants continue to grow for too long." << endl;
  cout << "After they're mature, they can rot and become fertiliser!" << endl;
  cout << endl;
  cout << "During the game, select the action you'd like to take by typing its number." << endl;
  cout << endl;

  cout << "1. START" << endl;
  cout << "2. EXIT" << endl;

  startMenu();

}

void visitOption() {

  cout << endl;
  cout << "VISIT:" << endl;
  cout << "1. FIELD" << endl;
  cout << "2. SHOP" << endl;
  cout << "3. EXIT" << endl;

  bool loop = true;
  int option;
  cin >> option;

  while (loop == true) {
    switch (option) {
      case 1:
              goField();
              loop = false;
              break;
      case 2:
              goShop();
              loop = false;
              break;
      case 3:
              clearScreen();
              endGame();
              loop = false;
              break;
      default:
              invalidOption();
              switchCinContinue();
              cin >> option;
              break;
    }
  }
}

void visit() {
  clearScreen();
  visitOption();
}

void plantoption() {

  clearScreen();
  cout << "Which seed would you like to plant?" << endl;
  cout << endl;

  int seedIndex = 0;

  for (int i=0; i<16; i++) {
    if (seeds[i] != NULL) {
      seedIndex++;
      cout << seedIndex << ". " << seeds[i]->getType() << endl;
    }
  }

  cout << endl;
  cout << "0. GO BACK" << endl;

  bool loop = true;
  int option;
  cin >> option;

  int notNullCounter;
  int optionIndex;

  while (loop == true) {

    notNullCounter = 1;
    optionIndex = 0;

    for (int i=1; i<=16; i++) {
      if (seeds[i-1] != NULL) {
        if (notNullCounter == option) {
          optionIndex = i-1;
        }
        notNullCounter++;
      }
    }

    if (option == 0) {
      clearScreen();
      printField();
      fieldoption();
    }

    if (notNullCounter <= option) {
      invalidOption();
      switchCinContinue();
      cin >> option;
    } else {

      farmingSimulator->plantSeed(seeds[optionIndex]);
      clearScreen();
      printField();
      cout << "You have planted a " << seeds[optionIndex]->getType() << " seed!" << endl;
      cout << endl;
      seeds[optionIndex] = NULL;
      fieldoption();
      loop = false;

    }
  }
}

void plantMenu() {
  if (checkEmptyArr(seeds) == true) {
    clearScreen();
    cout << endl;
    cout << "You have no seeds! Try buying some at the shop." << endl;
    visitOption();
  } else {
    plantoption();
  }
}

void fertiliseOption() {

  clearScreen();
  cout << endl;
  cout << "FERTILISERS: " << farmingSimulator->getFertiliser() << endl;
  cout << endl;
  cout << "Which plant would you like to fertilise?" << endl;

  for (int i=0; i<16; i++) {
    if (field[i] != NULL && field[i]->isFertilised() == false) {
      cout << i+1 << ". " << field[i]->getType() << endl;
    }
  }

  bool loop = true;
  int option;
  cin >> option;

  while (loop == true) {

    if (field[option-1] == NULL ) {

      invalidOption();
      switchCinContinue();
      cin >> option;

    } else if (field[option-1]->isFertilised() == 0) {

      farmingSimulator->fertiliseCrop(field[option-1]); //fertiliseCrop(field[option-1]);
      clearScreen();
      printField();
      cout << "You've fertilised " << field[option-1]->getType() << "!" << endl;
      cout << endl;
      fieldoption();
      loop = false;

    }
  }
}

bool checkFieldFertilised() {

  int numFertilised = 0;

  for (int i=0; i<16; i++) {
    if (field[i] != NULL) {
      if (field[i]->isFertilised() == true) {
        numFertilised++;
      }
    }
  }
  if (numFertilised == countArr(field)) {
    return true;
  }
  return false;
}

void fertiliseMenu() {
  clearScreen();
  if (farmingSimulator->getFertiliser() == 0) {
    cout << endl;
    cout << "You have no fertiliser. Try buying some at the shop." << endl;
    cout << "Rotten crops (X in the field) become fertiliser when harvested." << endl;
    cout << endl;
    cout << "It helps your vegetable plants grow an extra veges per harvest," << endl;
    cout << "and fully grows your grains instantly." << endl;
    visitOption();
  } else if (checkEmptyArr(field) == true) {
    cout << "You have no crops to fertilise." << endl;
    cout << "Try buying some seeds at the shop and planting them." << endl;
    visitOption();
  } else if (checkFieldFertilised() == true) {
    cout << "All your crops have already been fertilised." << endl;
    cout << "Try buying some seeds at the shop and planting them." << endl;
    visitOption();
  } else {
    fertiliseOption();
  }
}

void fieldOutput() {
  cout << endl;
  cout << "What would you like to do?" << endl;
  cout << "1. Plant crops" << endl;
  cout << "2. Water crops" << endl;
  cout << "3. Harvest crops" << endl;
  cout << "4. Fertilise crops" << endl;
  cout << "5. Go elsewhere" << endl;
}

void fieldoption() {

  fieldOutput();

  bool loop = true;
  int option;

  cout << endl;
  cin >> option;

  while (loop == true) {

    switch(option) {

      case 1:
              cout << endl;
              plantMenu();
              loop = false;
              break;
      case 2:
              if (farmingSimulator->checkIfBankrupt(countArr(field)) == false) {
                farmingSimulator->waterCrops();
                clearScreen();
                printField();
                if (checkEmptyArr(field) == false) {
                  cout << "You've watered all of your crops." <<  endl;
                } else {
                  cout << "You have no crops to water! Try planting some seeds." <<  endl;
                }
                fieldOutput();
                switchCinContinue();
                cin >> option;
                break;
              } else {
                printField();
                bankrupt();
                cout << endl;
                cout << "Harvest any crops you can to earn some money. However, if" << endl;
                cout << "you have no crops to harvest, then unfortunately you" <<  endl;
                cout << "can't make any more money, since you can't afford to grow" <<  endl;
                cout << "more crops to sell. " <<  endl;
                fieldOutput();
                switchCinContinue();
                cin >> option;
                break;
              }
      case 3:
              if (checkAnyMatureCrops() == 0) {
                noHarvest();
              } else {
                farmingSimulator->harvestCrops();
                clearScreen();
                printField();
                cout << endl;
                harvestPrint();
              }

              if (farmingSimulator->getMoney() >= 500){
                winGame();
                loop = false;
                break;
              }

              fieldOutput();
              switchCinContinue();
              cin >> option;
              break;
      case 4:
              fertiliseMenu();
              loop = false;
              break;
      case 5:
              visit();
              loop = false;
              break;
      default:
              invalidOption();
              switchCinContinue();
              cin >> option;
              break;
    };
  }
}

void goField() {

  clearScreen();
  printField();
  fieldoption();

}

void menuAfterBuying() {

  cout << endl;
  cout << "1. Return to shop" << endl;
  cout << "2. Go elsewhere" << endl;
  cout << endl;

  bool loop = true;
  int option;
  cin >> option;

  while (loop == true) {
    switch(option) {
      case 1:
              goShop();
              loop = false;
              break;
      case 2:
              visit();
              loop = false;
              break;

      default:
              invalidOption();
              switchCinContinue();
              cin >> option;
              break;
    }
  }
}

void buySeeds(string cropName, char symbol, int growth, int buy, int sell, string cropCategory) {

  clearScreen();
  int buyNum;

  cout << endl;
  cout << "How many "<< cropName <<" seeds would you like to buy?" << endl;
  cout << endl;
  cin >> buyNum;

  if (buyNum < 0) {
    invalidNumber();
    switchCinContinue();
    cin >> buyNum;
  }

  if (farmingSimulator->checkIfBankrupt(buy*buyNum) == false) {

    for (int i=0; i<buyNum; i++) {
      farmingSimulator->TakeMoney(buy);
      if (checkFullArr(seeds) == false){
        if (cropCategory.compare("grain") == 0){
          farmingSimulator->addSeed(new Grain(cropCategory, cropName, symbol, growth, buy, sell), seeds);
        } else if (cropCategory.compare("vegetable") == 0){
          farmingSimulator->addSeed(new Vegetable(cropCategory, cropName, symbol, growth, buy, sell), seeds);
        } 
      } else {
        cout << "You've reached the max seed storage capacity of 16." << endl;
        cout << "Please plant some then buy more." << endl;
        visitOption();
        break;
      }
    }

    cout << "You have bought " << buyNum << " " << cropName << " seed";
    if (buyNum > 1){
      cout<<"s";
    }
    cout<<"."<<endl;

  } else {
    bankrupt();
  }
  menuAfterBuying();
}


void buyFertiliser() {

  clearScreen();
  int buyNum;

  cout << endl;
  cout << "How many fertilisers would you like to buy?" << endl;
  cout << endl;
  cin >> buyNum;

  if (buyNum < 0) {
    invalidNumber();
    switchCinContinue();
    cin >> buyNum;
  }

  if (farmingSimulator->checkIfBankrupt(buyNum*5) == false) { 

    farmingSimulator->TakeMoney(buyNum*5);
    farmingSimulator->addFertiliser();
    cout << endl;
    cout << "You have bought " << buyNum << " " << "fertiliser";
    if (buyNum > 1){                                                  
      cout << "s";
    }
    cout << "." << endl;

  } else { 
    bankrupt();
  }
  menuAfterBuying();
}

void shopOption() {

  bool loop = true;
  int option;
  cin >> option;

    if (option < 0) {
    cout << "You can't purchase a negative amount of items" << endl;
    
  }

  string cropName = "";
  string cropCategory = "";
  char symbol = '?';
  int growth, buy, sell;

  while (loop == true) {

    cropName = "";

    switch(option) {
      case 1:
              buyFertiliser();
              loop = false;
              break;
      case 2:
              cropName = "radish";
              symbol = 'r';
              growth = 3;
              buy = 6;
              sell = 15;
              cropCategory = "vegetable";
              loop = false;
              break;
      case 3:
              cropName = "cucumber";
              symbol = 'c';
              growth = 5;
              buy = 8;
              sell = 18;
              cropCategory = "vegetable";
              loop = false;
              break;
      case 4:
              cropName = "tomato";
              symbol = 't';
              growth = 8;
              buy = 10;
              sell = 24;
              cropCategory = "vegetable";
              loop = false;
              break;
      case 5:
              cropName = "barley";
              symbol = 'b';
              growth = 2;
              buy = 20;
              sell = 5;
              cropCategory = "grain";
              loop = false;
              break;
      case 6:
              cropName = "wheat";
              symbol = 'w';
              growth = 4;
              buy = 30;
              sell = 10;
              cropCategory = "grain";
              loop = false;
              break;
      case 7:
              visit();
              loop = false;
              break;
      default:
              invalidOption();
              switchCinContinue();
              cin >> option;
              break;
    }

    if (cropName.compare("") != 0){
      buySeeds(cropName, symbol, growth, buy, sell, cropCategory);
    }
  }
}

void goShop() {

  clearScreen();

  cout << "____________" << endl;
  cout << "----SHOP----    MONEY: $" << farmingSimulator->getMoney() << endl;
  cout << "‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
  cout << "$5  | FERTILISER   | grows grains faster, +1 vege yield" << endl;
  cout << "$6  | RADISH       | ready to harvest at 3 growth, can harvest 3 times" << endl;
  cout << "$8  | CUCUMBER     | ready to harvest at 5 growth, can harvest 3 times" << endl;
  cout << "$10 | TOMATO       | ready to harvest at 8 growth, can harvest 3 times" << endl;
  cout << "$20 | BARLEY       | ready to harvest at 1 growth, unlimited harvests" << endl;
  cout << "$30 | WHEAT        | ready to harvest at 4 growth, unlimited harvests" << endl;
 
  cout << "What would you like to buy today?" << endl;
  cout << endl;
  cout << "1. Fertiliser" << endl;
  cout << "2. Radish" << endl;
  cout << "3. Cucumber" << endl;
  cout << "4. Tomato" << endl;
  cout << "5. Barley" << endl;
  cout << "6. Wheat" << endl;
  cout << "7. Go elsewhere" << endl;

  shopOption();

}

int checkAnyMatureCrops() {
  int matureCrops = 0;
  for (int i=0; i<16; i++) {
    if (field[i] != NULL) {
      if (field[i]->getGrowthP() >= field[i]->getGrowthReq()) {
        matureCrops++;
      }
    }
  }
  return matureCrops;
}

void noHarvest() {
  cout << "None of your crops are ready to be harvested yet." << endl;
  cout << "Try watering or fertilising your crops." <<  endl;
  cout << endl;
}

void harvestPrint() {

  cout << "All mature crops have been harvested and sold." << endl;

  farmingSimulator->clearHarvested();
}

void winGame() {
  clearScreen();
  cout << endl;
  cout << "You've hit your goal of $500." << endl;
  cout << "Congratulations, you've won the game!" << endl;
  cout << "Thank you for playing." << endl;
  endGame();
}

