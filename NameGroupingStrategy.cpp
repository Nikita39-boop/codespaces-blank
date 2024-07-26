#include <iostream>
#include "NameGroupingStrategy.h"

Comparator NameGroupingStrategy::getComparator()
{
    return Comparator(SortingCriterion::Name, this->sortDirection);
}

void NameGroupingStrategy::groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups)
{
    Group* nameGroup = findGroupByName(groups, "Имя");

    if (!nameGroup)
    {
        // Группа "Имя" не найдена, обработка ошибки
        throw std::runtime_error("Группа 'Имя' не найдена.");
    }

    Comparator nameComparator = getComparator();

    // Перебираем объекты и добавляем их в соответствующие подгруппы
    for (Object obj : objects)
    {
        QString name = QString::fromStdString(obj.getName());
        if (!name.isEmpty())
        {
            QChar firstLetter = name[0].toUpper(); // Преобразуем в верхний регистр

            Subgroup* subgroup = nullptr; // Создаем указатель на подгруппу

            if (isRussianLetter(firstLetter))
            {
                // Если первая буква имени объекта - русская буква, получаем соответствующую подгруппу
                QString subgroupName(1, firstLetter);
                subgroup = nameGroup->getSubgroup(subgroupName.toStdString());

                // Если подгруппа не существует, создаем ее
                if (!subgroup)
                {
                    nameGroup->addSubgroup(subgroupName.toStdString(), nameComparator);
                    subgroup = nameGroup->getSubgroup(subgroupName.toStdString());
                }
            }
            else
            {
                // Если первая буква имени объекта не является русской, получаем подгруппу "#"
                subgroup = nameGroup->getSubgroup("#");

                // Если подгруппа не существует, создаем ее
                if (!subgroup)
                {
                    nameGroup->addSubgroup("#", nameComparator);
                    subgroup = nameGroup->getSubgroup("#");
                }
            }

            // Добавляем объект в подгруппу, если она существует
            if (subgroup)
            {
                subgroup->addObject(obj);
            }
        }
    }
}


bool NameGroupingStrategy::isRussianLetter(QChar letter)
{
    QChar qletter(letter);
    QString letters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    return letters.contains(qletter);
}
