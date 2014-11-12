#include "listdialog.h"
#include "ui_listdialog.h"

using namespace base;
using namespace std;

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

    initTable();
    setTableContent();
    //ui->lineWidget->setItem(2, 0, item);
    //ui->lineWidget->setItem(3, 0, item);
}

void ListDialog::initTable()
{
    QStringList widgetHeader;
    widgetHeader << "服务器" << "协议" << "响应时间";
    ui->lineWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    int width = ui->lineWidget->width();
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
    if (objn.compare(QString("testButton")) == 0) {
        vector<LineItem> lines = _linelist.getLineByArea("free");
        ui->lineWidget->setRowCount(lines.size());
        for (size_t i = 0;i < lines.size(); i++) {
            ui->lineWidget->setItem(i, 0, new QTableWidgetItem(QString(lines[i].getName().c_str())));
            ui->lineWidget->setItem(i, 1, new QTableWidgetItem(QString(lines[i].getProtocols().c_str())));
        }
    }
}

ListDialog::~ListDialog()
{
    delete ui;
}
