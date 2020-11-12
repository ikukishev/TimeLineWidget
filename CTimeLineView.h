#pragma once

#include <QGraphicsView>

#include <QGraphicsItem>

class CTimeLineIndicator;

class CTimeLineView: public QGraphicsView
{
    Q_OBJECT
public:
    CTimeLineView(QWidget *parent = nullptr);
    
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    void AddItem(QPointF pos, QRect rect, QPen pen, QBrush brush);

signals:
    void sendMousePressEventSignal(QMouseEvent *event);
    void sendMouseMoveEventSignal(QMouseEvent *event);
    void sendMouseReleaseEventSignal(QMouseEvent *event);

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

    // QGraphicsView interface
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    CTimeLineIndicator* indicator;
};
