#ifndef EDITCASE_H
#define EDITCASE_H

#include <QDialog>

namespace Ui {
class EditCase;
}

class EditCase : public QDialog
{
    Q_OBJECT

public:
    explicit EditCase(QDialog *parent = nullptr);
    ~EditCase();

private:
    Ui::EditCase *ui;
};

#endif // EDITCASE_H
