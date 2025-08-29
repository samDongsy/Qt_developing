#ifndef VIEWDOCTORINFO_H
#define VIEWDOCTORINFO_H

#include <QDialog>

namespace Ui {
class ViewDoctorInfo;
}

class ViewDoctorInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDoctorInfo(QDialog *parent = nullptr);
    ~ViewDoctorInfo();

private:
    Ui::ViewDoctorInfo *ui;
};

#endif // VIEWDOCTORINFO_H
