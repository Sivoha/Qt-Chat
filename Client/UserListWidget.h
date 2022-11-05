#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>

class UserListWidget : public QListWidget {
    Q_OBJECT
public:
    UserListWidget(QWidget *parent = 0);
    ~UserListWidget();
protected:
    void mousePressEvent(QMouseEvent* event);
signals:
    void rightClick(QPoint pos);
};

#endif // USERLISTWIDGET_H
