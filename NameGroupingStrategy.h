#pragma once
#include "GroupingStrategy.h"

class NameGroupingStrategy : public GroupingStrategy 
{
public:
    Comparator getComparator() override;
    void groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups) override;

    bool isRussianLetter(QChar letter);
};

