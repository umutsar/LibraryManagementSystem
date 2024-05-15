#include "AcademicStaff.h"
#include <iostream>

AcademicStaff::AcademicStaff()
{
    department = "";
    position = "";
}

void AcademicStaff::displayInfo() const
{
    std::cout << "Akademik Personel ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << "\nBölüm: " << department << "\nPozisyon: " << position << std::endl;
}

void AcademicStaff::setDepartment(const std::string &department)
{
    this->department = department;
}

void AcademicStaff::setPosition(const std::string &position)
{
    this->position = position;
}

std::string AcademicStaff::getDepartment() const
{
    return department;
}

std::string AcademicStaff::getPosition() const
{
    return position;
}