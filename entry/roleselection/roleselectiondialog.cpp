#include "roleselectiondialog.h"
#include "ui_roleselectiondialog.h"

// 构造函数
RoleSelectionDialog::RoleSelectionDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RoleSelectionDialog) {
    // 初始化UI
    ui->setupUi(this);
    // 连接确认按钮的点击信号到对话框的accept()槽，点击后对话框会关闭并返回QDialog::Accepted
    connect(ui->confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}

// 析构函数
RoleSelectionDialog::~RoleSelectionDialog() {
    delete ui;
}

// 获取用户选择的角色
int RoleSelectionDialog::getSelectedRole() const {
    // 如果医生单选框被选中，返回1，否则返回0（患者）
    return ui->doctorRadioButton->isChecked() ? 1 : 0;
}
