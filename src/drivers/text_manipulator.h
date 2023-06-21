#ifndef __TEXT_MANIPULATOR_H__
#define __TEXT_MANIPULATOR_H__

#include <cctype>
#include <string>

std::string toUpperCase(const std::string &str);
std::string toUintStringNZ(std::string len);
void addTabs(std::string &str);

#endif // __TEXT_MANIPULATOR_H__