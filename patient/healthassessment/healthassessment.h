#ifndef HEALTHASSESSMENT_H
#define HEALTHASSESSMENT_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>

class HealthAssessment : public QDialog
{
    Q_OBJECT

public:
    explicit HealthAssessment(QDialog *parent = nullptr);
    ~HealthAssessment();

private slots:
    void onConfirmClicked();
    void onExitClicked();

private:
    // 布局
    QVBoxLayout *mainLayout;
    QGridLayout *inputLayout;
    QHBoxLayout *buttonLayout;

    // 标题
    QLabel *titleLabel;

    // 输入标签
    QLabel *heightLabel;
    QLabel *weightLabel;
    QLabel *heartRateLabel;
    QLabel *bloodPressureLabel;
    QLabel *lungCapacityLabel;

    // 输入框
    QTextEdit *heightEdit;
    QTextEdit *weightEdit;
    QTextEdit *heartRateEdit;
    QTextEdit *bloodPressureEdit;
    QTextEdit *lungCapacityEdit;

    // 单位标签
    QLabel *heightUnitLabel;
    QLabel *weightUnitLabel;
    QLabel *heartRateUnitLabel;
    QLabel *bloodPressureUnitLabel;
    QLabel *lungCapacityUnitLabel;

    // 按钮
    QPushButton *confirmButton;
    QPushButton *exitButton;

    // 弹簧
    QSpacerItem *verticalSpacerTop;
    QSpacerItem *verticalSpacerBottom;
    QSpacerItem *horizontalSpacerLeft;
    QSpacerItem *horizontalSpacerRight;
};

#endif // HEALTHASSESSMENT_H
