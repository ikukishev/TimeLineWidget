#include <QGraphicsScene>
#include <QMouseEvent>

#include <QDebug>

#include "CTimeLineView.h"
#include "CTimeLineIndicator.h"
#include "CTimeLineTrack.h"


CTimeLineView::CTimeLineView( QWidget *parent )
    : QGraphicsView( new QGraphicsScene( ), parent )
{

    setMouseTracking(true);
    int xOffset = 100;
    for( int i =0; i < 10; i++ )
    {
        QGraphicsItem *item = scene()->addText(QString::number(i));
        item->setPos(i*xOffset,-40);
    }

    indicator = new CTimeLineIndicator( 2000 );
    CTimeLineTrack *track = new CTimeLineTrack( 200, QColor(Qt::cyan) );
    track->setParentItem( indicator );

    indicator->setZValue(101);
    track->setPos( QPointF(300,0) );

    scene()->addItem(indicator);
}

void CTimeLineView::mousePressEvent(QMouseEvent *event)
{
    if ( !itemAt( event->pos() ) )
    {
        qDebug() << "Press";
    }
    else
    {
        auto item = this->scene()->itemAt( event->pos(), QTransform() );
    }

    QGraphicsView::mousePressEvent( event );
}

void CTimeLineView::mouseMoveEvent( QMouseEvent *event )
{
    /// WORKS!!!!!!!!!!
    // auto item = this->scene()->itemAt( event->pos(), QTransform() );
    qDebug() << "indicator.items.count: " << indicator->childItems().count();

    QGraphicsView::mouseMoveEvent(event);
}

void CTimeLineView::AddItem(QPointF pos, QRect rect, QPen pen, QBrush brush)
{
    QGraphicsItem *item = scene()->addRect(rect,pen,brush);
    item->setPos(pos);
}

void CTimeLineView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void CTimeLineView::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"CLCLLCLC";
    QGraphicsView::keyPressEvent(event);
}

void CTimeLineView::drawBackground(QPainter *painter, const QRectF &rect)
{

}
