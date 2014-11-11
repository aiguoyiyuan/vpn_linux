#include "listdialog.h"
#include "ui_listdialog.h"

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog)
{
    int ret = 0;
    if ((ret = _linelist.initFromFile(LIST_INI)) != 0) {
        //show a warning
    }

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    QStringList widgetHeader;
    widgetHeader << "服务器" << "响应时间";
    ui->lineWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    int width = ui->lineWidget->width();
    if (SERVER_WIDGET < width-100) {
        ui->lineWidget->setColumnWidth(0, SERVER_WIDGET);
    } else {
        ui->lineWidget->setColumnWidth(0, width-100);
    }
    ui->lineWidget->horizontalHeader()->setStretchLastSection(true);
    ui->lineWidget->setHorizontalHeaderLabels(widgetHeader);

    ui->lineWidget->setRowCount(5);
    QTableWidgetItem *item = new QTableWidgetItem(QString("192.168.1.1"));
    ui->lineWidget->setItem(0, 0, new QTableWidgetItem(QString("192.168.1.1")));
    ui->lineWidget->setItem(1, 0, new QTableWidgetItem(QString("192.168.1.2")));
    //ui->lineWidget->setItem(2, 0, item);
    //ui->lineWidget->setItem(3, 0, item);

    //QPushButton *areaButton = qobject_cast<QPushButton *> (ui->areaGroup->checkedButton());
    //if (QString::compare((areaButton->objectName(), QString("testButton")))) {

    //}


}

ListDialog::~ListDialog()
{
    delete ui;
}
