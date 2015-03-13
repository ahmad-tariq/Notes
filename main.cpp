
#include <QApplication>
#include <QHeaderView>
#include "notestablemanager.h"
#include "notesview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QList< QPair<QString, QString> > pairs;
    NotesTableManager *model = NotesTableManager::getInstance(pairs);

    NotesView *view = new NotesView();
    view->setModel(model);

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    if ( model->getList().size() > 0 )
    {
        view->selectRow(0);
        view->resizeColumnToContents(0);
    }
    QHeaderView *headerView = view->horizontalHeader();
    headerView->setStretchLastSection(true);    

#if defined(Q_OS_SYMBIAN)
    view->showMaximized();
#else
    view->show();
#endif
    return app.exec();
}
