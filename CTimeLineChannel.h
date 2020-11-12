#ifndef CTIMELINECHANNEL_H
#define CTIMELINECHANNEL_H

#include <QObject>
#include <QString>
#include <QGraphicsItem>

class CTimeLineChannel
        : public QObject
        , public QGraphicsItem
{
    Q_OBJECT
public:
    CTimeLineChannel( const QString& indentifer, const QString& label, QObject* parent = nullptr );


    const QString& indentifer() const;
    void setIndentifer(const QString &indentifer);

    const QString& label() const;
    void setLabel(const QString &label);

private:
    QString m_indentifer;
    QString m_label;

};

#endif // CTIMELINECHANNEL_H
