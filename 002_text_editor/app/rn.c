/**
* rn.c - реализует функцию удаления строки после текущей
*
* Copyright (c) 2022, Nikita Gordeev <gordeev@petrsu.ru>
*
* This code is licensed under a MIT-style license.
*/

#include "_text.h"


/**
 * Удаляет строку после текущей
 */
void rn(text txt)
{
   /* Проверяем, имеется ли текст */
   if (txt == NULL) {
       fprintf(stderr, "The text doesn't exist!\n");
       return;
   }

   /* Если список изначально пуст, делать ничего не надо */
   if (txt->length == 0 || txt->cursor->line == 0) {
       return;
   }

   /* Текст ненулевой длины должен содержать хотя бы одну строку */
   assert(txt->begin != NULL && txt->end != NULL);

   /* Стартуем с первого элемента списка */
   node* current = txt->cursor->line;

   // если (есть строка после текущей)
   if (current->next) {

       // получаем указатель на следующую строку
       node* next = current->next;


       /* Проверяем, имеется ли текст */
       if (txt == NULL || current == 0 || txt->length == 0  || current->next == 0 || next->next == 0 ) {
           return;
       }

       // текущая строка -> следующая строка = строка после следующей
       current->next = next->next;

       // строка после следующей -> предыдущая строка = текущая
       next->next->previous = current;

       // очистить память следующей строки
       free(next);
   }
}
