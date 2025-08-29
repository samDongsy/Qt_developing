#include "viewcase.h"
#include "ui_viewcase.h"

ViewCase::ViewCase(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ViewCase)
{
    ui->setupUi(this);
}

ViewCase::~ViewCase()
{
    delete ui;
}
