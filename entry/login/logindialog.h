#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class AuthManager; // 使用前置声明

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(int role, AuthManager* authManager, QWidget* parent = nullptr);
    ~LoginDialog();

    // 新增: 公共方法，用于从外部控制UI的可用状态
    void setUiEnabled(bool enabled);
    // 新增: 公共方法，用于设置标题标签的文本
    void setStatusText(const QString& text);


signals:
    void showRegisterPage();
    void loginSuccess(bool isDoctor);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void onLoginFailed(const QString& reason);

private:
    Ui::LoginDialog* ui;
    AuthManager* m_authManager;
    int m_role;
};

#endif // LOGINDIALOG_H
