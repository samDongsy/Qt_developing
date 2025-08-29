#ifndef DOCTORPROFILEPAGE_H
#define DOCTORPROFILEPAGE_H

#include <QWidget>

// 包含由.ui文件生成的类的声明
QT_BEGIN_NAMESPACE
namespace Ui { class DoctorProfilePage; }
QT_END_NAMESPACE

class DoctorProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorProfilePage(QWidget *parent = nullptr);
    ~DoctorProfilePage();

private slots:
    void toggleEditMode(bool editable);
    void onSaveClicked(); // 新增一个槽函数用于保存逻辑

private:
    void setupConnections();
    void populateTimeCombos(); // 将填充时间的逻辑独立出来

    Ui::DoctorProfilePage *ui; // 指向自动生成的UI类的指针

    // 用一个列表存储所有需要切换状态的控件
    QList<QWidget*> inputWidgets;
};

#endif // DOCTORPROFILEPAGE_H
