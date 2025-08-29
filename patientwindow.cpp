#include "patientwindow.h"
#include "ui_patientwindow.h"

PatientWindow::PatientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatientWindow) {
    ui->setupUi(this);
}

PatientWindow::~PatientWindow() {
    delete ui;
}
