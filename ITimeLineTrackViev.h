#ifndef CTIMELINEVIEW_H
#define CTIMELINEVIEW_H

#include <memory>
#include <QPoint>

#include <QGraphicsItem>
#include <QString>

constexpr int cFieldMargin = 10;

class ITimeLineChannel;
class ITimeLineTrackView;

class ITimeLineChannel: public QGraphicsItem
{
public:
   ITimeLineChannel() = default;
   virtual ~ITimeLineChannel() = default;

   virtual QColor color() const = 0;
   virtual ITimeLineTrackView* timeLinePtr() const = 0;
};

class ITrack: public QGraphicsItem
{
public:

   ITrack() = default;

   const QString& effectNameLabel() const {  return m_effectNameLabel;  }
   int64_t effectDuration() const {  return m_effectDuration;  }
   int64_t effectStartPosition() const {  return m_effectStartPosition;  }

protected:
   void setEffectNameLabel(const QString &ef) {  m_effectNameLabel = ef;  }
   void setEffectDuration(const int64_t &eD)  {  m_effectDuration = eD;  }
   void setEffectStartPosition(const int64_t &SP)  {  m_effectStartPosition = SP;  }

private:

   QString m_effectNameLabel;
   int64_t m_effectDuration;
   int64_t m_effectStartPosition;
};


class ITrackFactory
{
public:
   ITrackFactory();
   virtual ~ITrackFactory() = default;

   virtual const QString& menuLabel() const = 0;

   virtual ITrack* create(ITimeLineChannel* parent, u_int64_t position) = 0;

   static const std::list<ITrackFactory *> &trackFactories();

private:
   static std::list<ITrackFactory *> &initTrackFactories();
   static std::shared_ptr<std::list< ITrackFactory* >> sTrackFactories;

};


class ITimeLineTrackView
{
public:
   ITimeLineTrackView() = default;
   virtual ~ITimeLineTrackView() = default;

   virtual uint32_t channelHeight() const = 0;
   virtual uint64_t channelLabelWidth() const = 0;

   virtual int64_t compositionPosition() const = 0;
   virtual int64_t compositionDuration() const = 0;

   virtual qreal    convertPositionToSceneX() const = 0;
   virtual qreal    convertPositionToSceneX( int64_t position ) const = 0;
   virtual int64_t convertSceneXToPosition( qreal x ) const = 0;

   virtual ITimeLineChannel* getNeiborChannel( ITimeLineChannel* channel, int offsetIndex ) const = 0;

};


using TimeLineTrackVievPtr = std::shared_ptr<ITimeLineTrackView>;

#endif
