#include "appmanager.h"
#include <QApplication>
#include <QMessageBox>

#include "entry/roleselection/roleselectiondialog.h"
#include "entry/login/logindialog.h"
#include "entry/register/registerdialog.h"
#include "network/socketclient.h"
#include "authmanager.h"
#include "doctor/doctorinterface/doctorinterface.h"
#include "patient/patientinterface/patientinterface.h"

// 构造函数
AppManager::AppManager(QObject *parent) : QObject(parent)
{
    m_socketClient = new SocketClient(this);
    m_authManager = new AuthManager(m_socketClient, this);

    // 连接SocketClient的所有状态信号到AppManager的槽
    connect(m_socketClient, &SocketClient::connected, this, &AppManager::onSocketConnected);
    connect(m_socketClient, &SocketClient::disconnected, this, &AppManager::onSocketDisconnected);
    connect(m_socketClient, &SocketClient::connectionError, this, &AppManager::onSocketConnectionError);
}

// 析构函数
AppManager::~AppManager()
{
    delete m_doctorInterface;
    delete m_patientInterface;
}

// 启动应用，显示第一个窗口
void AppManager::start()
{
    showRoleSelection();
}

// 显示角色选择对话框
void AppManager::showRoleSelection()
{
    RoleSelectionDialog roleDialog;
    if (roleDialog.exec() == QDialog::Accepted) {
        m_currentRole = roleDialog.getSelectedRole();
        showLogin(); // 选择角色后，显示登录窗口
    } else {
        qApp->quit(); // 如果关闭则退出程序
    }
}

// 显示登录窗口，并处理网络连接
void AppManager::showLogin()
{
    if (m_registerDialog) {
        m_registerDialog->close();
        delete m_registerDialog;
        m_registerDialog = nullptr;
    }

    m_loginDialog = new LoginDialog(m_currentRole, m_authManager);
    connect(m_loginDialog, &LoginDialog::showRegisterPage, this, &AppManager::showRegister);
    connect(m_loginDialog, &LoginDialog::loginSuccess, this, &AppManager::onLoginSuccess);
    m_loginDialog->show();

    // 关键逻辑：在显示窗口后，检查当前连接状态
    if (m_socketClient->isConnected()) {
        // 如果已经连接（例如从注册页返回），直接调用槽函数启用UI
        onSocketConnected();
    } else {
        // 如果未连接，才发起新的连接请求 (端口号根据您的日志设为5555)
        m_socketClient->connectToServer("127.0.0.1", 5555);
    }
}

// 显示注册窗口，并处理网络连接
void AppManager::showRegister()
{
    if (m_loginDialog) {
        m_loginDialog->close();
        delete m_loginDialog;
        m_loginDialog = nullptr;
    }

    m_registerDialog = new RegisterDialog(m_currentRole, m_authManager);
    connect(m_registerDialog, &RegisterDialog::showLoginPage, this, &AppManager::showLogin);
    m_registerDialog->show();

    // 关键逻辑：为注册页面也添加同样的状态检查
    if (m_socketClient->isConnected()) {
        onSocketConnected();
    } else {
        m_socketClient->connectToServer("127.0.0.1", 5555);
    }
}

// 登录成功后的处理
void AppManager::onLoginSuccess(bool isDoctor)
{
    if (m_loginDialog) {
        m_loginDialog->close();
        delete m_loginDialog;
        m_loginDialog = nullptr;
    }
    if (m_registerDialog) {
        m_registerDialog->close();
        delete m_registerDialog;
        m_registerDialog = nullptr;
    }

    if (isDoctor) {
        m_doctorInterface = new DoctorInterface();
        m_doctorInterface->show();
    } else {
        m_patientInterface = new PatientInterface();
        m_patientInterface->show();
    }
}

// 当socket成功连接时调用
void AppManager::onSocketConnected()
{
    qDebug() << "成功连接到服务器!";
    // 启用当前可见的登录或注册窗口的UI
    if (m_loginDialog) {
        m_loginDialog->setStatusText("用户登录");
        m_loginDialog->setUiEnabled(true);
    }
    if (m_registerDialog) {
        m_registerDialog->setStatusText("用户注册");
        m_registerDialog->setUiEnabled(true);
    }
}

// 当socket断开连接时调用
void AppManager::onSocketDisconnected()
{
    qDebug() << "与服务器的连接已断开。";
    // 禁用当前可见的登录或注册窗口的UI
    if (m_loginDialog) {
        m_loginDialog->setStatusText("连接已断开");
        m_loginDialog->setUiEnabled(false);
    }
    if (m_registerDialog) {
        m_registerDialog->setStatusText("连接已断开");
        m_registerDialog->setUiEnabled(false);
    }
    QMessageBox::warning(nullptr, "连接提示", "与服务器的连接已断开。");
}

// 当socket连接出错时调用
void AppManager::onSocketConnectionError(const QString& errorString)
{
    qDebug() << "连接服务器失败:" << errorString;
    // 更新当前可见的登录或注册窗口的状态文本
    if (m_loginDialog) {
        m_loginDialog->setStatusText("连接失败");
    }
    if (m_registerDialog) {
        m_registerDialog->setStatusText("连接失败");
    }
    QMessageBox::critical(nullptr, "连接错误", "无法连接到服务器: \n" + errorString);
}
