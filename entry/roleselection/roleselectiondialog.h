#ifndef ROLESELECTIONDIALOG_H
#define ROLESELECTIONDIALOG_H

#include <QDialog>

// 声明UI类
namespace Ui {
class RoleSelectionDialog;
}

// 角色选择对话框类
class RoleSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit RoleSelectionDialog(QWidget* parent = nullptr);
    ~RoleSelectionDialog();

    // 获取选择的角色（0为患者，1为医生）
    int getSelectedRole() const;

private:
    Ui::RoleSelectionDialog* ui; // UI对象指针
};

#endif // ROLESELECTIONDIALOG_H
