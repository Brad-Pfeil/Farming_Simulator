#include "Seed.h"
#ifndef __VEGETABLE_H__
#define __VEGETABLE_H__

#include <string>

using namespace std;

class Vegetable : public Seed {
  
  private:
    int remainingYields; //stores number of remaining yields of the crop (how many more times it can be harvested)
    int yieldNum;
  public:
    Vegetable(string category, string type, char letter, int gReq, int buy, int sell); 
    void fertilise(); //function for fertilising the crop
    void harvestReset(); //function for what happens when harvested
    int getRemainingYields(); //returns remainingYields
    int getYieldNum(); //inherited
};

#endif //__VEGETABLE_H__
