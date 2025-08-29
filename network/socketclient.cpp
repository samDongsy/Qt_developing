#include "socketclient.h"
#include <QJsonParseError>
#include <QDebug>

// 构造函数，初始化socket并连接所有需要的信号
SocketClient::SocketClient(QObject* parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &SocketClient::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SocketClient::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &SocketClient::onReadyRead);

    // 连接QTcpSocket内置的错误信号到我们自定义的槽
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &SocketClient::onErrorOccurred);
}

SocketClient::~SocketClient() {}

// 连接到服务器
void SocketClient::connectToServer(const QString& host, quint16 port) {
    if (m_socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "正在连接到服务器 " << host << ":" << port;
        m_socket->connectToHost(host, port);
    }
}

// 检查是否连接
bool SocketClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// 当socket发生错误时，发射我们自己的错误信号
void SocketClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // 避免编译器关于未使用参数的警告
    emit connectionError(m_socket->errorString());
}

// 发送登录请求
void SocketClient::sendLoginRequest(const QString& account, const QString& password, int role) {
    QJsonObject json;
    json["task"] = "login";
    json["account"] = account;
    json["password"] = password;
    json["role"] = role;
    sendJson(json);
}

// 发送注册请求
void SocketClient::sendRegisterRequest(const QString& account, const QString& password, int role) {
    QJsonObject json;
    json["task"] = "register";
    json["account"] = account;
    json["password"] = password;
    json["role"] = role;
    sendJson(json);
}

// 当有数据可读时，此槽函数被调用
void SocketClient::onReadyRead() {
    m_buffer.append(m_socket->readAll());
    int idx;
    while ((idx = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(idx);
        m_buffer.remove(0, idx + 1);
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            if (obj.contains("ok")) {
                emit registerResponse(obj["ok"].toBool());
            }
            else if (obj.contains("id")) {
                emit loginResponse(obj["id"].toInt(), obj["isDoctor"].toInt() == 1);
            }
        } else {
            qWarning() << "无效的JSON响应: " << line;
        }
    }
}

// 发送JSON对象
void SocketClient::sendJson(const QJsonObject& obj) {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        data.append('\n');
        m_socket->write(data);
        m_socket->flush();
    } else {
        qWarning() << "Socket未连接，无法发送数据。";
    }
}

// 当连接断开时，此槽函数被调用
void SocketClient::onDisconnected() {
    qDebug() << "与服务器断开连接";
    emit disconnected();
}
