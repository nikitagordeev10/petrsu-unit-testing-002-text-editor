#ifndef LOADTEST_H
#define LOADTEST_H

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

#endif // LOADTEST_H