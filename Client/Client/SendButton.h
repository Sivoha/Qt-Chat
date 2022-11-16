#ifndef SENDBUTTON_H
#define SENDBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>

class SendButton : public QPushButton {
    Q_OBJECT
public:
    explicit SendButton(QWidget *parent = nullptr);
     ~SendButton();
protected:
    void mousePressEvent(QMouseEvent* event);
signals:
    void rightClick(QMouseEvent*);
};

#endif // SENDBUTTON_H
