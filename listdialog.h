#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QThread>
#include <QString>
#include "define.h"
#include "linelist.hpp"
#include <string>
#include <vector>
#include <pingproc.h>
#include <vpnproc.h>

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
    void on_pushButton_clicked();

private:
    void initTable();
    void setTableContent();

signals:
    void getping(QString area, QString ip, int line);
    void startVPN(QString id, QString user, QString password, QString ip);

public slots:
    void setping(QString area, QString sec, int line);
    void setVPNInfo(bool state, QString message);

private:
    Ui::ListDialog *ui;
    base::LineList _linelist;
    std::vector<base::LineItem> _lines;
    QString _currentArea;
    PingProc *_pingproc;
    QThread *_thread;
    VpnProc *_vpnproc;
    QThread *_vpnThread;
};

#endif // LISTDIALOG_H
