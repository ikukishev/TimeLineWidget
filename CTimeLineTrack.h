#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>



class CTimeLineTrack
        : public QObject
        , public QGraphicsItem
{
    Q_OBJECT
public:
    CTimeLineTrack(int _length, QColor _color, QObject* parent = nullptr );

    void SetLength(float _length) { length = _length; }

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor color;
    QColor outlineColor;
    int penWidth;
    int rounded;
    QBrush brush;
    QPen pen;
    int length,height;
    bool pressed=false;
    QPointF oldPos;
    QPointF oldMousePos;

};

