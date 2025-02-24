[![CI/CD GitHub Actions](https://github.com/nikitagordeev10/petrsu_unit_testing_002_text_editor/actions/workflows/test-action.yml/badge.svg)](https://github.com/nikitagordeev10/petrsu_unit_testing_002_text_editor/actions/workflows/test-action.yml)
[![Coverage Status](https://coveralls.io/repos/github/nikitagordeev10/petrsu_unit_testing_002_text_editor/badge.svg?branch=main)](https://coveralls.io/github/nikitagordeev10/petrsu_unit_testing_002_text_editor?branch=main)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=nikitagordeev10_petrsu-unit-testing-002-text-editor&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=nikitagordeev10_petrsu-unit-testing-002-text-editor)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=nikitagordeev10_petrsu-unit-testing-002-text-editor&metric=bugs)](https://sonarcloud.io/summary/new_code?id=nikitagordeev10_petrsu-unit-testing-002-text-editor)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=nikitagordeev10_petrsu-unit-testing-002-text-editor&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=nikitagordeev10_petrsu-unit-testing-002-text-editor)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=nikitagordeev10_petrsu-unit-testing-002-text-editor&metric=ncloc)](https://sonarcloud.io/summary/new_code?id=nikitagordeev10_petrsu-unit-testing-002-text-editor)

Лабораторная работа 2: Текстовый редактор
Цель работы: реализация тестов для модуля приложения.
Задачи:
- Подготовьте каталог программы и распакуйте в него содержимое приложенного архива.
- Создайте тестовый текстовый файл input.txt с произвольным содержимым.
- Соберите программу с помощью make и выполните несколько раз, исследуйте код функции main (editor.c) и изучите команды редактора load файл и show.
- Реализуйте функцию сохранения содержимого файла save() и обработку команды save файл.
- Реализуйте функцию библиотеки и соответствующую команду перемещения в заданную позицию m номер строки позиция. Измените функцию вывода содержимого текста на экран так, чтобы позиция курсора отображалась символом "|".
- Обратите внимание, что при вводе текста символы перевода строк сохраняются, теперь это бросается в глаза. Измените код так, чтобы переводы строк не хранились, но при выводе текста на экран, после каждой строки выводился бы символ перевода строки.
- Модифицировать сборку программы в соответствии с шаблоном (заменить созданный вручную Makefile на сборку через qmake).
- Проверить компиляцию проекта, при необходимости добавить требуемые зависимости в проект.
- Реализовать индивидуальные задания:
- Гордеев Никита Владиславович	для вывода текста в прямом порядке следования строк с заменой пробелов символом подчеркивания showunderscores;	для перемещения курсора в конец предыдущего слова, если это возможно mpweb;	для удаления строки после текущей rn;
- Составить перечень тестов (шаблон документа) проверяющую правильность работы функций (позитивные тесты) и его реакцию на возможные отклонения от стандартного поведения (негативные тесты).
- Реализовать запланированные тесты. Выполнить тестирование. В случае обнаружения ошибки сформировать протокол ошибки (шаблон протокола), выполнить отладку и повторное тестирование.
- Зарегистрироваться в GitHub, создать проект, загрузить полученный проект (код приложения и тестов). Пример готового проекта на GitHub.
- Подключить автоматический запуск тестов (Github Actions), оценку покрытия кода тестами (https://coveralls.io/) и статический анализ кода (https://sonarcloud.io). Добавить ссылки на отчеты о тестировании и оценке покрытия в файл README.md.