#include "authmanager.h" // <--- 关键修正：包含自己的头文件
#include "network/socketclient.h" // 包含SocketClient的完整定义以便使用
#include <QString>      // <--- 关键修正：包含QString的定义

// 构造函数
AuthManager::AuthManager(SocketClient* client, QObject* parent)
    : QObject(parent), m_client(client) {
    // 将SocketClient的信号连接到本类的槽函数
    connect(m_client, &SocketClient::loginResponse, this, &AuthManager::onLoginResponse);
    connect(m_client, &SocketClient::registerResponse, this, &AuthManager::onRegisterResponse);
}

// 调用SocketClient发送登录请求
void AuthManager::login(const QString& account, const QString& password, int role) {
    m_client->sendLoginRequest(account, password, role);
}

// 调用SocketClient发送注册请求
void AuthManager::registerAccount(const QString& account, const QString& password, int role) {
    m_client->sendRegisterRequest(account, password, role);
}

// 处理登录响应的槽函数
void AuthManager::onLoginResponse(int id, bool isDoctor) {
    // 根据服务端返回的id判断登录是否成功
    if (id != -1) {
        // id不为-1，登录成功，发射成功信号
        emit loginSuccess(isDoctor);
    } else {
        // id为-1，登录失败，发射失败信号
        emit loginFailed("用户名或密码错误");
    }
}

// 处理注册响应的槽函数
void AuthManager::onRegisterResponse(bool ok) {
    // 根据服务端返回的布尔值判断注册是否成功
    if (ok) {
        // 注册成功
        emit registrationSuccess();
    } else {
        // 注册失败
        emit registrationFailed("用户已存在，注册失败");
    }
}
