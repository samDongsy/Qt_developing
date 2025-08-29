#include "patientinterface.h"
#include "ui_patientinterface.h"
#include "../../patient/healthassessment/healthassessment.h"
#include "../../general/communication/communication.h"
#include "../registration/registration.h"
#include "../viewcase/viewcase.h"
#include "../viewprescription/viewprescription.h"

#include "../editprofile/editprofile.h"

#include "../viewdoctorinfo/viewdoctorinfo.h"

#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QResizeEvent> // 包含 QResizeEvent 头文件

// 构造函数
PatientInterface::PatientInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PatientInterface)
{
    // 初始化UI
    ui->setupUi(this);

    // 从资源文件加载原始图片到成员变量
    loadImage();

    // 设置信号和槽的连接
    setupConnections();

    resize(1600,1200);
}

// 析构函数
PatientInterface::~PatientInterface()
{
    delete ui;
}

// 设置信号和槽的连接
void PatientInterface::setupConnections()
{
    connect(ui->registrationButton, &QPushButton::clicked, this, &PatientInterface::onRegistrationClicked);
    connect(ui->viewCaseButton, &QPushButton::clicked, this, &PatientInterface::onViewCaseClicked);
    connect(ui->viewPrescriptionButton, &QPushButton::clicked, this, &PatientInterface::onViewPrescriptionClicked);
    connect(ui->editProfileButton, &QPushButton::clicked, this, &PatientInterface::onEditProfileClicked);
    connect(ui->viewDoctorInfoButton, &QPushButton::clicked, this, &PatientInterface::onViewDoctorInfoClicked);
    connect(ui->healthAssessmentButton, &QPushButton::clicked, this, &PatientInterface::onHealthAssessmentClicked);
    connect(ui->communicationButton, &QPushButton::clicked, this, &PatientInterface::onCommunicationClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &PatientInterface::onExitClicked);
}

// 该函数现在只负责从资源加载图片到成员变量 m_patientPixmap
void PatientInterface::loadImage()
{
    if (!m_patientPixmap.load(":/images/patient_image.png")) {
        qWarning() << "Failed to load patient image!";
        ui->imageLabel->setText("图片加载失败");
    }
}

// 每当窗口大小改变时，这个事件处理器就会被调用
void PatientInterface::resizeEvent(QResizeEvent *event)
{
    // 首先调用基类的实现
    QMainWindow::resizeEvent(event);

    // 如果图片已成功加载
    if (!m_patientPixmap.isNull()) {
        // 将图片以平滑的方式缩放到 imageLabel 的当前大小，并保持其宽高比
        ui->imageLabel->setPixmap(m_patientPixmap.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}

void PatientInterface::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);

    // 如果图片已成功加载
    if (!m_patientPixmap.isNull()) {
        // 将图片以平滑的方式缩放到 imageLabel 的当前大小，并保持其宽高比
        ui->imageLabel->setPixmap(m_patientPixmap.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}
// --- 槽函数实现 ---

void PatientInterface::onRegistrationClicked()
{
    qDebug() << "“挂号”按钮被点击";

    Registration  *registration= new Registration;
    registration->exec();
}

void PatientInterface::onViewCaseClicked()
{
    qDebug() << "“查看病例”按钮被点击";

    ViewCase *viewcase =new ViewCase;
    viewcase->exec();
}

void PatientInterface::onViewPrescriptionClicked()
{
    qDebug() << "“查看处方和缴费”按钮被点击";

    ViewPrescription *viewprescription = new ViewPrescription;
    viewprescription->exec();
}

void PatientInterface::onEditProfileClicked()
{
    qDebug() << "“编辑个人信息”按钮被点击";

    EditProfile *editprofile = new EditProfile;
    editprofile->exec();
}

void PatientInterface::onViewDoctorInfoClicked()
{
    qDebug() << "“查看医生信息”按钮被点击";

    ViewDoctorInfo *viewdoctorinfo = new ViewDoctorInfo;
    viewdoctorinfo->exec();
}

void PatientInterface::onHealthAssessmentClicked()
{
    qDebug() << "“健康评估”按钮被点击";

    HealthAssessment *healthAssessment = new HealthAssessment();
    healthAssessment->exec();
}

void PatientInterface::onCommunicationClicked()
{
    qDebug() << "“医患沟通平台”按钮被点击";

    Communication *communication= new Communication();
    communication->exec();
}

void PatientInterface::onExitClicked()
{
    qDebug() << "“退出”按钮被点击，程序关闭";
    this->close();
}
