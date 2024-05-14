#ifndef ADMIN_H
#define ADMIN_H

#include "Expert.h"

class Admin : public Expert {
public:
    void displayInfo() const override;
};

#endif // ADMIN_H