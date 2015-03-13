
#include <QGridLayout>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QMessageBox>
#include "notestablemanager.h"
#include "notesview.h"
#include "notedialog.h"
#include <QDebug>

const QString FILE_NAME("/notes.dat");

NotesView::NotesView(QWidget *parent) :
    QTableView(parent)
{
    instance = NotesTableManager::getInstance();

    addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNoteEntry()));

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openNoteEntry(QModelIndex)));

    removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeNoteEntry()));

    exitButton = new QPushButton("Exit");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitApplication()));

    QGridLayout *layout = new QGridLayout();
    layout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    layout->addWidget(addButton,0,0);
    layout->addWidget(removeButton,0,2);
    layout->addWidget(exitButton,0,3);

    readNotesFromFile();
    updateButtons();

    setLayout(layout);
}

void NotesView::updateButtons()
{
    if ( instance->getList().size() > 0 )
    {
        removeButton->setEnabled(true);
    } else {
        removeButton->setDisabled(true);
    }
}

void NotesView::exitApplication()
{
    this->close();
}

void NotesView::addNoteEntry()
{
    NoteDialog noteDialog;
    noteDialog.setWindowTitle(tr("Add a Note"));

     if (noteDialog.exec()) {
         QDate *date = new QDate(QDate::currentDate());
         QString noteDate = date->toString(Qt::SystemLocaleShortDate);
         QString noteText = noteDialog.noteText->toPlainText();
         if ( !noteText.isEmpty()) {
             addNoteEntry(noteDate, noteText);
         }
     }

     updateButtons();
}

void NotesView::addNoteEntry(QString noteDate, QString noteText)
{
    instance->insertRows(0, 1, QModelIndex());
    QModelIndex index = instance->index(0, 0, QModelIndex());
    instance->setData(index, noteDate, Qt::EditRole);
    index = instance->index(0, 1, QModelIndex());
    instance->setData(index, noteText, Qt::EditRole);    
    selectRow(index.row());
    if ( instance->getList().size() == 1) {
        resizeColumnToContents(0);
    }
    writeNotesToFile();
}

void NotesView::openNoteEntry(QModelIndex index)
{
    NoteDialog noteDialog;
    noteDialog.setWindowTitle(tr("View/Edit a Note"));

    QString text;
    int row = index.row();

    index = instance->index(row, 1, QModelIndex());
    QVariant noteText = instance->data(index, Qt::DisplayRole);
    text = noteText.toString();

    noteDialog.noteText->setText(text);

    if (noteDialog.exec()) {
        QDate *date = new QDate(QDate::currentDate());
        QString newDate = date->toString(Qt::SystemLocaleShortDate);
        QString newText = noteDialog.noteText->toPlainText();
        if ( !newText.isEmpty()) {
            if (QString::compare(text, newText, Qt::CaseSensitive)) {
                index = instance->index(row, 0, QModelIndex());
                instance->setData(index, newDate, Qt::EditRole);
                index = instance->index(row, 1, QModelIndex());
                instance->setData(index, newText, Qt::EditRole);
            }
        } else {
            removeNoteEntry();
        }
    }

}

void NotesView::removeNoteEntry()
{
    QModelIndex index = currentIndex();
    int row = index.row();
    instance->removeRows(row, 1, QModelIndex());
    updateButtons();
    writeNotesToFile();
}

void NotesView::readNotesFromFile()
{
    QFile file(FILE_NAME);

    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, tr("Error opening file"),
            file.errorString());
        return;
    }

    QList< QPair<QString, QString> > pairs = instance->getList();
    QDataStream in(&file);
    in >> pairs;

    if (!pairs.isEmpty()) {
        for (int i=0; i<pairs.size(); ++i) {
            QPair<QString, QString> p = pairs.at(i);
            addNoteEntry(p.first, p.second);
        }
    }
}


void NotesView::writeNotesToFile()
{
    QFile file(FILE_NAME);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error opening file"), file.errorString());
        return;
    }

    QList< QPair<QString, QString> > pairs = instance->getList();
    QDataStream out(&file);
    out << pairs;
}
