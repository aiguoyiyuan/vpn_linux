#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QThread>
#include "define.h"
#include "linelist.hpp"
#include <string>
#include <vector>
#include <pingproc.h>

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

signals:
    void getping(QString area, QString ip, int line);

public slots:
    void setping(QString area, QString sec, int line);

private:
    Ui::ListDialog *ui;
    base::LineList _linelist;
    std::vector<base::LineItem> _lines;
    QString _currentArea;
    PingProc *_pingproc;
    QThread *_thread;
};

#endif // LISTDIALOG_H
