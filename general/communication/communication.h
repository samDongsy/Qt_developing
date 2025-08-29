#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QDialog>

namespace Ui {
class Communication;
}

class Communication : public QDialog
{
    Q_OBJECT

public:
    explicit Communication(QDialog *parent = nullptr);
    ~Communication();

private:
    Ui::Communication *ui;
};

#endif // COMMUNICATION_H
