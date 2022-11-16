#include "SendButton.h"

SendButton::SendButton(QWidget *parent) : QPushButton(parent) {}

SendButton::~SendButton() {}

void SendButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit rightClick(event);
    } else {
        QPushButton::mousePressEvent(event);
    }
}
