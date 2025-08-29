#include "editprescription.h"
#include "ui_editprescription.h"

EditPrescription::EditPrescription(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrescription)
{
    ui->setupUi(this);
}

EditPrescription::~EditPrescription()
{
    delete ui;
}
