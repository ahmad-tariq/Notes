
#include <QGridLayout>
#include "notedialog.h"

NoteDialog::NoteDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Add a Note"));

    noteLabel = new QLabel("Note");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    noteText = new QTextEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    //! adding lable and text fields to layout
    gLayout->addWidget(noteLabel, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    gLayout->addWidget(noteText, 0, 1, Qt::AlignLeft);

    //! adding buttons to layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 1, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}


NoteDialog::~NoteDialog()
{
    delete noteLabel;
    delete noteText;
}

void NoteDialog::accept()
{
    QDialog::accept();
}

void NoteDialog::reject()
{
    QDialog::reject();
}

void NoteDialog::show()
{
    QDialog::showFullScreen();
}

