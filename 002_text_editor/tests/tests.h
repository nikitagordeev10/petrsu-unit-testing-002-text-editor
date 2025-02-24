#ifndef EQTEST_H
#define EQTEST_H

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

/* ------------------- load.c -------------------  */

// Загрузка txt файла (позитивный)
TEST(TestLoad, loading_txt_file)
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

// Загрузка c файла (позитивный)
TEST(TestLoad, loading_c_file)
{
    text txt = create_text();
    load(txt, lorem_input_c);

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

// Загрузка несуществующего файла (негативный)
TEST(TestLoad, non_existent_file) {
    text new_txt = create_text();

    std::string output;
    testing::internal::CaptureStdout();

    load(new_txt, "fakefile.txt");
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "The file fakefile.txt cannot be opened\n");
}

// Загрузка не текстового файла (негативный)
TEST(TestLoad, not_text_file) {
    text new_txt = create_text();

    std::string output;
    testing::internal::CaptureStdout();

    load(new_txt, "not_text_file.png");
    output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "The file not_text_file.png cannot be opened\n");
}

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

/* ------------------- save.c -------------------  */
// Чтение, изменение и сохранение файла (позитивный)
TEST (TestSave, default_save)
{
    text txt = create_text();
    load(txt, lorem_input);
    append_line(txt, "Example text in line.");

    testing::internal::CaptureStdout();
    save(txt, "save_test_file.txt");
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Save file successeed!\n");

    remove_all(txt);
}

// Не указан файл на открытие (негативный)
TEST (TestSave, emply_txt_structure)
{
    text txt = create_text();

    testing::internal::CaptureStderr();
    save(txt, "test_save.txt");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "The text doesn't exist\n");
    remove_all(txt);
}

// Неверно указан формат сохранения save(NULL, "test_save.txt"); (негативный)
TEST (TestSave, invalid_save_format)
{
    text txt = create_text();
    load(txt, lorem_input);

    testing::internal::CaptureStdout();
    save(NULL, "invalid_save_format.txt");
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");

    remove_all(txt);
}

// Добавление строк в неоткрытый файл append_line(txt, "Example text."); (позитивный)
TEST (TestSave, not_open_file)
{
    text txt = create_text();
    append_line(txt, "Example text in line.");

    testing::internal::CaptureStdout();
    save(txt, "not_open_file.txt");
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Save file successeed!\n");

    remove_all(txt);
}

// Сохранеие без указания места save(txt, NULL); (негативный)
TEST (TestSave, no_location)
{
    text txt = create_text();
    append_line(txt, "Example text in line.");

    testing::internal::CaptureStdout();
    save(txt, NULL);
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");

    remove_all(txt);
}

// Сохранение без набора имени save(txt, ""); (негативный)
TEST (TestSave, no_name)
{
    text txt = create_text();
    append_line(txt, "Example text in line.");

    testing::internal::CaptureStdout();
    save(txt, "");
    remove_all(txt);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");

    remove_all(txt);
}

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

/* ------------------- showunderscores.c -------------------  */

// Файл в несколько строк с обычными пробелами (позитивный)
TEST(TestShowunderscores, real_file)
{
    text txt = create_text();
    load(txt, lorem_input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "What_is_Lorem_Ipsum?\n"
                      "Lorem_Ipsum_is_simply_dummy_text_of_the_printing_and_typesetting_industry.\n"
                      "Lorem_Ipsum_has_been_the_industry's_standard_dummy_text_ever_since_the_1500s.\n"
                      "It_has_survived_not_only_five_centuries,_but_also_the_leap_into_electronic_typesetting.\n"
                      "It_was_popularised_in_the_1960s_with_the_release_of_Letraset_sheets_containing.|\n");
    remove_all(txt);
}

// Файл в одну строку без пробелов (позитивный)
TEST(TestShowunderscores, without_spaces)
{
    text txt = create_text();
    load(txt, no_spaces_input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Itwaspopularisedinthe1960swiththereleaseofLetrasetsheetscontaining.|\n");
    remove_all(txt);
}

// Файл в одну строку с пробелами длины 5 символов (если уменьшить до 4 => табами) (позитивный)
TEST(TestShowunderscores, unusual_spaces)
{
    text txt = create_text();
    load(txt, unusual_spaces_input);

    testing::internal::CaptureStdout();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Lorem_____Ipsum_____is_____simply_____dummy_____text_____of_____the_____printing_____and_____typesetting_____industry.|\n");
    remove_all(txt);
}

// Не указан файл (негативный)
TEST(TestShowunderscores, empty)
{
    text txt = create_text();

    testing::internal::CaptureStderr();
    showunderscores(txt);
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "There are already no any lines in the text!\n");
    remove_all(txt);
}

#endif // EQTEST_H
