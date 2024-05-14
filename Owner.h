#ifndef OWNER_H
#define OWNER_H

#include "Expert.h"

class Owner : public Expert {
public:
    void displayInfo() const override;
};

#endif