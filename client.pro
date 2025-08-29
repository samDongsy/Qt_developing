QT       += core gui network widgets

TARGET = SmartMedicalClient
TEMPLATE = app

# 确保 SOURCES 变量中包含了 authmanager.cpp
SOURCES += \
    main.cpp \
    appmanager.cpp \
    authmanager.cpp \ # <--- 关键修正：请确保这一行存在且文件名大小写正确
    entry/roleselection/roleselectiondialog.cpp \
    entry/login/logindialog.cpp \
    entry/register/registerdialog.cpp \
    network/socketclient.cpp \
    doctorwindow.cpp \
    patientwindow.cpp \
    general/communication/communication.cpp \
    doctor/doctorinterface/doctorinterface.cpp \
    doctor/editcase/editcase.cpp \
    doctor/editprescription/editprescription.cpp \
    doctor/editprofile/doctorprofilepage.cpp \
    patient/healthassessment/healthassessment.cpp \
    patient/patientinterface/patientinterface.cpp \
    patient/registration/registration.cpp \
    patient/viewcase/viewcase.cpp \
    patient/viewdoctorinfo/viewdoctorinfo.cpp \
    patient/viewprescription/viewprescription.cpp \
    general/viewregistration/viewregistration.cpp \
    patient/editprofile/editprofile.cpp

# 确保 HEADERS 变量中包含了 authmanager.h
HEADERS += \
    appmanager.h \
    authmanager.h \ # <--- 确认这一行也存在
    entry/roleselection/roleselectiondialog.h \
    entry/login/logindialog.h \
    entry/register/registerdialog.h \
    network/socketclient.h \
    doctorwindow.h \
    patientwindow.h \
    general/communication/communication.h \
    doctor/doctorinterface/doctorinterface.h \
    doctor/editcase/editcase.h \
    doctor/editprescription/editprescription.h \
    doctor/editprofile/doctorprofilepage.h \
    patient/healthassessment/healthassessment.h \
    patient/patientinterface/patientinterface.h \
    patient/registration/registration.h \
    patient/viewcase/viewcase.h \
    patient/viewdoctorinfo/viewdoctorinfo.h \
    patient/viewprescription/viewprescription.h \
    general/viewregistration/viewregistration.h \
    patient/editprofile/editprofile.h

FORMS += \
    entry/roleselection/roleselectiondialog.ui \
    entry/login/logindialog.ui \
    entry/register/registerdialog.ui \
    doctorwindow.ui \
    patientwindow.ui \
    general/communication/communication.ui \
    doctor/doctorinterface/doctorinterface.ui \
    doctor/editcase/editcase.ui \
    doctor/editprescription/editprescription.ui \
    doctor/editprofile/doctorprofilepage.ui \
    patient/patientinterface/patientinterface.ui \
    patient/registration/registration.ui \
    patient/viewcase/viewcase.ui \
    patient/viewdoctorinfo/viewdoctorinfo.ui \
    patient/viewprescription/viewprescription.ui \
    general/viewregistration/viewregistration.ui \
    patient/editprofile/editprofile.ui

RESOURCES += \
    src/resources.qrc
