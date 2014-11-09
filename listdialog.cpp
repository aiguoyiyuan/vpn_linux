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

    QStringList widgetHeader;
    widgetHeader << "服务器" << "响应时间";
    ui->lineWidget->setHorizontalHeaderLabels(widgetHeader);
    QTableWidgetItem *item = new QTableWidgetItem(QString("192.168.1.1"));
    ui->lineWidget->setItem(1,1, item);

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());


    QPushButton *areaButton = qobject_cast<QPushButton *> (ui->areaGroup->checkedButton());
    //if (QString::compare((areaButton->objectName(), QString("testButton")))) {

    //}


}

ListDialog::~ListDialog()
{
    delete ui;
}
