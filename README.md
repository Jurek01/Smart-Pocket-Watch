# Smart-Pocket-Watch

Projekt na technikę mikroprocesorową
Program korzysta z SDK dla Raspberry pico

main.c - główny program

`/lib` - biblioteki dostarczone przez producenta modułu
- Config  --Podstawowy interfejs sprzętowy
- Fonts   --Fonty dla sterownika LCD
- LCD     --Sterownik LCD
- GUI     --Funkcje do rysowania -Q
- QMI8658 --Sterownik IMU

`/mylib` - biblioteki napisane przeze mnie 
- hardware    --inicjalizacja oraz sterowanie enkoderem
- apps        --zarządzanie aplikacjami
- watch_app   --aplikacje zegarka tarczowego oraz numerycznego
- measurement --aplikacja wyświetlania danych oraz mini gry
