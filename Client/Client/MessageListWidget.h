#ifndef MESSAGELISTWIDGET_H
#define MESSAGELISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QTime>

typedef struct {
    QString messageTime;
    QString senderIP;
    QString senderName;
    QString messageText;
} Message;

class MessageListWidget : public QListWidget {
    Q_OBJECT
public:
    MessageListWidget(QWidget *parent = 0);
    ~MessageListWidget();
protected:
    void mousePressEvent(QMouseEvent* event);
signals:
    void rightClickOnMessage(QMouseEvent* event);
};

#endif // MESSAGELISTWIDGET_H
