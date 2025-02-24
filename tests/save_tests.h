#ifndef SAVETEST_H
#define SAVETEST_H

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

#endif // SAVETEST_H
