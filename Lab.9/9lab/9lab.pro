include(gtest_dependency.pri)

INCLUDEPATH += C:\Users\ThRuW\Downloads\Lab9_Project_for_tests

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../Downloads/Lab9_Project_for_tests/IKeypad.h \
        ../../Downloads/Lab9_Project_for_tests/ILatch.h \
        ../../Downloads/Lab9_Project_for_tests/lockcontroller.h \
        tst_9labtest.h

SOURCES += \
        ../../Downloads/Lab9_Project_for_tests/lockcontroller.cpp \
        main.cpp
