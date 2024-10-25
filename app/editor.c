/**
 * editor.c -- строковый текстовый редактор
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;
    
    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {
        printf("ed > ");

        /* Получаем команду */
        fgets(cmdline, MAXLINE, stdin);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */
        
        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0 || strcmp(cmd, "l") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                load(txt, arg);
            }
            continue;
        }

        if (strcmp(cmd, "move") == 0 || strcmp(cmd, "m") == 0) {
            char *line, *col;
            if ((line = strtok(NULL, " \n")) == NULL
                || (col = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: m line column\n");
            } else {
                move(txt, atoi(line), atoi(col));
            }
            continue;
        }
        
        if (strcmp(cmd, "save") == 0 || strcmp(cmd, "s") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: save filename\n");
            } else {
                save(txt, arg);
            }
            continue;
        }
        
        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }
        
        /* */
        if (strcmp(cmd, "showunderscores") == 0) {
            showunderscores(txt);
            continue;
        }

        /**/
        if (strcmp(cmd, "mpweb") == 0) {
            mpweb(txt);
            continue;
        }

        /* Перемещение строки с курсором перед предыдущей  */
        if (strcmp(cmd, "rn") == 0) {
            rn(txt);
            continue;
        }

        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);
    }

    return 0;
}
