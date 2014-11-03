#include "logindialog.h"
#include "ui_logindialog.h"
#include <QUrl>
#include <QDesktopServices>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_urllabel_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl("https://www.grjsq.im/component/user/?task=register"));
}
