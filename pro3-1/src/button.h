/*#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Button(QPixmap name, QGraphicsItem * parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H*/
