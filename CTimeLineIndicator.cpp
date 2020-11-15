#include "CTimeLineIndicator.h"
#include <QGraphicsScene>

constexpr qreal cIndicatorSize = 7;

CTimeLineIndicator::CTimeLineIndicator(float height):QGraphicsItem ()
{
    pen = QPen(Qt::darkMagenta,1);
    brush = QBrush(Qt::RoundCap);
    brush.setColor(QColor("#50f"));
    points<<QPointF(-cIndicatorSize,0)
         <<QPointF(0,cIndicatorSize)
        <<QPointF(cIndicatorSize,0)
       <<QPointF(cIndicatorSize,-cIndicatorSize)
      <<QPointF(-cIndicatorSize,-cIndicatorSize);
    setHeight(height);
   setAcceptHoverEvents(true);
   this->setAcceptDrops(true);

   setFlag(QGraphicsItem::ItemIsMovable);
   setFlag(QGraphicsItem::ItemIsFocusable);
   setFlag(ItemSendsGeometryChanges);
}

QSizeF CTimeLineIndicator::calculateSize()const
{
    float minX = points[0].x();
    float minY = points[0].y();
    float maxX = points[0].x();
    float maxY = points[0].y();
    for(QPointF point : points){
        if (point.x() < minX){
            minX = point.x();
        }
        if (point.y() < minY){
            minY = point.y();
        }
        if (point.x() > maxX){
            maxX = point.x();
        }
        if (point.y() > maxY){
            maxY = point.y();
        }
    }
    return QSizeF(maxX-minX,line.p2().y());
}

ITimeLineTrackView *CTimeLineIndicator::TimeLinePtr() const
{
   return m_TimeLinePtr;
}

void CTimeLineIndicator::setTimeLinePtr(ITimeLineTrackView *TimeLinePtr)
{
   m_TimeLinePtr = TimeLinePtr;
}

QRectF CTimeLineIndicator::boundingRect() const
{
   QSizeF size = this->calculateSize();
   return QRectF(-5,-5,size.width(),size.height());
}

void CTimeLineIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setPen(pen);
    painter->drawLine(line);
    painter->setBrush(brush);
    //painter->translate(-boundingRect().width()/2,0);
    painter->drawPolygon(points);
    //painter->translate(boundingRect().width()/2,0);
//    QBrush b(Qt::red);
//    painter->setBrush(b);
//    painter->drawRect(boundingRect());
}

void CTimeLineIndicator::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        pressed = true;
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        pressed = false;
    }

    QGraphicsItem::mousePressEvent(event);
    update();
}

void CTimeLineIndicator::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    if(pressed){
        this->setPos(pos.x(),y());
    }
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void CTimeLineIndicator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    qDebug()<<event->scenePos();
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void CTimeLineIndicator::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//qDebug()<<"hover enter";


   QGraphicsItem::hoverEnterEvent(event);
}

void CTimeLineIndicator::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//qDebug()<<"hover move";

//    if(pressed){

//        QPointF pos = event->scenePos();
//        qDebug()<<pos;
//        this->setPos(pos.x(),y());
//    }
   QGraphicsItem::hoverMoveEvent(event);
}

void CTimeLineIndicator::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//qDebug()<<"hover leave";
    //    pressed=false;
   QGraphicsItem::hoverLeaveEvent(event);
}

QVariant CTimeLineIndicator::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if ( change == ItemPositionChange && scene() )
    {
        // value is the new position.
        QPointF newPos = value.toPointF();
        newPos.setY(y());
        if( newPos.x() < 0 || nullptr == m_TimeLinePtr )
        {
            newPos.setX(0);
        }
        else
        {
           auto rightPosLimit = scene()->width() - m_TimeLinePtr->channelLabelWidth() - cFieldMargin;
           if ( newPos.x() > rightPosLimit )
           {
              newPos.setX( rightPosLimit );
           }
        }
//        newPos = qBound(QPointF(0,0),newPos,QPointF(10000,0));
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
