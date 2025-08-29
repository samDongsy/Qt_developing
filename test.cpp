#include "doctor/doctorinterface/doctorinterface.h"
#include "patient/patientinterface/patientinterface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DoctorInterface w;
    PatientInterface P;
    w.show();
    P.show();
    return a.exec();
}
