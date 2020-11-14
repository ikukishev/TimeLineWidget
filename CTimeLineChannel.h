#ifndef CTIMELINECHANNEL_H
#define CTIMELINECHANNEL_H

#include <QObject>
#include <QString>
#include <QColor>
#include "ITimeLineTrackViev.h"

class CTimeLineChannel
      : public QObject
      , public ITimeLineChannel
{
    Q_OBJECT
public:
    CTimeLineChannel( const QString& indentifer, const QString& label, QObject* parent = nullptr );


    const QString& indentifer() const { return m_indentifer; }
    void setIndentifer(const QString &indentifer) { m_indentifer = indentifer; }

    const QString& label() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; }

    void setTimeLinePtr( ITimeLineTrackView* ptr ) { m_TimeLinePtr = ptr; }
    void setColor( const QColor& color) { m_labelColor = color; }

    // ITimeLineChannel interface
    ITimeLineTrackView* timeLinePtr( ) const override { return m_TimeLinePtr; }
    virtual QColor color() const override;

    void updateChannelGraphics();

    // QGraphicsItem interface

signals:
    void effectsSetChanged( CTimeLineChannel* tlChannel );

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

protected:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QString m_indentifer;
    QString m_label;
    QColor  m_labelColor;

    ITimeLineTrackView* m_TimeLinePtr = nullptr;

};

#endif // CTIMELINECHANNEL_H
