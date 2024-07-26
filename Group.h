#pragma once
#include <string>
#include <unordered_map>
#include "Subgroup.h"

class Group 
{
private:
    std::string name;
    std::unordered_map<std::string, Subgroup> subgroups;
public:
    Group(const std::string& name) :name(name) {}

    void addSubgroup(const std::string& subgroupName, Comparator comparator);
    void clearSubgroups();

    Subgroup *getSubgroup(const std::string& subgroupName);
    std::unordered_map<std::string, Subgroup> getSubgroups(){return subgroups;}
    std::string getName() { return name; };
};


