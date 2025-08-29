#include "logindialog.h"
#include "ui_logindialog.h"
#include "authmanager.h"
#include <QMessageBox>

LoginDialog::LoginDialog(int role, AuthManager* authManager, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_authManager(authManager),
    m_role(role) {
    ui->setupUi(this);

    if (m_role == 1) {
        setWindowTitle("医生登录");
    } else {
        setWindowTitle("患者登录");
    }

    connect(m_authManager, &AuthManager::loginFailed, this, &LoginDialog::onLoginFailed);
    connect(m_authManager, &AuthManager::loginSuccess, this, &LoginDialog::loginSuccess);

    // 关键修改：初始化时，禁用所有UI控件并提示正在连接
    setStatusText("正在连接服务器...");
    setUiEnabled(false);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

// 新增: setUiEnabled的实现
void LoginDialog::setUiEnabled(bool enabled)
{
    ui->accountLineEdit->setEnabled(enabled);
    ui->passwordLineEdit->setEnabled(enabled);
    ui->loginButton->setEnabled(enabled);
    ui->registerButton->setEnabled(enabled);
}

// 新增: setStatusText的实现
void LoginDialog::setStatusText(const QString& text)
{
    ui->titleLabel->setText(text);
}


// ... on_loginButton_clicked, on_registerButton_clicked, onLoginFailed 等其他函数保持不变 ...
void LoginDialog::on_loginButton_clicked() {
    const QString account = ui->accountLineEdit->text().trimmed();
    const QString password = ui->passwordLineEdit->text();
    if (account.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "帐号和密码不能为空！");
        return;
    }
    m_authManager->login(account, password, m_role);
}

void LoginDialog::on_registerButton_clicked() {
    emit showRegisterPage();
}

void LoginDialog::onLoginFailed(const QString& reason) {
    QMessageBox::critical(this, "登录失败", reason);
}
