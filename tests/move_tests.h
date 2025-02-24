#ifndef MOVETEST_H
#define MOVETEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <iostream>
#include <fstream>

extern "C"{
#include "text.h"
#include "_text.h"
#include "common.h"
}

/* =================== constants ===================  */

char *lorem_input = INPUTDIR "/lorem_input.txt";
char *lorem_input_c = INPUTDIR "/lorem_input.c";
char *no_spaces_input = INPUTDIR "/no_spaces_input.txt";
char *empty_file_input = INPUTDIR "/empty_file_input.txt";
char *unusual_spaces_input = INPUTDIR "/unusual_spaces_input.txt";
char *fakefile = INPUTDIR "/fakefile.txt";
char *save_test_file = INPUTDIR "/save_test_file.txt";

/* ------------------- move.c -------------------  */

// Первая строка, выход за пределы текста влево (негативный)
TEST(TestMove, first_line_text_overflow_left)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, -10);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "|What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка, начало первого слова (позитивный)
TEST(TestMove, first_line_start_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, 0);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "|What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка, выход за пределы текста вправо (негативный)
TEST(TestMove, first_line_out_of_text_right)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, 100);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?|\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка строка, середина первого слова (позитивный)
TEST(TestMove, middle_line_middle_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 3);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lor|em Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Cредняя строка, конец второго слова (позитивный)
TEST(TestMove, middle_line_end_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 11);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum| has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Последняя строка, конец последнего слова (позитивный)
TEST(TestMove, last_line_end_of_last_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 5, 78);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing|.\n");
    remove_all(txt);
}

// Последняя строка, выход за пределы текста вправо (негативный)
TEST(TestMove, last_line_overflow_right)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 5, 100);
    mpweb(txt);

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

// После-последняя строка текста, выход за границы текста вниз (негативный)
TEST(TestMove, after_last_line_overflow_down)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 10, 3);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It| was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

#endif // MOVETEST_H
