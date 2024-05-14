#ifndef ACADEMICSTAFF_H
#define ACADEMICSTAFF_H

#include "BasePerson.h"

class AcademicStaff : public BasePerson {
public:
    void displayInfo() const override;

private:
    string department;
};

#endif // ACADEMICSTAFF_H