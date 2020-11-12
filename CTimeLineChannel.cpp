#include "CTimeLineChannel.h"

CTimeLineChannel::CTimeLineChannel(const QString &indentifer, const QString &label, QObject *parent )
    : QObject( parent )
    , m_indentifer( indentifer )
    , m_label( label )
{

}

const QString &CTimeLineChannel::indentifer() const
{
    return m_indentifer;
}

void CTimeLineChannel::setIndentifer(const QString &indentifer)
{
    m_indentifer = indentifer;
}

const QString &CTimeLineChannel::label() const
{
    return m_label;
}

void CTimeLineChannel::setLabel(const QString &label)
{
    m_label = label;
}
