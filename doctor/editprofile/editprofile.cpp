#include "editprofile.h"
#include "ui_editprofile.h"

EditProfile::EditProfile(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfile)
{
    ui->setupUi(this);
}

EditProfile::~EditProfile()
{
    delete ui;
}
