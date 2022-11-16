#include <MessageListWidget.h>

MessageListWidget::MessageListWidget(QWidget *parent) : QListWidget(parent) {}

MessageListWidget::~MessageListWidget() {}

void MessageListWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit rightClickOnMessage(event);
    } else {
        QListWidget::mousePressEvent(event);
    }
}
