#ifndef NOTESTABLEMANAGER_H
#define NOTESTABLEMANAGER_H

#include <QAbstractTableModel>
#include <QPair>
#include <QList>

/*! Class for handling table operations.
 */

class NotesTableManager : public QAbstractTableModel
{
    Q_OBJECT
public:
    static NotesTableManager *getInstance();
    static NotesTableManager *getInstance(QList< QPair<QString, QString> > pairs);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    QList< QPair<QString, QString> > getList();

private:
    NotesTableManager(QObject *parent = 0);
    NotesTableManager(QList< QPair<QString, QString> > pairs, QObject *parent = 0);

private:
    static NotesTableManager *instance;
    QList< QPair<QString, QString> > listOfPairs;
};

#endif // NOTESTABLEMANAGER_H
