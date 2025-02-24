#ifndef SHOWTEST_H
#define SHOWTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
}
#include "constants.h"
/* ------------------- show.c -------------------  */

// Файл в несколько строк, курсор в конце (позитивный)
TEST(TestShow, default_position)
{
    text txt = create_text();
    load(txt, lorem_input);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.|\n");

    remove_all(txt);
}

// Файл в несколько строк, курсор в второго слова (позитивный)
TEST(TestShow, moved_position)
{
    text txt = create_text();
    load(txt, lorem_input);
    move(txt, 2, 2);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lo|rem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");

    remove_all(txt);
}

// Файл в несколько строк, курсор за границами текста вправо (негативный)
TEST(TestShow, position_outside_left)
{
    text txt = create_text();
    load(txt, lorem_input);
    move(txt, 2, 100);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.|\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");

    remove_all(txt);
}

// Файл в несколько строк, курсор за границами текста влево (негативный)
TEST(TestShow, position_outside_right)
{
    text txt = create_text();
    load(txt, lorem_input);
    move(txt, 2, -10);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "|Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");

    remove_all(txt);
}

// Не указан файл (негативный)
TEST(TestShow, no_text)
{
    text txt = create_text();

    testing::internal::CaptureStderr();
    show(txt);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}

#endif // SHOWTEST_H
