#include "Seed.h"
#ifndef GRAIN_H
#define GRAIN_H

#include <string>

class Grain : public Seed {
  public:
    Grain(std::string category, std::string type, char letter, int gReq, int buy, int sell);
    void fertilise(); //fertilise to be instantly ready for harvest
    void harvestReset(); ///inherited
    int getRemainingYields(); //inherited
    int getYieldNum(); //inherited
};

#endif //GRAIN_H
