#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "authmanager.h"
#include <QMessageBox>

// 构造函数
RegisterDialog::RegisterDialog(int role, AuthManager* authManager, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    m_authManager(authManager),
    m_role(role) {
    ui->setupUi(this);

    // 设置窗口标题
    if (m_role == 1) {
        setWindowTitle("医生注册");
    } else {
        setWindowTitle("患者注册");
    }

    // 连接认证管理器的信号到本类的槽函数
    connect(m_authManager, &AuthManager::registrationSuccess, this, &RegisterDialog::onRegistrationSuccess);
    connect(m_authManager, &AuthManager::registrationFailed, this, &RegisterDialog::onRegistrationFailed);

    // 初始化时，设置为禁用状态并等待网络
    setStatusText("请等待网络连接...");
    setUiEnabled(false);
}

// 析构函数
RegisterDialog::~RegisterDialog() {
    delete ui;
}

// 设置UI可用状态的实现
void RegisterDialog::setUiEnabled(bool enabled)
{
    ui->accountLineEdit->setEnabled(enabled);
    ui->passwordLineEdit->setEnabled(enabled);
    ui->confirmPasswordLineEdit->setEnabled(enabled);
    ui->registerButton->setEnabled(enabled);
    ui->backButton->setEnabled(enabled);
}

// 设置状态文本的实现
void RegisterDialog::setStatusText(const QString& text)
{
    ui->titleLabel->setText(text);
}

// "注册"按钮点击事件处理
void RegisterDialog::on_registerButton_clicked() {
    const QString account = ui->accountLineEdit->text().trimmed();
    const QString password = ui->passwordLineEdit->text();
    const QString confirmPassword = ui->confirmPasswordLineEdit->text();

    // 前端校验
    if (account.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "帐号和密码不能为空！");
        return;
    }
    if (password != confirmPassword) {
        QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
        return;
    }

    // 调用认证管理器进行注册
    m_authManager->registerAccount(account, password, m_role);
}

// "返回登录"按钮点击事件处理
void RegisterDialog::on_backButton_clicked() {
    // 发射信号，通知主流程显示登录页面
    emit showLoginPage();
}

// 处理注册成功的槽函数
void RegisterDialog::onRegistrationSuccess() {
    QMessageBox::information(this, "注册成功", "帐号注册成功！");
    // 注册成功后，自动返回登录页面
    emit showLoginPage();
}

// 处理注册失败的槽函数
void RegisterDialog::onRegistrationFailed(const QString& reason) {
    QMessageBox::critical(this, "注册失败", reason);
}
