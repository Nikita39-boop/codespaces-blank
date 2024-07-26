#include <iostream>
#include <algorithm>
#include "TypeGroupingStrategy.h"

Comparator TypeGroupingStrategy::getComparator()
{
	return Comparator(SortingCriterion::Name, this->sortDirection);
}

void TypeGroupingStrategy::groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups)
{
    Group* typeGroup = findGroupByName(groups, "Тип");

    if (!typeGroup)
    {
        // Группа "Тип" не найдена, обработка ошибки
        throw std::runtime_error("Группа 'Тип' не найдена.");
    }

    Comparator typeComparator = getComparator();

    int typeCount = 0;
    for (Object obj : objects)
    {
        std::string type = obj.getType();
        typeCount = std::count_if(objects.begin(), objects.end(), [type](const Object& o) 
            {
                return o.getType() == type;
            });

        if (typeCount < this->minimumNumberOfTypeObjects)
        {
            type = "Разное";
        }

        Subgroup* subgroup = typeGroup->getSubgroup(type);
        if (!subgroup)
        {
            typeGroup->addSubgroup(type, typeComparator);
            subgroup = typeGroup->getSubgroup(type);
        }
        subgroup->addObject(obj);
    }
}
