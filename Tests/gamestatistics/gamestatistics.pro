QT += testlib
QT += gui
QT += widgets gui network core multimedia

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../Game\
                ../../Course/CourseLib\
                ../../Course/CourseLib/actors\
                ../../Course/CourseLib/core\
                ../../Course/CourseLib/errors\
                ../../Course/CourseLib/graphics\
                ../../Course/CourseLib/interfaces\
                ../../Course/CourseLib/offlinedata

DEPENDPATH  += ../../Game\
                ../../Course/CourseLib\
                ../../Course/CourseLib/actors\
                ../../Course/CourseLib/core\
                ../../Course/CourseLib/errors\
                ../../Course/CourseLib/graphics\
                ../../Course/CourseLib/interfaces\
                ../../Course/CourseLib/offlinedata

SOURCES +=  tst_gamestatistics.cpp\
    ../../Game/gamestatistics.cpp

HEADERS +=  ../../Game/gamestatistics.h
