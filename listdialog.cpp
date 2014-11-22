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
    _pingproc(NULL),
    _thread(NULL),
    _vpnproc(NULL),
    _vpnThread(NULL)
{
    _pingproc =  new PingProc;
    _thread = new QThread;
    _vpnproc = new VpnProc;
    _vpnThread = new QThread;

    int ret = 0;
    if ((ret = _linelist.initFromFile(LIST_INI)) != 0) {
        //show a warning
    }

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    connect(this, SIGNAL(getping(QString , QString , int)), _pingproc, SLOT(getping(QString, QString, int)));
    connect(_pingproc, SIGNAL(setping(QString,QString,int)), this, SLOT(setping(QString,QString,int)));
    connect(this, SIGNAL(startVPN(QString, QString, QString, QString)), _vpnproc, SLOT(startVPN(QString, QString, QString, QString)));
    connect(_vpnproc, SIGNAL(setVPNInfo(bool,QString)), this, SLOT(setVPNInfo(bool,QString)));

    _pingproc->moveToThread(_thread);
    _thread->start();
    _vpnproc->moveToThread(_vpnThread);
    _vpnThread->start();

    initTable();
    setTableContent();
}

void ListDialog::initTable()
{
    QStringList widgetHeader;
    widgetHeader << "服务器" << "协议" << "响应时间";
    ui->lineWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->lineWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
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
    QPushButton *areaButton = qobject_cast<QPushButton *> (ui->areaGroup->checkedButton());
    QString objn = areaButton->objectName();
    _currentArea = objn;

    ui->lineWidget->clearContents();  

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
        emit getping(objn, QString(_lines[i].getIp().c_str()), i);
    }
    for (; i < rows; i++) {
        ui->lineWidget->setRowHeight(i, ROW_HEIGHT);
    }
    ui->lineWidget->setCurrentCell(0,0,QItemSelectionModel::ClearAndSelect|QItemSelectionModel::Rows);
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::on_areaGroup_buttonClicked(QAbstractButton * button)
{
    setTableContent();
}

void ListDialog::setping(QString area, QString sec, int line)
{
    if (_currentArea == area) {
        ui->lineWidget->setItem(line, 2, new QTableWidgetItem(sec + QString("ms")));
    }
}

void ListDialog::on_pushButton_clicked()
{
    int current = ui->lineWidget->currentRow();
    QString ip = QString::fromStdString(_lines[current].getIp());
    QString id = QString::fromStdString(_lines[current].getId());
    QString user("spotted_deer");
    QString password("9151003685");
    emit startVPN(id, user, password, ip);
}

void ListDialog::setVPNInfo(bool state, QString message)
{
    QString s = message;
}
