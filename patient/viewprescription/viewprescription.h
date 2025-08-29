#ifndef VIEWPRESCRIPTION_H
#define VIEWPRESCRIPTION_H

#include <QDialog>

namespace Ui {
class ViewPrescription;
}

class ViewPrescription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPrescription(QDialog *parent = nullptr);
    ~ViewPrescription();

private:
    Ui::ViewPrescription *ui;
};

#endif // VIEWPRESCRIPTION_H
