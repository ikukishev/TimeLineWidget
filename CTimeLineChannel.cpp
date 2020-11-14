#include "CTimeLineChannel.h"
#include <QGraphicsScene>
#include <QPen>
#include <QPainter>
#include <QLine>
#include <QDebug>

CTimeLineChannel::CTimeLineChannel(const QString &indentifer, const QString &label, QObject *parent )
    : QObject( parent )
    , m_indentifer( indentifer )
    , m_label( label )
{
   setCacheMode( NoCache );
}

QRectF CTimeLineChannel::boundingRect() const
{
    return QRectF(0,0, scene()->width( ), m_TimeLinePtr? m_TimeLinePtr->channelHeight() : 20);
}

void CTimeLineChannel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   if ( m_TimeLinePtr )
   {
      QPen pen;
      pen.setColor( QColorConstants::Gray );
      pen.setWidth(1);
      painter->setPen( pen );

      painter->drawRect( 0, 0, scene()->width()-cFieldMargin, m_TimeLinePtr->channelHeight() );

      painter->setBrush( QBrush( m_labelColor ) );

      painter->drawRect( 0, 0, m_TimeLinePtr->channelLabelWidth() - cFieldMargin, m_TimeLinePtr->channelHeight() );

      QFont font = scene()->font();
      QFontMetricsF fontMetrics( font );

      pen.setColor( ~m_labelColor.rgb() );
      painter->setPen( pen );

      int heightFont = fontMetrics.boundingRect( m_label ).height();
      painter->drawText( 5, m_TimeLinePtr->channelHeight()/2 + heightFont/2, m_label );

      for ( auto item : childItems())
      {
         item->update(item->boundingRect());
      }

   }
}

QColor CTimeLineChannel::color() const
{
   return m_labelColor;
}

void CTimeLineChannel::updateChannelGraphics()
{
   update(boundingRect());
}

QVariant CTimeLineChannel::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
   switch ( change )
   {
      case QGraphicsItem::ItemChildAddedChange:
      case QGraphicsItem::ItemChildRemovedChange:
         emit effectsSetChanged( this );
         break;
   }

   return ITimeLineChannel::itemChange( change, value);
}
