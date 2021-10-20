#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "item.h"
#include <QAbstractListModel>

class ItemModel;
class QQmlContext;

struct Data {
  QGeoCoordinate coord;
  int angle;
};
Q_DECLARE_METATYPE(Data)

class ItemList : public QAbstractListModel {
  Q_OBJECT

public:
  explicit ItemList(QObject *parent = nullptr);
  enum Roles {
    NameRole = Qt::UserRole + 1,
    AssetRole,
    AngleRole
  };
  void register_objects(const QString &assetName, const QString &nodeName, QQmlContext *context);

  //Q_INVOKABLE bool addAsset(QGeoCoordinate coord, const QString &name);
  Q_INVOKABLE bool addAsset(QGeoCoordinate coord, int angle, const QString &name);
  Q_INVOKABLE bool createAsset(QGeoCoordinate coord, const QString &name);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
  QList<Item> m_assets;
  ItemModel *model;
};

#endif // ITEMLIST_H
