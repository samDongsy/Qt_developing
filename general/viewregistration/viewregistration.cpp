#include "viewregistration.h"
#include "ui_viewregistration.h"

ViewRegistration::ViewRegistration(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ViewRegistration)
{
    ui->setupUi(this);
}

ViewRegistration::~ViewRegistration()
{
    delete ui;
}
