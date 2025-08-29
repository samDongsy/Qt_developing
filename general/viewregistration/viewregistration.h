#ifndef VIEWREGISTRATION_H
#define VIEWREGISTRATION_H

#include <QDialog>

namespace Ui {
class ViewRegistration;
}

class ViewRegistration : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRegistration(QDialog *parent = nullptr);
    ~ViewRegistration();

private:
    Ui::ViewRegistration *ui;
};

#endif // VIEWREGISTRATION_H
