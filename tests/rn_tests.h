#ifndef RNTEST_H
#define RNTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
#include "constants.h"
}

/* ------------------- rn.c -------------------  */

// Позиция выше первой строки текста, выход за границы текста вверх, удаление второй строки. (негативный)
TEST(TestRemovenext, position_above_first_line_of_text) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, -10, 0);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "|What is Lorem Ipsum?\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Позиция первая строка. Удаление второй строки. (позитивный)
TEST(TestRemovenext, first_line_of_text) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, 5);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What |is Lorem Ipsum?\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Позиция вторая строка. Удаление третьей строки. (позитивный)
TEST(TestRemovenext, position_second_line) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 2, 0);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "|Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Позиция предпоследняя строка. Удаление последней строки.(позитивный)
TEST(TestRemovenext, before_last_line) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 4, 0);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "|It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n"  );
    remove_all(txt);
}

// Позиция последняя строка. Удаление послепоследней(несуществующей) строки. (негативный)
TEST(TestRemovenext, last_line) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 5, 0);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "|It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Позиция после-последняя строка. Удаление после-после-последней(несуществующей) строки. (негативный)
TEST(TestRemovenext, after_last_line) {
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 15, 0);
    rn(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "|It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Удаление строки в пустом файле (негативный)
TEST(TestRemovenext, empty_file) {
    text txt = create_text();
    load(txt, empty_file_input);

    rn(txt);

    testing::internal::CaptureStderr();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}

#endif // MPWEBTEST_H
