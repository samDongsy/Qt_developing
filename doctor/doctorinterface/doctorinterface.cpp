#include "doctorinterface.h"
#include "ui_doctorinterface.h"

#include "../../general/viewregistration/viewregistration.h"
#include "../editcase/editcase.h"
#include "../editprescription/editprescription.h"
#include "../../general/communication/communication.h"
#include "../editprofile/doctorprofilepage.h" // <-- 关键：删除对旧头文件的包含

#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QResizeEvent>

// 构造函数
DoctorInterface::DoctorInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DoctorInterface)
    , m_doctorProfilePage(nullptr) // 初始化新成员变量
{
    ui->setupUi(this);
    loadImage();
    setupConnections();
    resize(1600,1200);

    // 假设您的UI中有一个名为 contentStackedWidget 的 QStackedWidget
    ui->contentStackedWidget->setCurrentIndex(0);
}

// 析构函数
DoctorInterface::~DoctorInterface()
{
    delete ui;
}

// ... setupConnections, loadImage, resizeEvent, showEvent 等函数保持不变 ...

void DoctorInterface::setupConnections()
{
    connect(ui->viewRegistrationButton, &QPushButton::clicked, this, &DoctorInterface::onViewRegistrationClicked);
    connect(ui->editCaseButton, &QPushButton::clicked, this, &DoctorInterface::onEditCaseClicked);
    connect(ui->editPrescriptionButton, &QPushButton::clicked, this, &DoctorInterface::onEditPrescriptionClicked);
    connect(ui->editProfileButton, &QPushButton::clicked, this, &DoctorInterface::onEditProfileClicked);
    connect(ui->communicationButton, &QPushButton::clicked, this, &DoctorInterface::onCommunicationClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &DoctorInterface::onExitClicked);
}

void DoctorInterface::loadImage()
{
    if (!m_doctorPixmap.load(":/images/doctor_image.png")) {
        qWarning() << "Failed to load doctor image!";
        ui->imageLabel->setText("图片加载失败");
    }
}


// --- 核心修改 ---
// 点击"编辑个人信息"按钮的槽函数
void DoctorInterface::onEditProfileClicked()
{
    qDebug() << "“编辑个人信息”按钮被点击";

    // 不再创建 EditProfile 的实例
    DoctorProfilePage* editprofile =new DoctorProfilePage; // <-- 删除这一行
    editprofile ->show();                   // <-- 删除这一行

    // 而是创建并显示新的 DoctorProfilePage 实例
    // if (!m_doctorProfilePage) {
    //     m_doctorProfilePage = new DoctorProfilePage(); // 注意：这里没有parent
    // }

    // 调用辅助函数切换到该页面
    switchContentPage(m_doctorProfilePage);
}

// 辅助函数，用于切换StackedWidget中的页面
void DoctorInterface::switchContentPage(QWidget *widget)
{
    if (!widget) return;
    int index = ui->contentStackedWidget->indexOf(widget);
    if (index == -1) {
        index = ui->contentStackedWidget->addWidget(widget);
    }
    ui->contentStackedWidget->setCurrentIndex(index);
}


// 每当窗口大小改变时，这个事件处理器就会被调用
void DoctorInterface::resizeEvent(QResizeEvent *event)
{
    // 首先调用基类的实现
    QMainWindow::resizeEvent(event);

    // 如果图片已成功加载
    if (!m_doctorPixmap.isNull()) {
        // 将图片以平滑的方式缩放到 imageLabel 的当前大小，并保持其宽高比
        ui->imageLabel->setPixmap(m_doctorPixmap.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}

void DoctorInterface::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);

    // 如果图片已成功加载
    if (!m_doctorPixmap.isNull()) {
        // 将图片以平滑的方式缩放到 imageLabel 的当前大小，并保持其宽高比
        ui->imageLabel->setPixmap(m_doctorPixmap.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}
// --- 槽函数实现 ---

void DoctorInterface::onViewRegistrationClicked()
{
    qDebug() << "“查看挂号信息”按钮被点击";

    ViewRegistration  *viewregistration =new ViewRegistration;
    viewregistration->exec();
}

void DoctorInterface::onEditCaseClicked()
{
    qDebug() << "“编辑病例”按钮被点击";

    EditCase *editcase = new EditCase;
    editcase->exec();
}

void DoctorInterface::onEditPrescriptionClicked()
{
    qDebug() << "“编辑处方和缴费单”按钮被点击";

    EditPrescription *editprescription = new EditPrescription;
    editprescription->exec();
}

void DoctorInterface::onCommunicationClicked()
{
    qDebug() << "“医患沟通平台”按钮被点击";

    Communication *communication = new Communication;
    communication  -> exec();
}

void DoctorInterface::onExitClicked()
{
    qDebug() << "“退出”按钮被点击，程序关闭";
    this->close();
}
