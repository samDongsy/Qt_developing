#include "editcase.h"
#include "ui_editcase.h"

EditCase::EditCase(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::EditCase)
{
    ui->setupUi(this);
}

EditCase::~EditCase()
{
    delete ui;
}
