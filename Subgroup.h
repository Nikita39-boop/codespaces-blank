#pragma once
#include <set>
#include "Object.h"
#include "Comparator.h"

class Subgroup 
{
private:
    std::multiset<Object, Comparator> objects;
    Comparator comparator;
public:
    Subgroup(const Comparator& comparator) : comparator(comparator), objects(comparator) {}

    void addObject(const Object& object);
    std::multiset<Object, Comparator> getObjects() { return objects; }
};

