#include "viewprescription.h"
#include "ui_viewprescription.h"

ViewPrescription::ViewPrescription(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ViewPrescription)
{
    ui->setupUi(this);
}

ViewPrescription::~ViewPrescription()
{
    delete ui;
}
