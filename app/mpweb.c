/**
 * mpweb.c - функция перемещения курсора в конец предыдущего слова
 *
 * Copyright (c) 2022, Gordeev Nikita <gordeev@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

/**
 * Перемещает курсор в конец предыдущего слова
 */
void mpweb(text txt) {
    int pos = txt->cursor->position;

    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    /* Текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);

    /* Стартуем с начальной строки текста */
    node *current = txt->begin;
    int i;
    int count = pos;
    int flag = 0;

    /* К каждой строке текста применяем обработчик */
    while(current) {
        if (txt->cursor->line == current) {
            flag = 1;
            break;
        }
        current = current->next;
    }
    if (flag == 0) {
        printf("No cursor in the text");
        return;
    }
    char *contents = current->contents;

    /* Цикл с поиском слова */
    for (i=pos; contents[i] != ' '; i--) {
        /* Проверка на конец слова и кол-во выведенных символов */
        if (contents[i] == ' ' || contents[i] == '?' || contents[i] == '.' || contents[i] == '!')
            break;

        if (i == 0)
            break;

        /* Проверка на букву */
        if (((int)contents[i] >= (int)'a') && (int)(contents[i] <= (int)'z')) {
            count--;
        }
        if (((int)contents[i] >= (int)'A') && ((int)contents[i] <= (int)'Z')) {
            count--;
        }
    }

    txt->cursor->position = count;

    return;
};
