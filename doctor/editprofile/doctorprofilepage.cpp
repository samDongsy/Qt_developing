#include "doctorprofilepage.h"
#include "ui_doctorprofilepage.h" // 包含由 .ui 文件生成的头文件
#include <QDebug>

DoctorProfilePage::DoctorProfilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorProfilePage) // 创建UI类的实例
{
    ui->setupUi(this); // 使用UI文件设置界面

    populateTimeCombos(); // 填充时间下拉框
    setupConnections();   // 设置信号槽

    // --- 将所有需要切换状态的控件添加到列表中 ---
    inputWidgets << ui->nameInput << ui->departmentInput << ui->employeeNoInput << ui->titleInput
                 << ui->detailInput << ui->startHourCombo << ui->startMinuteCombo << ui->endHourCombo
                 << ui->endMinuteCombo << ui->registrationFeeInput << ui->dailyLimitInput
                 << ui->vacationYes << ui->vacationNo << ui->emailInput << ui->phoneInput;

    toggleEditMode(false); // 初始状态为只读
}

DoctorProfilePage::~DoctorProfilePage()
{
    delete ui; // 析构时删除UI对象
}

void DoctorProfilePage::populateTimeCombos()
{
    for (int i = 0; i < 24; ++i) {
        QString hour = QString("%1").arg(i, 2, 10, QChar('0'));
        ui->startHourCombo->addItem(hour);
        ui->endHourCombo->addItem(hour);
    }
    for (int i = 0; i < 60; ++i) {
        QString minute = QString("%1").arg(i, 2, 10, QChar('0'));
        ui->startMinuteCombo->addItem(minute);
        ui->endMinuteCombo->addItem(minute);
    }
}

void DoctorProfilePage::setupConnections()
{
    // 连接按钮到槽函数
    connect(ui->editButton, &QPushButton::clicked, this, [=]() { toggleEditMode(true); });
    connect(ui->saveButton, &QPushButton::clicked, this, &DoctorProfilePage::onSaveClicked);
}

void DoctorProfilePage::onSaveClicked()
{
    qDebug() << "保存按钮被点击，数据将被发送到服务器...";
    // 在这里添加您真正的保存数据的逻辑，例如：
    // QString name = ui->nameInput->text();
    // ...获取所有数据...
    // m_networkManager->saveDoctorProfile(...);

    toggleEditMode(false); // 保存后切换回只读模式
}


void DoctorProfilePage::toggleEditMode(bool editable)
{
    // 遍历所有输入控件并设置其状态
    for (QWidget *widget : inputWidgets) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget);
        if (lineEdit) {
            lineEdit->setReadOnly(!editable);
            continue;
        }

        QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget);
        if (textEdit) {
            textEdit->setReadOnly(!editable);
            continue;
        }

        // 其他控件（QComboBox, QRadioButton）直接启用/禁用
        widget->setEnabled(editable);
    }

    // 特殊处理按钮的可用性
    ui->editButton->setEnabled(!editable);
    ui->saveButton->setEnabled(editable);
}
