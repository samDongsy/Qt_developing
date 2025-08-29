#ifndef EDITPRESCRIPTION_H
#define EDITPRESCRIPTION_H

#include <QDialog>

namespace Ui {
class EditPrescription;
}

class EditPrescription : public QDialog
{
    Q_OBJECT

public:
    explicit EditPrescription(QDialog *parent = nullptr);
    ~EditPrescription();

private:
    Ui::EditPrescription *ui;
};

#endif // EDITPRESCRIPTION_H
