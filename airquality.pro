QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    network/activationFunctions/activationfunction.cpp \
    fileUtils/airqualitydata.cpp \
    fileUtils/csvparser.cpp \
    geneticalgorithm.cpp \
    main.cpp \
    windows/mainwindow.cpp \
    network/neuralnetwork.cpp \
    network/neuron.cpp \
    network/activationFunctions/reluactivationfunction.cpp \
    network/activationFunctions/sigmoidactivationfunction.cpp \
    windows/testwidget.cpp \
    windows/trainingwidget.cpp \
    fileUtils/weightserializer.cpp

HEADERS += \
    network/activationFunctions/activationfunction.h \
    fileUtils/airqualitydata.h \
    fileUtils/csvparser.h \
    geneticalgorithm.h \
    windows/mainwindow.h \
    network/neuralnetwork.h \
    network/neuron.h \
    network/activationFunctions/reluactivationfunction.h \
    network/activationFunctions/sigmoidactivationfunction.h \
    windows/testwidget.h \
    windows/trainingwidget.h \
    fileUtils/weightserializer.h

FORMS += \
    mainwindow.ui \
    testwidget.ui \
    trainingwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
