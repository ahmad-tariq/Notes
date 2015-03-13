#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>

/*! Class for handling dialog.
 */

class NoteDialog : public QDialog
{
    Q_OBJECT
public:
    //! constructor
    NoteDialog(QWidget *parent = 0);

    //! Destructor
    ~NoteDialog();

public slots:
    //! sets and shows values in dialog.
    void show();

private slots:
    //! dialog has been accepted.
    void accept();

    //! dialog has been rejected.
    void reject();

public:
    QTextEdit *noteText;

private:
    QLabel *noteLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // NOTEDIALOG_H
