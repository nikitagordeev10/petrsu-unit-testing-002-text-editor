#ifndef SHOWUNDERSCORESTEST_H
#define SHOWUNDERSCORESTEST_H

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

#endif // SHOWUNDERSCORESTEST_H