# cub3D_by_ncliff
------------
Проект собирается в готовый исполнительный файл.
Правила Makefile: make, make re, make clean, make fclean.

**Использование:**
- ./cub3D \<map\> - для запуска игры.
- ./cub3D \<map\> --save - для сохранения первого кадра игры.

**Аргументы:**
- Карта должна иметь расширение ".cub"
- Меньше 2 и бльше 3 вргументов быть не может
- Скриншот делается только через "--save"

**Карта:**
- не должна иметь дыр в стенах
- не должна иметь символы кроме: 0, 1, 2, W, E, S, N
- не должны иметь '\n' в карте

**Пример валидной карты:**
```txt
R 1920 1080
NO ./north_texture
SO ./south_texture
WE ./west_texture
EA ./east_texture
S ./sprite_texture
F 255,100,0
C 0,100,255

    11111111111111
    10000200200001
    10200000000201
111110000000000001
10200000N000000201
100000000000000001
102000000000000201
100002002200200001
111111111111111111

```
