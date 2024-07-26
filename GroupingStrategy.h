#pragma once
#include <vector>
#include "Object.h"
#include "Group.h"

class Comparator;

class GroupingStrategy 
{
protected:
    SortDirection sortDirection;
public:
    GroupingStrategy() : sortDirection(SortDirection::Ascending) {}

    virtual void groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups) = 0;
    virtual Comparator getComparator() = 0;
    virtual ~GroupingStrategy() {}

    void setSortDirection(const SortDirection& direction);

    Group* findGroupByName(std::vector<Group>& groups, const std::string& groupName);
};

