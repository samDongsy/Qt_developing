#include "viewdoctorinfo.h"
#include "ui_viewdoctorinfo.h"

ViewDoctorInfo::ViewDoctorInfo(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ViewDoctorInfo)
{
    ui->setupUi(this);
}

ViewDoctorInfo::~ViewDoctorInfo()
{
    delete ui;
}
