#ifndef __FARM_H__
#define __FARM_H__

#include "Seed.h"
#include "Grain.h"
#include <string>
#include <vector>

using namespace std;

class Farm {

  private:
    Seed **field; //double pointer array for the farm
    Seed **seeds; //double pointer array for the players seeds
    int money; //farms money
    int fertiliser; //farms fertiliser count
    vector<Seed*> harvested; //vector to store seeds per harvest

  public:
          Farm();

          int getMoney(); //returns money
          void AddMoney(int addThis); //adds to money
          void TakeMoney(int takeThis); //takes from money
          bool checkIfBankrupt(int takeThis); //check if taking these money will end in bankruptcy

          int getFertiliser(); //returns fertiliser count
          void addFertiliser(); //adds a fertiliser
          void takeFertiliser(); //takes a fertiliser

          Seed **getField(); //returns field
          Seed **getSeeds(); //returns seeds
          vector<Seed*> getHarvested(); //returns harvested

          //seed actions
          bool addSeed(Seed *addThis, Seed **array); //adds a seed object to an array
          void removeSeed(Seed *removeThis, Seed **array); //removes a seed object from an array
          void waterCrops(); //adds +1 growth to all seeds in field
          void harvestCrops(); //moves mature seeds from field to harvested
          void plantSeed(Seed *plantSeed); //moves seed from seeds to field
          void fertiliseCrop(Seed *needFertiliser); //fertilises a seed
          void clearHarvested(); //clears harvested vector

          ~Farm();
};


#endif //__FARM_H__
