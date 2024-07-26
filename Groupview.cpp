#include "Groupview.h"
#include "DateGroupingStrategy.h"
#include "DistanceGroupingStrategy.h"
#include "GroupingStrategy.h"
#include "NameGroupingStrategy.h"
#include "TypeGroupingStrategy.h"
#include "qlineedit.h"
#include <QTreeView>
#include <QMessageBox>

GroupView::GroupView(QTabWidget *tabView, QObject *parent) : QObject(parent), tabView(tabView)
{
    Group distanceGroup("Расстояние");
    Group nameGroup("Имя");
    Group dateGroup("Дата создания");
    Group typeGroup("Тип");

    // Добавляем созданные группы в вектор groups
    this->groups.push_back(distanceGroup);
    this->groups.push_back(nameGroup);
    this->groups.push_back(dateGroup);
    this->groups.push_back(typeGroup);
}

void GroupView::updateViewWithObjects(const std::vector<Object> &objects)
{
    if (objects.empty() || groups.empty() || !tabView)
    {
        return; // Проверка на наличие данных и виджета вкладок
    }

    int currentIndex = tabView->currentIndex(); // Получите индекс активной вкладки

    // Проверяем, что индекс активной вкладки допустим
    if (currentIndex < 0 || currentIndex >= tabView->count())
    {
        return;
    }

    this->groups[currentIndex].clearSubgroups();

    // Получим виджет текущей вкладки
    QWidget *currentTabWidget = tabView->widget(currentIndex);
    std::unique_ptr<GroupingStrategy> groupingStrategy;

    QTreeView *treeView = nullptr;
    QString tabName = currentTabWidget->objectName();
    if(tabName == "distanceTab")
    {
        treeView = currentTabWidget->findChild<QTreeView*>("distanceTableView");

        // Ищем виджеты по именам "originXLineEdit" и "originYLineEdit"
        QWidget *foundOriginXWidget = currentTabWidget->findChild<QWidget*>("originXLineEdit");
        QWidget *foundOriginYWidget = currentTabWidget->findChild<QWidget*>("originYLineEdit");

        // Проверяем, найдены ли виджеты
        if (foundOriginXWidget && foundOriginYWidget)
        {
            // Преобразуем найденные виджеты в QLineEdit
            QLineEdit *originXLineEdit = qobject_cast<QLineEdit*>(foundOriginXWidget);
            QLineEdit *originYLineEdit = qobject_cast<QLineEdit*>(foundOriginYWidget);

            if (originXLineEdit && originYLineEdit)
            {
                // Получаем тексты из QLineEdit и преобразуем их в float
                bool ok;
                float startX = originXLineEdit->text().toFloat(&ok);
                float startY = originYLineEdit->text().toFloat(&ok);

                if (ok)
                {
                    groupingStrategy = std::make_unique<DistanceGroupingStrategy>(startX, startY);
                }
                else
                {
                    QMessageBox::warning(tabView, "Предупреждение", "Координаты должны быть числами.");
                    return;
                }
            }
        }
    }
    else if(tabName == "nameTab")
    {
        treeView = currentTabWidget->findChild<QTreeView*>("nameTableView");

        groupingStrategy = std::make_unique<NameGroupingStrategy>();
    }
    else if(tabName == "timeTab")
    {
        treeView = currentTabWidget->findChild<QTreeView*>("timeTableView");

        groupingStrategy = std::make_unique<DateGroupingStrategy>();
    }
    else if(tabName == "typeTab")
    {
        treeView = currentTabWidget->findChild<QTreeView*>("typeTableView");

        // Ищем виджеты по имени "minimumNumberOfTypeObjectsLineEdit"
        QWidget *foundLineEditWidget = currentTabWidget->findChild<QWidget*>("minimumNumberOfTypeObjectsLineEdit");

        // Проверяем, найден ли виджет
        if (foundLineEditWidget)
        {
            // Преобразуем найденные виджеты в QLineEdit
            QLineEdit *minimumNumberOfTypeObjectsLineEdit = qobject_cast<QLineEdit*>(foundLineEditWidget);

            if (minimumNumberOfTypeObjectsLineEdit)
            {
                // Получаем тексты из QLineEdit и преобразуем их в int
                bool ok;
                int minNum = minimumNumberOfTypeObjectsLineEdit->text().toInt(&ok);

                if (ok)
                {
                    groupingStrategy = std::make_unique<TypeGroupingStrategy>(minNum);
                }
                else
                {
                    QMessageBox::warning(tabView, "Предупреждение", "Количество объектов должно быть числом.");
                    return;
                }
            }
        }
    }

    groupingStrategy->groupObjects(objects, this->groups);

    if (treeView)
    {
        // Создаем модель данных
        QStandardItemModel *model = createGroupModel(this->groups[currentIndex]);

        treeView->setModel(model);

        treeView->update();
    }

}

QStandardItemModel *GroupView::createGroupModel(Group rootGroup)
{
    QStandardItemModel *model = new QStandardItemModel();

    // Устанавливаем заголовки для столбцов
    model->setHorizontalHeaderLabels(QStringList() << "Subgroup" << "Name" << "Coordinate X" << "Coordinate Y" << "Type" << "Create Date");

    // Добавляем подгруппы в модель
    for (auto& subgroupIdPair : rootGroup.getSubgroups())
    {
        Subgroup& subgroup = subgroupIdPair.second;
        QStandardItem *subgroupItem = new QStandardItem(subgroupIdPair.first.c_str());
        subgroupItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserTristate); // Устанавливаем флаги
        model->appendRow(subgroupItem);

        // Добавляем объекты в подгруппу
        for (const Object& object : subgroup.getObjects())
        {
            QStandardItem *subgroupColumn = new QStandardItem("");
            QStandardItem *nameItem = new QStandardItem(object.getName().c_str());
            QStandardItem *xItem = new QStandardItem(QString::number(object.getCoordinateX()));
            QStandardItem *yItem = new QStandardItem(QString::number(object.getCoordinateY()));
            QStandardItem *typeItem = new QStandardItem(object.getType().c_str());
            QStandardItem *dateItem = new QStandardItem(object.getDate().toString().toStdString().c_str());

            // Устанавливаем флаги только для чтения для каждого элемента
            subgroupColumn->setFlags(Qt::ItemIsEnabled);
            nameItem->setFlags(Qt::ItemIsEnabled);
            xItem->setFlags(Qt::ItemIsEnabled);
            yItem->setFlags(Qt::ItemIsEnabled);
            typeItem->setFlags(Qt::ItemIsEnabled);
            dateItem->setFlags(Qt::ItemIsEnabled);

            // Добавляем элементы в строку подгруппы
            QList<QStandardItem*> rowItems;
            rowItems << subgroupColumn << nameItem << xItem << yItem << typeItem << dateItem;
            subgroupItem->appendRow(rowItems);
        }
    }

    return model;
}
