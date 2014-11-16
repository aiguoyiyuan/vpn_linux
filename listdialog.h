#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QProcess>
#include "define.h"
#include "linelist.hpp"
#include <string>
#include <vector>

namespace Ui {
class ListDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = 0);
    ~ListDialog();

private slots:
    void on_areaGroup_buttonClicked(QAbstractButton * button);

private:
    void initTable();
    void setTableContent();
    void ping();
private slots:
    void pingStarted();

private:
    Ui::ListDialog *ui;
    base::LineList _linelist;
    QProcess *_process;
    std::vector<base::LineItem> _lines;
    size_t _currentPingLine;
};

#endif // LISTDIALOG_H
