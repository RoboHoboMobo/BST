QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

prefix = $$PWD/../Sources

INCLUDEPATH += $$prefix

SOURCES += $$prefix/BinarySearchTree.cpp \
    tst_bst.cpp

HEADERS += $$prefix/BinarySearchTree.h \
    $$prefix/BinarySearchTree.tpp
