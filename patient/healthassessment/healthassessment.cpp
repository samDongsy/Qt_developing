#include "healthassessment.h"
#include <QFont>
#include <QMessageBox>
#include <QDebug>
#include <QSpacerItem>

HealthAssessment::HealthAssessment(QDialog *parent) : QDialog(parent)
{
    // 设置窗口标题和大小
    setWindowTitle("健康评估");
    resize(1600, 1200); // 设置窗口大小为1600x1200

    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(30); // 增加间距

    // 添加上方垂直弹簧
    verticalSpacerTop = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacerTop);

    // 创建标题
    titleLabel = new QLabel("健康评估界面");
    QFont titleFont("黑体", 24, QFont::Bold); // 增大字体
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { padding: 20px; }"); // 增加内边距
    mainLayout->addWidget(titleLabel);

    // 创建输入布局
    inputLayout = new QGridLayout();
    inputLayout->setVerticalSpacing(40); // 增加垂直间距
    inputLayout->setHorizontalSpacing(30); // 增加水平间距
    mainLayout->addLayout(inputLayout);

    // 设置行和列的拉伸因子，使内容均匀分布
    for (int i = 0; i < 5; ++i) {
        inputLayout->setRowStretch(i, 1);
    }
    inputLayout->setColumnStretch(0, 1);
    inputLayout->setColumnStretch(1, 2);
    inputLayout->setColumnStretch(2, 1);

    // 创建标签和输入框
    heightLabel = new QLabel("身高");
    weightLabel = new QLabel("体重");
    heartRateLabel = new QLabel("心率");
    bloodPressureLabel = new QLabel("血压");
    lungCapacityLabel = new QLabel("肺活量");

    // 设置标签字体
    QFont labelFont("宋体", 16); // 增大字体
    heightLabel->setFont(labelFont);
    weightLabel->setFont(labelFont);
    heartRateLabel->setFont(labelFont);
    bloodPressureLabel->setFont(labelFont);
    lungCapacityLabel->setFont(labelFont);

    // 创建输入框
    heightEdit = new QTextEdit();
    weightEdit = new QTextEdit();
    heartRateEdit = new QTextEdit();
    bloodPressureEdit = new QTextEdit();
    lungCapacityEdit = new QTextEdit();

    // 设置输入框高度和字体
    QFont editFont("宋体", 14); // 增大字体
    int editHeight = 80; // 增加高度

    heightEdit->setFixedHeight(editHeight);
    heightEdit->setFont(editFont);

    weightEdit->setFixedHeight(editHeight);
    weightEdit->setFont(editFont);

    heartRateEdit->setFixedHeight(editHeight);
    heartRateEdit->setFont(editFont);

    bloodPressureEdit->setFixedHeight(editHeight);
    bloodPressureEdit->setFont(editFont);

    lungCapacityEdit->setFixedHeight(editHeight);
    lungCapacityEdit->setFont(editFont);

    // 创建单位标签
    heightUnitLabel = new QLabel("(cm)");
    weightUnitLabel = new QLabel("(kg)");
    heartRateUnitLabel = new QLabel("(次/分钟)");
    bloodPressureUnitLabel = new QLabel("(mmHg, 如:120/80)");
    lungCapacityUnitLabel = new QLabel("(ml)");

    // 设置单位标签字体
    QFont unitFont("宋体", 14); // 增大字体
    QPalette unitPalette;
    unitPalette.setColor(QPalette::WindowText, Qt::gray);

    heightUnitLabel->setFont(unitFont);
    heightUnitLabel->setPalette(unitPalette);
    weightUnitLabel->setFont(unitFont);
    weightUnitLabel->setPalette(unitPalette);
    heartRateUnitLabel->setFont(unitFont);
    heartRateUnitLabel->setPalette(unitPalette);
    bloodPressureUnitLabel->setFont(unitFont);
    bloodPressureUnitLabel->setPalette(unitPalette);
    lungCapacityUnitLabel->setFont(unitFont);
    lungCapacityUnitLabel->setPalette(unitPalette);

    // 将标签、输入框和单位标签添加到网格布局
    inputLayout->addWidget(heightLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    inputLayout->addWidget(heightEdit, 0, 1);
    inputLayout->addWidget(heightUnitLabel, 0, 2, Qt::AlignLeft | Qt::AlignVCenter);

    inputLayout->addWidget(weightLabel, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    inputLayout->addWidget(weightEdit, 1, 1);
    inputLayout->addWidget(weightUnitLabel, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    inputLayout->addWidget(heartRateLabel, 2, 0, Qt::AlignRight | Qt::AlignVCenter);
    inputLayout->addWidget(heartRateEdit, 2, 1);
    inputLayout->addWidget(heartRateUnitLabel, 2, 2, Qt::AlignLeft | Qt::AlignVCenter);

    inputLayout->addWidget(bloodPressureLabel, 3, 0, Qt::AlignRight | Qt::AlignVCenter);
    inputLayout->addWidget(bloodPressureEdit, 3, 1);
    inputLayout->addWidget(bloodPressureUnitLabel, 3, 2, Qt::AlignLeft | Qt::AlignVCenter);

    inputLayout->addWidget(lungCapacityLabel, 4, 0, Qt::AlignRight | Qt::AlignVCenter);
    inputLayout->addWidget(lungCapacityEdit, 4, 1);
    inputLayout->addWidget(lungCapacityUnitLabel, 4, 2, Qt::AlignLeft | Qt::AlignVCenter);

    // 添加下方垂直弹簧
    verticalSpacerBottom = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacerBottom);

    // 创建按钮布局
    buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    // 添加左侧水平弹簧，使按钮靠右
    horizontalSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(horizontalSpacerLeft);

    // 创建按钮
    confirmButton = new QPushButton("确定");
    exitButton = new QPushButton("退出");

    // 设置按钮大小和字体
    confirmButton->setFixedSize(150, 60); // 增大按钮
    exitButton->setFixedSize(150, 60); // 增大按钮

    QFont buttonFont("宋体", 16); // 增大字体
    confirmButton->setFont(buttonFont);
    exitButton->setFont(buttonFont);

    // 将按钮添加到布局
    QHBoxLayout *buttonSubLayout = new QHBoxLayout();
    buttonSubLayout->setSpacing(30); // 按钮间距
    buttonSubLayout->addWidget(confirmButton);
    buttonSubLayout->addWidget(exitButton);

    buttonLayout->addLayout(buttonSubLayout);

    // 添加右侧水平弹簧
    horizontalSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    buttonLayout->addItem(horizontalSpacerRight);

    // 连接按钮信号和槽
    connect(confirmButton, &QPushButton::clicked, this, &HealthAssessment::onConfirmClicked);
    connect(exitButton, &QPushButton::clicked, this, &HealthAssessment::onExitClicked);
}

HealthAssessment::~HealthAssessment()
{
    // 自动删除所有子对象，无需手动删除
}

void HealthAssessment::onConfirmClicked()
{
    // 获取输入的值
    QString height = heightEdit->toPlainText();
    QString weight = weightEdit->toPlainText();
    QString heartRate = heartRateEdit->toPlainText();
    QString bloodPressure = bloodPressureEdit->toPlainText();
    QString lungCapacity = lungCapacityEdit->toPlainText();

    // 这里可以添加健康评估的逻辑
    qDebug() << "健康评估数据:";
    qDebug() << "身高:" << height << "cm";
    qDebug() << "体重:" << weight << "kg";
    qDebug() << "心率:" << heartRate << "次/分钟";
    qDebug() << "血压:" << bloodPressure << "mmHg";
    qDebug() << "肺活量:" << lungCapacity << "ml";

    QMessageBox::information(this, "提示", "健康评估数据已提交!");
}

void HealthAssessment::onExitClicked()
{
    this->close();
}
