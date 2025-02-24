#ifndef MPWEBTEST_H
#define MPWEBTEST_H

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
/* ------------------- mpweb.c -------------------  */

// Выше первой строки текста, выход за границы текста вверх (негативный)
TEST(TestMpweb, negative_line_above_start_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, -10, -10);
    mpweb(txt);

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

// Первая строка выход за пределы текста влево (негативный)
TEST(TestMpweb, first_line_text_overflow_left)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 2, -2);
    mpweb(txt);

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

// Первая строка, начало первого слова (позитивный)
TEST(TestMpweb, first_line_start_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, 0);
    mpweb(txt);

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

// Первая строка, середина первого слова (позитивный)
TEST(TestMpweb, first_line_middle_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 2);
    mpweb(txt);

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

// Первая строка, конец первого слова (позитивный)
TEST(TestMpweb, first_line_end_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 0, 4);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What| is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка начало второго слова (позитивный)
TEST(TestMpweb, first_line_beginning_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 5);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What| is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка середина второго слова (позитивный)
TEST(TestMpweb, first_line_middle_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 6);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What| is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка конец второго слова (позитивный)
TEST(TestMpweb, first_line_end_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 7);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is| Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка середина последнего слова (позитивный)
TEST(TestMpweb, first_line_middle_of_last_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 16);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem| Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка конец последнего слова (позитивный)
TEST(TestMpweb, first_line_end_of_last_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 19);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum|?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Первая строка курсор после знака препинания "вопрос" (позитивный)
TEST(TestMpweb, first_line_after_punctuation_mark_question)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 20);
    mpweb(txt);

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

// Первая строка курсор после знака препинания "точка" (позитивный)
TEST(TestMpweb, first_line_after_punctuation_point_dot)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 2, 75);
    mpweb(txt);

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

// Первая строка выход за пределы текста вправо (негативный)
TEST(TestMpweb, first_line_out_of_text_right)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 1, 100);
    mpweb(txt);

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

// Средняя строка начало первого слова (позитивный)
TEST(TestMpweb, middle_line_beginning_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 0);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "|Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка, середина первого слова (позитивный)
TEST(TestMpweb, middle_line_middle_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 3);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "|Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка, конец первого слова (позитивный)
TEST(TestMpweb, middle_line_end_of_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 5);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem| Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка, начало второго слова (позитивный)
TEST(TestMpweb, middle_of_text_first_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 6);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem| Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка, середина второго слова (позитивный)
TEST(TestMpweb, middle_line_middle_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 10);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem| Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

// Средняя строка, конец второго слова (позитивный)
TEST(TestMpweb, middle_line_end_of_second_word)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 3, 11);
    mpweb(txt);

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

// Ниже последней строки текста, выход за границы текста вниз (негативный)
TEST(TestMpweb, below_the_last_line_of_text)
{
    text txt = create_text();
    load(txt, lorem_input);

    move(txt, 6, 11);
    mpweb(txt);

    testing::internal::CaptureStdout();
    show(txt);
    std::string output = testing::internal::GetCapturedStdout();


    EXPECT_EQ(output, "What is Lorem Ipsum?\n"
                      "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n"
                      "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.\n"
                      "It has survived not only five centuries, but also the leap into electronic typesetting.\n"
                      "It was| popularised in the 1960s with the release of Letraset sheets containing.\n");
    remove_all(txt);
}

#endif // MPWEBTEST_H
