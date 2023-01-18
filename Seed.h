#ifndef __SEED_H__
#define __SEED_H__

#include <string>

using namespace std;

class Seed {

  private:
    int buyPrice; //price to buy seeds
    int sellPrice; //price of selling crop

  protected:
    Seed();
    Seed(string category, string type, char letter, int gReq, int buy, int sell);
    string seedCategory; //stores type of seed. For example, grain or vegetable
    string seedType; //stores name of crop. For example, cucumber or wheat
    char fieldLetter; //stores letter representing crop in field array
    int growthReq; //growth points required for plant to be harvested
    int growthP; //number of current growth points
    int fertilised; //is plant fertilised?

  public:
    string getCategory(); //returns seedCategory
    string getType(); //returns seed type
    char getFieldLetter(); //returns fieldLetter
    int getBuyPrice(); //returns buyPrice
    int getSellPrice(); //returns sellPrice
    int getGrowthReq(); //returns growthReq
    int getGrowthP(); //returns growthP
    bool isFertilised(); // returns bool if plant is fertilised or not

    void grow(); //function that increase growthP
    void updateLetter(); //changes fieldLetter as needed. For example, lowercase to upper when mature, X when rotten)

    virtual void fertilise() = 0; //fertilises plant
    virtual void harvestReset() = 0; //resets harvest (grain only)
    virtual int getRemainingYields() = 0; //returns remainingYields (veg only)
    virtual int getYieldNum() = 0; //returns yieldNum (veg only)
    virtual ~Seed();

};

#endif //__SEED_H__
