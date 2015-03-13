#ifndef NOTESVIEW_H
#define NOTESVIEW_H

#include <QTableView>
#include <QPushButton>
#include "notestablemanager.h"

/*! view class for notes application
 *
 */

class NotesView : public QTableView
{
    Q_OBJECT
public:
    NotesView(QWidget *parent = 0);

    /*! Updates the enabled/disabled state of buttons.
     */
    void updateButtons();

private slots:

    /*! Add a note entry
     */
    void addNoteEntry();

    /*! Open a note entry
     * @param index Index of the note
     */
    void openNoteEntry(QModelIndex index);

    /*! Remove a note entry
     */
    void removeNoteEntry();

    /*! Exit appliaction
     */
    void exitApplication();

private:

    /*! Add a note entry called by addNoteEntry() slot
     *
     * @param noteDate Date of the note
     * @param noteText Text of the note
     */
    void addNoteEntry(QString noteDate, QString noteText);

    /*! Reading notes from a file
     */
    void readNotesFromFile();

    /*! Writing notes to a file
     */
    void writeNotesToFile();

private:
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *exitButton;
    NotesTableManager *instance;
};

#endif // NOTESVIEW_H
