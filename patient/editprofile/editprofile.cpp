#include "editprofile.h"
#include "ui_editprofile.h"

#include <QDate>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>

EditProfile::EditProfile(QDialog *parent)
    : QDialog(parent),
      ui(new Ui::EditProfile)
{
    ui->setupUi(this);
    initUi();
    initValidators();

    // 连接信号槽，使用Qt5.9兼容的语法
    connect(ui->pushButtonConfirm, SIGNAL(clicked()), this, SLOT(onConfirm()));
    connect(ui->pushButtonBack,    SIGNAL(clicked()), this, SLOT(onBack()));

    // 编辑时清除错误高亮
    connect(ui->lineEditName,     SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    connect(ui->lineEditIdNumber, SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    connect(ui->lineEditPhone,    SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    connect(ui->lineEditEmail,    SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    connect(ui->dateEditBirth,    SIGNAL(dateChanged(QDate)), this, SLOT(onDateChanged(QDate)));
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::initUi()
{
    setWindowTitle(QStringLiteral("编辑个人信息"));
    setMinimumWidth(420);

    // 出生日期范围：1900-01-01 至今日
    ui->dateEditBirth->setDisplayFormat("yyyy-MM-dd");
    ui->dateEditBirth->setCalendarPopup(true);
    ui->dateEditBirth->setMinimumDate(QDate(1900, 1, 1));
    ui->dateEditBirth->setMaximumDate(QDate::currentDate());
    ui->dateEditBirth->setDate(QDate::currentDate());
}

void EditProfile::initValidators()
{
    // 姓名：中文及“·”，长度 2-20。Qt5.9使用\u表示Unicode
    {
        QRegularExpression re("^[\\u4e00-\\u9fa5·]{0,20}$");
        ui->lineEditName->setValidator(new QRegularExpressionValidator(re, ui->lineEditName));
    }

    // 身份证：允许输入阶段，最终 18 位，末位可 X/x
    {
        QRegularExpression re("^[0-9]{0,17}[0-9Xx]?$");
        ui->lineEditIdNumber->setValidator(new QRegularExpressionValidator(re, ui->lineEditIdNumber));
    }

    // 手机号：仅数字，最多 11 位
    {
        QRegularExpression re("^\\d{0,11}$");
        ui->lineEditPhone->setValidator(new QRegularExpressionValidator(re, ui->lineEditPhone));
    }
}

void EditProfile::onConfirm()
{
    QStringList errors;
    QWidget* firstInvalid = nullptr;
    if (!validateAll(&errors, &firstInvalid)) {
        QMessageBox::warning(this, QStringLiteral("校验失败"),
                             QStringLiteral("请修正以下内容：\n• ") + errors.join(QStringLiteral("\n• ")));
        if (firstInvalid) firstInvalid->setFocus();
        return;
    }

    // 校验通过，发出信号，关闭对话框
    emit profileSaved(ui->lineEditName->text().trimmed(),
                      ui->dateEditBirth->date(),
                      ui->lineEditIdNumber->text().trimmed().toUpper(),
                      ui->lineEditPhone->text().trimmed(),
                      ui->lineEditEmail->text().trimmed());
    accept();
}

void EditProfile::onBack()
{
    reject();
}

void EditProfile::onTextEdited(const QString&)
{
    if (auto le = qobject_cast<QLineEdit*>(sender())) {
        markError(le, false);
    }
}

void EditProfile::onDateChanged(const QDate&)
{
    markError(ui->dateEditBirth, false);
}

void EditProfile::clearErrorStyles()
{
    markError(ui->lineEditName, false);
    markError(ui->lineEditIdNumber, false);
    markError(ui->lineEditPhone, false);
    markError(ui->lineEditEmail, false);
    markError(ui->dateEditBirth, false);
}

void EditProfile::markError(QWidget* w, bool on)
{
    if (!w) return;
    if (on) {
        w->setStyleSheet("QLineEdit, QDateEdit { border:1px solid #d93c3c; border-radius:4px; }");
    } else {
        w->setStyleSheet("");
    }
}

bool EditProfile::validateAll(QStringList* errorsOut, QWidget** firstInvalidWidget)
{
    clearErrorStyles();
    QString msg;
    bool ok = true;

    if (!validateName(&msg)) {
        ok = false;
        if (errorsOut) errorsOut->append(QStringLiteral("姓名：") + msg);
        markError(ui->lineEditName, true);
        if (firstInvalidWidget && !*firstInvalidWidget) *firstInvalidWidget = ui->lineEditName;
    }
    if (!validateIdNumber(&msg)) {
        ok = false;
        if (errorsOut) errorsOut->append(QStringLiteral("身份证号：") + msg);
        markError(ui->lineEditIdNumber, true);
        if (firstInvalidWidget && !*firstInvalidWidget) *firstInvalidWidget = ui->lineEditIdNumber;
    }
    if (!validatePhone(&msg)) {
        ok = false;
        if (errorsOut) errorsOut->append(QStringLiteral("手机号：") + msg);
        markError(ui->lineEditPhone, true);
        if (firstInvalidWidget && !*firstInvalidWidget) *firstInvalidWidget = ui->lineEditPhone;
    }
    if (!validateEmail(&msg)) {
        ok = false;
        if (errorsOut) errorsOut->append(QStringLiteral("邮箱：") + msg);
        markError(ui->lineEditEmail, true);
        if (firstInvalidWidget && !*firstInvalidWidget) *firstInvalidWidget = ui->lineEditEmail;
    }

    return ok;
}

bool EditProfile::validateName(QString* errorOut)
{
    const QString name = ui->lineEditName->text().trimmed();
    if (name.isEmpty()) {
        if (errorOut) *errorOut = QStringLiteral("不能为空");
        return false;
    }
    // Qt5.9使用\u表示Unicode范围
    static const QRegularExpression re("^[\\u4e00-\\u9fa5·]{2,20}$");
    if (!re.match(name).hasMatch()) {
        if (errorOut) *errorOut = QStringLiteral("仅限中文（可含“·”），长度 2-20 个字符");
        return false;
    }
    return true;
}

bool EditProfile::validatePhone(QString* errorOut)
{
    const QString phone = ui->lineEditPhone->text().trimmed();
    static const QRegularExpression re("^1[3-9]\\d{9}$");
    if (!re.match(phone).hasMatch()) {
        if (errorOut) *errorOut = QStringLiteral("须为大陆手机号，1[3-9] 开头共 11 位数字");
        return false;
    }
    return true;
}

bool EditProfile::validateEmail(QString* errorOut)
{
    const QString email = ui->lineEditEmail->text().trimmed();
    // 简化的常用邮箱正则
    static const QRegularExpression re(
        "^(?=.{6,254}$)[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$",
        QRegularExpression::CaseInsensitiveOption);
    if (!re.match(email).hasMatch()) {
        if (errorOut) *errorOut = QStringLiteral("邮箱格式不正确");
        return false;
    }
    return true;
}

bool EditProfile::validateIdNumber(QString* errorOut)
{
    QString id = ui->lineEditIdNumber->text().trimmed().toUpper();
    // 18位，地区码(1-9开头)6 + 年(月日) + 顺序码3 + 校验位
    static const QRegularExpression re(
        "^[1-9]\\d{5}(19\\d{2}|20\\d{2})(0[1-9]|1[0-2])"
        "(0[1-9]|[12]\\d|3[01])\\d{3}[0-9X]$");
    if (!re.match(id).hasMatch()) {
        if (errorOut) *errorOut = QStringLiteral("须为 18 位，最后一位可为 X，且年月日位合法");
        return false;
    }

    // 校验码算法
    static const int weights[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    static const char checkMap[12] = {'1','0','X','9','8','7','6','5','4','3','2'};

    int sum = 0;
    for (int i = 0; i < 17; ++i) {
        int d = id.at(i).digitValue();
        if (d < 0) {
            if (errorOut) *errorOut = QStringLiteral("前 17 位必须为数字");
            return false;
        }
        sum += d * weights[i];
    }
    int mod = sum % 11;
    const QChar expect = QChar(checkMap[mod]);
    const QChar last = id.at(17);
    if (last != expect) {
        if (errorOut) *errorOut = QStringLiteral("校验位不正确，应为 %1").arg(expect);
        return false;
    }

    return true;
}
