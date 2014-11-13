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
    vector<LineItem> lines;
    if (objn.compare(QString("testButton")) == 0) {
        lines = _linelist.getLineByArea("free");
    } else if (objn.compare(QString("nAmericaButton")) == 0) {
        lines = _linelist.getLineByArea("northAmerican");
    } else if (objn.compare(QString("europeButton")) == 0) {
        lines = _linelist.getLineByArea("europe");
    } else if (objn.compare(QString("asiaaButton")) == 0) {
        lines = _linelist.getLineByArea("asiaA");
    } else if (objn.compare(QString("asiabButton")) == 0) {
        lines = _linelist.getLineByArea("asiaB");
    }
    size_t rows = ROW_COUNT > lines.size() ? ROW_COUNT : lines.size();
    ui->lineWidget->setRowCount(rows);
    size_t i = 0;
    for (i = 0;i < lines.size(); i++) {
        ui->lineWidget->setItem(i, 0, new QTableWidgetItem(QString(lines[i].getName().c_str())));
        ui->lineWidget->setItem(i, 1, new QTableWidgetItem(QString(lines[i].getProtocols().c_str())));
        ui->lineWidget->setRowHeight(i, ROW_HEIGHT);
    }
    for (; i < rows; i++) {
        ui->lineWidget->setRowHeight(i, ROW_HEIGHT);
    }
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::on_areaGroup_buttonClicked(QAbstractButton * button)
{
    setTableContent();
}
