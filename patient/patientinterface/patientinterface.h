#ifndef PATIENTINTERFACE_H
#define PATIENTINTERFACE_H

#include <QMainWindow>
#include <QPixmap> // 包含 QPixmap 头文件

QT_BEGIN_NAMESPACE
namespace Ui { class PatientInterface; }
QT_END_NAMESPACE

class PatientInterface : public QMainWindow
{
    Q_OBJECT

public:
    PatientInterface(QWidget *parent = nullptr);
    ~PatientInterface();

protected:
    // 重写 resizeEvent 事件，用于处理图片的高质量缩放
    void resizeEvent(QResizeEvent *event) override;
    // 让图片在开始调整一次
    void showEvent(QShowEvent* event) override;

private slots:
    // 处理"挂号"按钮点击事件的槽函数
    void onRegistrationClicked();

    // 处理"查看病例"按钮点击事件的槽函数
    void onViewCaseClicked();

    // 处理"查看处方和缴费"按钮点击事件的槽函数
    void onViewPrescriptionClicked();

    // 处理"编辑个人信息"按钮点击事件的槽函数
    void onEditProfileClicked();

    // 处理"查看医生信息"按钮点击事件的槽函数
    void onViewDoctorInfoClicked();

    // 处理"健康评估"按钮点击事件的槽函数
    void onHealthAssessmentClicked();

    // 处理"医患沟通平台"按钮点击事件的槽函数
    void onCommunicationClicked();

    // 处理"退出"按钮点击事件的槽函数
    void onExitClicked();

private:
    Ui::PatientInterface *ui;
    QPixmap m_patientPixmap; // 用于存储原始图片

    void setupConnections();
    void loadImage(); // 该函数现在只负责从资源加载图片到m_patientPixmap
};

#endif // PATIENTINTERFACE_H
