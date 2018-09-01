TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    employee.cpp \
    technician.cpp \
    manager.cpp \
    salesman.cpp \
    salesmanager.cpp

HEADERS += \
    employee.h \
    technician.h \
    manager.h \
    salesman.h \
    salesmanager.h
