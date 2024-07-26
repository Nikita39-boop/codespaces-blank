#ifndef GROUPVIEW_H
#define GROUPVIEW_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QStandardItemModel>
#include "Group.h"

class GroupView : public QObject
{
    Q_OBJECT

public:
    GroupView(QTabWidget *tabView, QObject *parent = nullptr);

    void updateViewWithObjects(const std::vector<Object> &objects);
    QStandardItemModel* createGroupModel(Group rootGroup);

private:
    std::vector<Group> groups;
    QTabWidget *tabView;
};

#endif // GROUPVIEW_H
