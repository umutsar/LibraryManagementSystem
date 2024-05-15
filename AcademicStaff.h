#ifndef ACADEMICSTAFF_H
#define ACADEMICSTAFF_H

#include "BasePerson.h"

class AcademicStaff : public BasePerson {
public:
    AcademicStaff();
    void displayInfo() const override;
    void setDepartment(const std::string& department);
    void setPosition(const std::string& position);

    std::string getDepartment() const;
    std::string getPosition() const;

private:
    std::string department;
    std::string position;
};

#endif 