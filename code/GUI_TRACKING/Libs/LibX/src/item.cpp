#include "item.h"

QString Item::getname() const {
    return m_name;
}
void Item::setName(const QString &name) {
    m_name = name;
}
QGeoCoordinate Item::getAsset() const {
    return m_asset;
}
void Item::setAsset(const QGeoCoordinate &asset) {
    m_asset = asset;
}
int Item::getAngle() const {
    return m_angle;
}
void Item::setAngle(int angle) {
    m_angle = angle;
}
