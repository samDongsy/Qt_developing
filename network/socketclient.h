#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QAbstractSocket> // 为了使用 QAbstractSocket::SocketError

// 网络客户端类，负责与服务器的所有socket通信
class SocketClient : public QObject {
    Q_OBJECT

public:
    // 构造函数
    explicit SocketClient(QObject* parent = nullptr);
    // 析构函数
    ~SocketClient();

    // 连接到服务器
    void connectToServer(const QString& host, quint16 port);

    // 发送登录请求
    void sendLoginRequest(const QString& account, const QString& password, int role);

    // 发送注册请求
    void sendRegisterRequest(const QString& account, const QString& password, int role);

    // 检查当前是否已连接
    bool isConnected() const;

private slots:
    // 当socket准备好读取数据时调用的槽函数
    void onReadyRead();
    // 当与服务器断开连接时调用的槽函数
    void onDisconnected();
    // 当socket发生错误时调用的槽函数
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

signals:
    // 登录响应信号
    void loginResponse(int id, bool isDoctor);
    // 注册响应信号
    void registerResponse(bool ok);
    // 连接成功信号
    void connected();
    // 连接断开信号
    void disconnected();
    // 连接错误信号
    void connectionError(const QString& errorString);

private:
    // 发送JSON对象到服务器
    void sendJson(const QJsonObject& json);

    QTcpSocket* m_socket; // TCP socket 实例
    QByteArray m_buffer;  // 用于接收数据的缓冲区
};

#endif // SOCKETCLIENT_H
