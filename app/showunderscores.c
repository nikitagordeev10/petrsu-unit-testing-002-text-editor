/**
 * showunderscores.c -- реализует команду вывода хранимого текста на экран c заменой пробелов символом подчеркивания
 *
 * Copyright (c) 2022, Nikita Gordeev <gordeev@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "common.h"
#include "_text.h"
#include "text.h"

static void showunderscores_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран c заменой пробелов символом подчеркивания
 */
void showunderscores(text txt)
{
    /* Применяем функцию showunderscores_line к каждой строке текста */
    process_forward(txt, showunderscores_line, NULL);
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void showunderscores_line(int index, char *contents, int cursor, void *data)
{
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);

    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);

    int data_len = (int)strnlen(contents, strlen(contents)) - 1;
    int len = data_len > cursor ? data_len : cursor;

    for (int i = 0; i <= len; i++)
    {
        if (i == cursor) {
            printf("|");
        }
        if (i <= data_len ) {
            if (contents[i] == ' ') {
                printf("_");
            }
            else {
                printf("%c", contents[i]);
            }
        }
        else if (i < len) {
            printf(" ");
        }
    }
    printf("\n");
}
