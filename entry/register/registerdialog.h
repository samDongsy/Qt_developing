#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

class AuthManager; // 前置声明

namespace Ui {
class RegisterDialog;
}

// 注册对话框类
class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(int role, AuthManager* authManager, QWidget* parent = nullptr);
    ~RegisterDialog();

    // 公共方法，用于从外部控制UI的可用状态
    void setUiEnabled(bool enabled);
    // 公共方法，用于设置标题标签的文本
    void setStatusText(const QString& text);

signals:
    // 返回登录页面的信号
    void showLoginPage();

private slots:
    // "注册"按钮点击槽函数
    void on_registerButton_clicked();
    // "返回登录"按钮点击槽函数
    void on_backButton_clicked();
    // 处理注册成功的槽函数
    void onRegistrationSuccess();
    // 处理注册失败的槽函数
    void onRegistrationFailed(const QString& reason);

private:
    Ui::RegisterDialog* ui;
    AuthManager* m_authManager;
    int m_role;
};

#endif // REGISTERDIALOG_H
