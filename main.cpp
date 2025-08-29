#include "appmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建应用管理器实例
    AppManager manager;
    // 启动应用流程
    manager.start();

    // 进入Qt事件循环
    return a.exec();
}
