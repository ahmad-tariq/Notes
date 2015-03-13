#include "notestablemanager.h"

NotesTableManager *NotesTableManager::instance = NULL;

NotesTableManager *NotesTableManager::getInstance()
{
    if (!instance)
        instance = new NotesTableManager();
    return instance;
}

NotesTableManager *NotesTableManager::getInstance(QList< QPair<QString, QString> > pairs)
{
    if (!instance)
        instance = new NotesTableManager(pairs);
    return instance;
}

NotesTableManager::NotesTableManager(QObject *parent) :
    QAbstractTableModel(parent)
{

}

 NotesTableManager::NotesTableManager(QList< QPair<QString, QString> > pairs, QObject *parent)
     : QAbstractTableModel(parent)
 {
     listOfPairs = pairs;
 }

 int NotesTableManager::rowCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return listOfPairs.size();
 }

 int NotesTableManager::columnCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return 2;
 }

 QVariant NotesTableManager::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= listOfPairs.size() || index.row() < 0)
         return QVariant();

     if (role == Qt::DisplayRole) {
         QPair<QString, QString> pair = listOfPairs.at(index.row());
         if (index.column() == 0)
             return pair.first;
         else if (index.column() == 1)
             return pair.second;
     }
     return QVariant();
 }

 QVariant NotesTableManager::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
             case 0:
                 return tr("Date");

             case 1:
                 return tr("Description");

             default:
                 return QVariant();
         }
     }
     return QVariant();
 }

 bool NotesTableManager::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; row++) {
         QPair<QString, QString> pair(" ", " ");
         listOfPairs.insert(position, pair);
     }

     endInsertRows();
     return true;
 }

 bool NotesTableManager::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         listOfPairs.removeAt(position);
     }

     endRemoveRows();
     return true;
 }

 bool NotesTableManager::setData(const QModelIndex &index, const QVariant &value, int role)
 {
     if (index.isValid() && role == Qt::EditRole) {
         int row = index.row();

         QPair<QString, QString> p = listOfPairs.value(row);

         if (index.column() == 0)
             p.first = value.toString();
         else if (index.column() == 1)
             p.second = value.toString();
         else
             return false;

         listOfPairs.replace(row, p);
         emit(dataChanged(index, index));

         return true;
     }

     return false;
 }

 Qt::ItemFlags NotesTableManager::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return QAbstractTableModel::flags(index);
 }

 QList< QPair<QString, QString> > NotesTableManager::getList()
 {
     return listOfPairs;
 }
