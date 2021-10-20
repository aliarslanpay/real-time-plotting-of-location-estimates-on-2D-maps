#ifndef ITEM_H
#define ITEM_H

#include <QGeoCoordinate>
#include <QString>

class Item {
public:
  QString getname() const;
  void setName(const QString &name);
  QGeoCoordinate getAsset() const;
  void setAsset(const QGeoCoordinate &asset);
  int getAngle() const;
  void setAngle(int angle);

private:
  QString m_name;
  QGeoCoordinate m_asset;
  int m_angle;
};

#endif // ITEM_H
