#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include "define.h"
#include "linelist.hpp"

namespace Ui {
class ListDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = 0);
    ~ListDialog();

private:
    Ui::ListDialog *ui;
    base::LineList _linelist;
};

#endif // LISTDIALOG_H
