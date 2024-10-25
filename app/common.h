/**
 * common.h -- прототипы функций реализации команд редактора
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef COMMON_H
#define COMMON_H

#include "text.h"

/* Декларирует неиспользуемый аргумент,
 * корректно подавляя предупреждение вида "unused parameter" */
#define UNUSED(x) (void)(x)

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt);

/**
 * Загружает содержимое указанного файла
 */
void load(text txt, char *filename);

/**
 * Загружает содержимое указанного файла
 */
void save(text txt, char *filename);

/**
 * Загружает содержимое указанного файла
 */
void move(text txt, int line, int pos);

/**
 * Загружает содержимое указанного файла
 */
void showunderscores(text txt);

/**
 * Загружает содержимое указанного файла
 */
void mpweb(text txt);

/**
 * Загружает содержимое указанного файла
 */
void rn(text txt);

#endif
