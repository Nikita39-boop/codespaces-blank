#include "Group.h"

void Group::addSubgroup(const std::string& subgroupName, Comparator comparator)
{
    subgroups.emplace(subgroupName, Subgroup(comparator));
}

void Group::clearSubgroups()
{
    this->subgroups.clear();
}

Subgroup* Group::getSubgroup(const std::string& subgroupName)
{
    // Проверяем, есть ли такая подгруппа
    auto it = subgroups.find(subgroupName);
    if (it != subgroups.end()) 
    {
        return &it->second; // Возвращаем указатель на найденную подгруппу
    }
    else 
    {
        return nullptr; // Возвращаем nullptr, если подгруппа не найдена
    }
}
