#include <UserListWidget.h>

UserListWidget::UserListWidget(QWidget *parent) : QListWidget(parent) {}

UserListWidget::~UserListWidget() {}

void UserListWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit rightClick(event);
    } else {
        QListWidget::mousePressEvent(event);
    }
}
