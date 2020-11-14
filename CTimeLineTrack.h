#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "ITimeLineTrackViev.h"



class CTimeLineTrack
        : public QObject
        , public ITrack
{
    Q_OBJECT
public:
    CTimeLineTrack( ITimeLineChannel *channel,
                    uint64_t position,
                    QObject* parent = nullptr );

    class TrackFactory: public ITrackFactory
    {
    public:
       // ITrackFactory interface
    public:
       const QString &menuLabel() const;
       ITrack *create(ITimeLineChannel *parent, u_int64_t position);

       static TrackFactory factory;
    };

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void updatePosition();
    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool pressedForMove=false;
    bool pressedForChangeDuration=false;
    QPointF oldPos;
    QPointF oldMousePos;

};

