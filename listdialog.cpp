#include "listdialog.h"
#include "ui_listdialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

ListDialog::~ListDialog()
{
    delete ui;
}
