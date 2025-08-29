#ifndef DOCTORINTERFACE_H
#define DOCTORINTERFACE_H

#include <QMainWindow>
#include <QPixmap>

// --- 修改点 ---
// 包含新的个人信息页面头文件
#include "../editprofile/doctorprofilepage.h" // 路径请根据您的项目结构确认

QT_BEGIN_NAMESPACE
namespace Ui { class DoctorInterface; }
QT_END_NAMESPACE

class DoctorInterface : public QMainWindow
{
    Q_OBJECT

public:
    DoctorInterface(QWidget *parent = nullptr);
    ~DoctorInterface();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent* event) override;

private slots:
    void onViewRegistrationClicked();
    void onEditCaseClicked();
    void onEditPrescriptionClicked();
    void onEditProfileClicked(); // 槽函数声明保持不变
    void onCommunicationClicked();
    void onExitClicked();

private:
    Ui::DoctorInterface *ui;
    QPixmap m_doctorPixmap;

    // --- 修改点 ---
    // 添加一个成员变量来管理新的页面实例
    DoctorProfilePage *m_doctorProfilePage;

    void setupConnections();
    void loadImage();
    void switchContentPage(QWidget *widget); // 假设这个辅助函数已存在
};

#endif // DOCTORINTERFACE_H
