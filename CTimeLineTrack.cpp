#include "CTimeLineTrack.h"
#include <QDebug>
#include <QGraphicsScene>

CTimeLineTrack::CTimeLineTrack(int _length, QColor _color, QObject* parent)
    : QObject( parent )
    , QGraphicsItem()
    , color( _color )
    , outlineColor( color.lighter(30) )
    , penWidth( 2 )
    , rounded( 0 )
    , brush( color )
    , pen( outlineColor, penWidth )
    , length( _length )
    , height( 30 )
    , oldPos( scenePos() )
{
    setFlags(ItemIsMovable);
    pen.setCapStyle(Qt::RoundCap);
}

QRectF CTimeLineTrack::boundingRect() const
{
    return QRectF(0,0,length,height);
}

void CTimeLineTrack::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRoundedRect(boundingRect(),rounded,rounded);
    painter->setBrush(outlineColor);
    QFont font = scene()->font();
    QFontMetricsF fontMetrics(font);
    QString text("tReplaySong1");
    int heightFont = fontMetrics.boundingRect(text).height();
    painter->drawText(0,heightFont,text);

}


QVariant CTimeLineTrack::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange )
    {
        // value is the new position.
        QPointF newPos = value.toPointF();
        newPos.setY(y());
        if(newPos.x() < 0){
            newPos.setX(0);
        }

        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}


void CTimeLineTrack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Press";
    pressed = true;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
}

void CTimeLineTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Move";

    if ( pressed )
    {
        QPointF newPos = event->scenePos();
        qDebug()<<newPos;
        int yDiff = newPos.y() - oldPos.y();
        qDebug()<<abs(yDiff);
        int heightDiff=15;
        if (abs(yDiff) > heightDiff )
        {
            heightDiff*=2;
            heightDiff+=5;
            int d = (int)(yDiff%heightDiff);
            newPos.setY(oldPos.y()+(int)(yDiff/heightDiff)*heightDiff);
            setY(newPos.y());
        }
        else
        {
            setY(oldPos.y());
        }

        int dx = (newPos - oldMousePos).x();
        setX(oldPos.x()+dx);
    }
}
void CTimeLineTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Release";
    pressed = false;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
}
void CTimeLineTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Double Click";
}
