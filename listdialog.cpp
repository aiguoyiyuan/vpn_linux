#include "listdialog.h"
#include "ui_listdialog.h"
#include <QProcess>
#include <stdio.h>
#include <QDebug>

using namespace base;
using namespace std;

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog),
    _process(NULL),
    _currentPingLine(0)
{
    _process =  new QProcess;
    int ret = 0;
    if ((ret = _linelist.initFromFile(LIST_INI)) != 0) {
        //show a warning
    }

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    //connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setPing()));
    //connect(_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(pingFinished(int,QProcess::ExitStatus)));
    //connect(_process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(statesChange(QProcess::ProcessState)));
    connect(_process, SIGNAL(started()), this, SLOT(pingStarted()));
    initTable();
    setTableContent();
}

void ListDialog::initTable()
{
    QStringList widgetHeader;
    widgetHeader << "服务器" << "协议" << "响应时间";
    ui->lineWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->lineWidget->setColumnWidth(0, SERVER_WIDGET);
    ui->lineWidget->setColumnWidth(1, PROTOCOL_WIDGET);
    ui->lineWidget->horizontalHeader()->setStretchLastSection(true);
    ui->lineWidget->setHorizontalHeaderLabels(widgetHeader);
    ui->lineWidget->verticalHeader()->setVisible(false);
    ui->lineWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->lineWidget->setSelectionBehavior(QTableWidget::SelectRows);
    ui->lineWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void ListDialog::setTableContent()
{
    ui->lineWidget->clearContents();
    QPushButton *areaButton = qobject_cast<QPushButton *> (ui->areaGroup->checkedButton());
    QString objn = areaButton->objectName();

    if (objn.compare(QString("testButton")) == 0) {
        _lines = _linelist.getLineByArea("free");
    } else if (objn.compare(QString("nAmericaButton")) == 0) {
        _lines = _linelist.getLineByArea("northAmerican");
    } else if (objn.compare(QString("europeButton")) == 0) {
        _lines = _linelist.getLineByArea("europe");
    } else if (objn.compare(QString("asiaaButton")) == 0) {
        _lines = _linelist.getLineByArea("asiaA");
    } else if (objn.compare(QString("asiabButton")) == 0) {
        _lines = _linelist.getLineByArea("asiaB");
    }
    size_t rows = ROW_COUNT > _lines.size() ? ROW_COUNT : _lines.size();
    ui->lineWidget->setRowCount(rows);
    size_t i = 0;
    for (i = 0;i < _lines.size(); i++) {
        ui->lineWidget->setItem(i, 0, new QTableWidgetItem(QString(_lines[i].getName().c_str())));
        ui->lineWidget->setItem(i, 1, new QTableWidgetItem(QString(_lines[i].getProtocols().c_str())));
        ui->lineWidget->setRowHeight(i, ROW_HEIGHT);
    }
    for (; i < rows; i++) {
        ui->lineWidget->setRowHeight(i, ROW_HEIGHT);
    }

    _currentPingLine = 0;
    ping();
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::on_areaGroup_buttonClicked(QAbstractButton * button)
{
    setTableContent();
}

void ListDialog::ping()
{
    if (_currentPingLine < _lines.size()) {
        string ip(_lines[_currentPingLine].getIp());
        QString cmd("ping");
        QStringList args;
        args << ip.c_str() << PING_ARGS.c_str();
        _process->start(cmd, args);
    }
}

void ListDialog::pingStarted()
{
    bool ret = _process->waitForFinished(1000);
    QString sec;
    QString result;
    int from, b, e;
    if (ret == false) {
        sec.setNum(200);
        goto SET_PING;
    } else {
        result = QString::fromLocal8Bit(_process->readAllStandardOutput());
        from = result.indexOf(QString("mdev"));
        if (from == -1) {
            sec.setNum(200);
            goto SET_PING;
        }
        b = result.indexOf('/', from);
        if (b == -1) {
            sec.setNum(200);
            goto SET_PING;
        }
        e = result.indexOf('/', b+1);
        if (e == -1) {
            sec.setNum(200);
            goto SET_PING;
        }
        sec =  result.mid(b+1, e-b-1);
    }
SET_PING:
    ui->lineWidget->setItem(_currentPingLine, 2, new QTableWidgetItem(sec + QString("ms")));

    _currentPingLine++;
    if (_currentPingLine < _lines.size()) {
        ping();
    }
}
