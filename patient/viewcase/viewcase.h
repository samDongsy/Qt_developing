#ifndef VIEWCASE_H
#define VIEWCASE_H

#include <QDialog>

namespace Ui {
class ViewCase;
}

class ViewCase : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCase(QDialog *parent = nullptr);
    ~ViewCase();

private:
    Ui::ViewCase *ui;
};

#endif // VIEWCASE_H
