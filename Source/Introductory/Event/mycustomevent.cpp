#include "mycustomevent.h"

MyCustomEvent::MyCustomEvent(const QVariant& data)
    : QEvent(static_cast<QEvent::Type>(Type)), m_data(data)
{
}

MyCustomEvent::~MyCustomEvent()
= default;

QVariant MyCustomEvent::getData() const
{
    return m_data;
}