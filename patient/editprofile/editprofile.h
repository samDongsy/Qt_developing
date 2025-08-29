#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class EditProfile;
}

class EditProfile : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfile(QDialog *parent = nullptr);
    ~EditProfile();

signals:
    // 保存成功后抛出，父界面可连接此信号接收数据并持久化
    void profileSaved(const QString& name,
                      const QDate& birthDate,
                      const QString& idNumber,
                      const QString& phone,
                      const QString& email);

private slots:
    void onConfirm();
    void onBack();
    void onTextEdited(const QString&);
    // 新增：onDateChanged 槽函数声明（对应日期编辑框变化时清除错误高亮）
    void onDateChanged(const QDate&);

private:
    Ui::EditProfile *ui;

    void initUi();
    void initValidators();
    void clearErrorStyles();
    void markError(QWidget* w, bool on);

    bool validateAll(QStringList* errorsOut = nullptr, QWidget** firstInvalidWidget = nullptr);
    bool validateName(QString* errorOut = nullptr);
    bool validatePhone(QString* errorOut = nullptr);
    bool validateEmail(QString* errorOut = nullptr);
    bool validateIdNumber(QString* errorOut = nullptr);
};

#endif // EDITPROFILE_H
