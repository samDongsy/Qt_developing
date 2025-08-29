#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include "doctor/doctorinterface/doctorinterface.h"
#include "patient/patientinterface/patientinterface.h"

class SocketClient;
// ... 其他前置声明
class AuthManager;
class LoginDialog;
class RegisterDialog;
class DoctorWindow;
class PatientWindow;

class AppManager : public QObject
{
    Q_OBJECT

public:
    explicit AppManager(QObject *parent = nullptr);
    ~AppManager();
    void start();

private slots:
    void showLogin();
    void showRegister();
    void onLoginSuccess(bool isDoctor);
    // 新增: 用于响应Socket连接状态的槽函数
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketConnectionError(const QString& errorString);

private:
    // ... 其他成员变量和函数不变
    void showRoleSelection();
    SocketClient* m_socketClient = nullptr;
    AuthManager* m_authManager = nullptr;
    LoginDialog* m_loginDialog = nullptr;
    RegisterDialog* m_registerDialog = nullptr;
    DoctorInterface* m_doctorInterface = nullptr;
    PatientInterface* m_patientInterface = nullptr;
    int m_currentRole = 0;
};

#endif // APPMANAGER_H
