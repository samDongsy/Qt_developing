#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}
