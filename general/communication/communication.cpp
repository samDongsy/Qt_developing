#include "communication.h"
#include "ui_communication.h"

Communication::Communication(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Communication)
{
    ui->setupUi(this);
}

Communication::~Communication()
{
    delete ui;
}
