#include "CTimeLineTrack.h"
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>

constexpr int64_t cDefaultDuration = 5000;
constexpr int64_t cMinimumDuration = 200;

CTimeLineTrack::CTimeLineTrack( ITimeLineChannel* channel, uint64_t position, QObject* parent )
    : QObject( parent )
    , oldPos( scenePos() )
{
    setEffectStartPosition( position );
    setEffectDuration( cDefaultDuration );
    setParentItem(channel);
    setEffectNameLabel( "base" );
    updatePosition();
}

QRectF CTimeLineTrack::boundingRect() const
{

   ITimeLineChannel* channel = dynamic_cast<ITimeLineChannel*>( parentItem() );

   assert( nullptr != channel );

   QRectF rect ( 0, 0, channel->timeLinePtr()->convertPositionToSceneX( effectDuration() ), channel->timeLinePtr()->channelHeight() );
   return rect;
}

void CTimeLineTrack::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    Q_UNUSED(widget);

    ITimeLineChannel* channel = dynamic_cast<ITimeLineChannel*>( parentItem() );
    if ( nullptr != channel )
    {
       updatePosition();

       painter->setBrush( channel->color() );
       QPen pen;
       pen.setWidth(1);
       if ( pressedForChangeDuration || pressedForMove )
       {
         pen.setColor( ~channel->color().rgb() );
       }
       painter->setPen(pen);

       painter->drawRect(boundingRect());
       QFont font = scene()->font();
       QFontMetricsF fontMetrics(font);
       int heightFont = fontMetrics.boundingRect( effectNameLabel() ).height();
       painter->drawText(0,heightFont,effectNameLabel());

    }
}


QVariant CTimeLineTrack::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange )
    {
        // value is the new position.
        QPointF newPos = value.toPointF();
        //newPos.setY(y());
        if(newPos.x() < 0)
        {
            newPos.setX(0);
        }

        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void CTimeLineTrack::updatePosition()
{
      ITimeLineChannel* channel = dynamic_cast<ITimeLineChannel*>( parentItem() );
      assert( nullptr != channel );
      setX( channel->timeLinePtr()->channelLabelWidth() + channel->timeLinePtr()->convertPositionToSceneX( effectStartPosition() ));
}


void CTimeLineTrack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   oldMousePos = event->pos();
   oldPos = event->pos();

   if ( 4>(boundingRect().width() - event->pos().x())  )
   {
      pressedForChangeDuration = true;
      pressedForMove = false;

      auto cur = this->cursor();
      cur.setShape( Qt::SizeHorCursor );
      this->setCursor(cur);
   }
   else
   {
      pressedForMove = true;
      pressedForChangeDuration = false;

      auto cur = this->cursor();
      cur.setShape( Qt::DragMoveCursor );
      this->setCursor(cur);
   }

}

void CTimeLineTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   QPointF newPos = event->pos();
    if ( pressedForMove )
    {
        ITimeLineChannel* channel = dynamic_cast<ITimeLineChannel*>( parentItem() );
        assert( nullptr != channel );

        int yDiff = newPos.y() - oldPos.y();

        int heightDiff= channel->timeLinePtr()->channelHeight() / 2;

        if (abs(yDiff) > heightDiff )
        {
           int offset = yDiff / heightDiff;
           auto newParent = channel->timeLinePtr()->getNeiborChannel( channel, offset );
           if ( nullptr != newParent )
           {
              parentItem()->update( parentItem()->boundingRect());
              setParentItem(newParent);
           }
        }

        int dx = newPos.x() - oldMousePos.x();
        auto realTrekPos = pos().x() - channel->timeLinePtr()->channelLabelWidth() + dx;
        if ( realTrekPos > 0 )
        {
           auto newPosition = channel->timeLinePtr()->convertSceneXToPosition( realTrekPos  );
           if ( newPosition + effectDuration() < channel->timeLinePtr()->compositionDuration() && newPosition > 0 )
           {
              setEffectStartPosition(  newPosition );
           }
        }

        updatePosition();
        parentItem()->update( parentItem()->boundingRect());
    }
    else if ( pressedForChangeDuration )
    {

       ITimeLineChannel* channel = dynamic_cast<ITimeLineChannel*>( parentItem() );
       assert( nullptr != channel );

       int dx = newPos.x() - oldMousePos.x();

       auto posDx = channel->timeLinePtr()->convertSceneXToPosition( dx );

       auto newDuration = effectDuration()+posDx;
       if ( newDuration > cMinimumDuration
            && ( channel->timeLinePtr()->compositionDuration() >  effectStartPosition() + newDuration ) )
       {
          setEffectDuration( newDuration );
       }
       oldMousePos = newPos;
       parentItem()->update( parentItem()->boundingRect());
    }
}

void CTimeLineTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressedForMove = false;
    pressedForChangeDuration = false;
    oldMousePos = event->pos();
    oldPos = event->pos();

    auto cur = this->cursor();
    cur.setShape( Qt::ArrowCursor );
    this->setCursor(cur);
}

void CTimeLineTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Double Click";
}


CTimeLineTrack::TrackFactory CTimeLineTrack::TrackFactory::factory;

const QString &CTimeLineTrack::TrackFactory::menuLabel() const
{
   static QString label("test");
   return label;
}

ITrack *CTimeLineTrack::TrackFactory::create(ITimeLineChannel *parent, u_int64_t position)
{
   return new CTimeLineTrack( parent, position );
}
