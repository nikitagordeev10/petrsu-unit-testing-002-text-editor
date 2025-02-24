include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

HEADERS += load_tests.h \
        move_tests.h \
        mpweb_tests.h \
        rn_tests.h \
        save_tests.h \
        show_tests.h \
        showunderscores_tests.h \
        constants.h\
        ../app/common.h \
        ../app/text.h \
        ../app/_text.h

SOURCES += main.cpp \
    ../app/load.c \
    ../app/move.c \
    ../app/mpweb.c \
    ../app/rn.c \
    ../app/save.c \
    ../app/show.c \
    ../app/showunderscores.c \
    ../app/append_line.c \
    ../app/create_text.c \
    ../app/process_forward.c \
    ../app/remove_all.c


INCLUDEPATH += ../app

DISTFILES += \
    input/empty_file_input.txt \
    input/no_spaces_input.txt \
    input/unusual_spaces_input.txt \
    tests/input/input.txt
