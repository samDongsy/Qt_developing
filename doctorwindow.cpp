#include "doctorwindow.h"
#include "ui_doctorwindow.h"

// DoctorWindow 类的构造函数
// parent: 父窗口部件的指针
DoctorWindow::DoctorWindow(QWidget *parent) :
    QMainWindow(parent),          // 调用基类 QMainWindow 的构造函数
    ui(new Ui::DoctorWindow)      // 创建并初始化 UI 对象
{
    // ui->setupUi(this) 会读取 .ui 文件并根据其内容创建和布局窗口中的所有小部件
    ui->setupUi(this);
}

// DoctorWindow 类的析构函数
DoctorWindow::~DoctorWindow()
{
    // 删除在构造函数中创建的 ui 对象，防止内存泄漏
    delete ui;
}
