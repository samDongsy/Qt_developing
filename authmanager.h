#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject> // 1. 必须包含 QObject 头文件
#include <QString> // 因为信号和槽中用到了 QString

// 前置声明，避免在头文件中包含完整的 "socketclient.h"
class SocketClient;

// 2. 必须继承自 QObject
class AuthManager : public QObject
{
    Q_OBJECT // 3. 必须有 Q_OBJECT 宏才能使用信号和槽

public:
    // 4. 构造函数的声明，必须与 .cpp 文件中的实现完全一致
    explicit AuthManager(SocketClient* client, QObject* parent = nullptr);

    // 5. 公共成员函数的声明
    void login(const QString& account, const QString& password, int role);
    void registerAccount(const QString& account, const QString& password, int role);

signals:
    // 6. 信号的声明
    void loginSuccess(bool isDoctor);
    void loginFailed(const QString& reason);
    void registrationSuccess();
    void registrationFailed(const QString& reason);

private slots:
    // 7. 槽函数的声明
    void onLoginResponse(int id, bool isDoctor);
    void onRegisterResponse(bool ok);

private:
    // 8. 成员变量的声明
    SocketClient* m_client;
};

#endif // AUTHMANAGER_H
