#include "DateGroupingStrategy.h"

Comparator DateGroupingStrategy::getComparator()
{
    return Comparator(SortingCriterion::Date, this->sortDirection);
}

void DateGroupingStrategy::groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups)
{
    Group* dateGroup = findGroupByName(groups, "Дата создания");

    if (!dateGroup)
    {
        // Группа "Дата создания" не найдена, обработка ошибки
        throw std::runtime_error("Группа 'Дата создания' не найдена.");
    }

    Comparator dateComparator = getComparator();

    QDateTime currentDate = QDateTime::currentDateTime();

    for (Object obj : objects)
    {
        QDateTime createDate = obj.getDate();

        if (createDate.isValid())
        {
            std::string subgroupName;

            if (createDate.date() == currentDate.date())
            {
                subgroupName = "Сегодня";
            }
            else if (createDate.date() == currentDate.date().addDays(-1))
            {
                subgroupName = "Вчера";
            }
            else if (createDate.date() >= currentDate.date().addDays(-7))
            {
                subgroupName = "На этой неделе";
            }
            else if (createDate.date().year() == currentDate.date().year())
            {
                subgroupName = "В этом году";
            }
            else
            {
                subgroupName = "Ранее";
            }

            // Проверяем, есть ли такая подгруппа, и создаем ее, если нет
            if (!dateGroup->getSubgroup(subgroupName))
            {
                dateGroup->addSubgroup(subgroupName, dateComparator);
            }

            Subgroup* subgroup = dateGroup->getSubgroup(subgroupName);
            subgroup->addObject(obj);
        }
    }
}
