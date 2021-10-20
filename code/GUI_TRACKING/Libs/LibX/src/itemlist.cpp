#include "itemlist.h"
#include "itemmodel.h"
#include <QQmlContext>

ItemList::ItemList(QObject *parent) : QAbstractListModel(parent) {
  model = new ItemModel{this};
}

void ItemList::register_objects(const QString &assetName, const QString &nodeName, QQmlContext *context) {
  context->setContextProperty(assetName, this);
  context->setContextProperty(nodeName, model);
}

bool ItemList::addAsset(QGeoCoordinate coord, int angle, const QString &name) {
  auto item = std::find_if(m_assets.begin(), m_assets.end(),[&](Item const &obj) { return obj.getname() == name; });
  if (item != m_assets.end()) {
    int row = item - m_assets.begin();
    QModelIndex ix = index(row);
    QGeoCoordinate c = ix.data(AssetRole).value<QGeoCoordinate>();
    float a = ix.data(AngleRole).toInt();
    Data data{coord, angle};
    bool result = setData(ix, QVariant::fromValue(data), AssetRole);
    if (result)
      model->appendNode(c, a);
    return result;
  }
  return false;
}

bool ItemList::createAsset(QGeoCoordinate coord, const QString &name) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  Item item;
  item.setName(name);
  item.setAsset(coord);
  item.setAngle(0);
  m_assets << item;
  endInsertRows();
  return true;
}

int ItemList::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_assets.count();
}

QVariant ItemList::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() >= 0 && index.row() < rowCount()) {
    const Item &item = m_assets[index.row()];
    if (role == NameRole)
      return item.getname();
    else if (role == AssetRole)
      return QVariant::fromValue(item.getAsset());
    else if (role == AngleRole) {
      return item.getAngle();
    }
  }
  return QVariant();
}

QHash<int, QByteArray> ItemList::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "nameData";
  roles[AssetRole] = "assetData";
  roles[AngleRole] = "angleData";
  return roles;
}

bool ItemList::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (!index.isValid())
    return false;
  if (index.row() >= 0 && index.row() < rowCount()) {
    if (role == AssetRole) {
      const Data &data = value.value<Data>();
      QGeoCoordinate new_asset(data.coord);
      m_assets[index.row()].setAsset(new_asset);
      m_assets[index.row()].setAngle(data.angle);
      emit dataChanged(index, index, QVector<int>{AssetRole});
      return true;
    }
  }
  return false;
}
