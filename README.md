# АВС, задание 1

- **Автор**: Коннов Илья (@iliakonnov), БПИ201
- **Вариант**: 16

## Задание
Прочитать простые геометрические фигуры с цветом, отсортировать их по периметру при помощи straight sort и вывести.

# Кроссплатформенность
Программа написана на C и зависит от glibc. Следовательно будет работать практически на всех дистрибутивах linux (и только на них).

# Компиляция и запуск
```bash
./build.sh -DCMAKE_BUILD_TYPE=Release && ./build/AVS1
```

# Использование
См. `AVS1 -h`

# Архитектура

Параметры компьютера:

- **Процессор:**  AMD Athlon(tm) X4 750K Quad Core Processor
- **ОС:** NixOS 21.11.git.e83b22e2a36
- **Kernel:** `Linux 5.10.69 x86_64`

## Использование памяти

- Базовые типы:
    * `size_t`, `*T` - 8
    * `unsigned int`, `int` - 4
    * `char` - 1
    * Небольшие перечисления компилируются как `int` в моём случае.

- `enum color`
    * 4 байта, аналогично `int`

- `struct point`
    * `int x` – 4 (0)
    * `int y` — 4 (4)
    * Итого: 8

- `struct circle`
    * `color` — 4 (0)
    * `point` — 8 (4)
    * `int radius` – 4 (12)
    * Итого: 16

- `struct rectangle`
    * `color` — 4 (0)
    * `point left_upper` — 8 (4)
    * `point right_bottom` – 8 (12)
    * Итого: 20

- `struct triangle`
    * `color` — 4 (0)
    * `point a` — 8 (4)
    * `point b` – 8 (12)
    * `point c` – 8 (20)
    * Итого: 28

- `struct shape`
    * `kind` — 4 (0), аналогично `int`
    * `union value` — 28 (4)
        + `circle` — 16 (4)
        + `rectangle` — 20 (4)
        + `triangle` — 28 (4)
    * Итого: 32

- `struct buffer`
    * `size_t position` — 8 (0)
    * `char* start` — 8 (8), на куче, 4КиБ.
    * `buffer* next` – 8 (16), на куче 24 байта
    * Итого: 24

- `struct vector`
    * `size_t length` — 8 (0)
    * `size_t capacity` — 8 (8)
    * `shape* start` – 8 (16), на куче по необходимости
    * Итого: 24

Только последние два типа используют кучу.

# Модули
По одному модулю (`.c` + `.h`) на каждую структуру, получаем 8 модулей. Плюс точка входа `main.c`
