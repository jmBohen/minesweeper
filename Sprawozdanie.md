# Raport z gry Saper

## Instrukcja obsługi

### Zasady gry
Saper to gra, w której gracz odkrywa pola na planszy, unikając trafienia na miny. Każde odkryte pole pokazuje liczbę min na sąsiednich polach (od 0 do 8). Gracz może oznaczać pola flagami, aby zaznaczyć potencjalne miny.

### Jak uruchomić program
1. **Zbuduj program**: Uruchom `make` w terminalu.
2. **Uruchom grę**: Wykonaj `bin/minesweeper`.
3. **Wybierz poziom trudności**:
   - Łatwy: 9x9, 10 min
   - Średni: 16x16, 40 min
   - Trudny: 16x30, 99 min
   - Własny: Zdefiniuj rozmiar planszy i liczbę min
4. **Graj w grę**:
   - `f x y`: Oznacz/odznacz flagą pole (wiersz `x`, kolumna `y`)
   - `r x y`: Odkryj pole (wiersz `x`, kolumna `y`)
5. **Koniec gry**: Gra kończy się po odkryciu wszystkich pól bez min lub miny. Wprowadź swoje imię, aby zapisać wynik.

### Uruchamianie w trybie plikowym
1. **Uruchom**: `bin/minesweeper -f <ścieżka_do_pliku>`.
2. **Format pliku**: Układ planszy i ruchy w formacie komend terminalowych.
3. **Wyjście**: Liczba poprawnych ruchów, wynik i informacja o wygranej/przegranej.

## Szczegóły implementacji

### Moduły
- **board.c**: Plansza, ustawienia, logika gry.
- **leaderboard.c**: Tabela wyników.
- **user_interface.c**: Wejście/wyjście użytkownika.
- **game.c**: Główna pętla gry i inicjalizacja.

### Funkcje
- **create_empty_board**: Inicjalizacja pustej planszy.
- **set_settings**: Ustawienia gry.
- **initialize_board**: Ustawia miny po pierwszym kliknięciu.
- **reveal_square**: Odkrywa pole i sąsiadów.
- **flag_square**: Oznacza/odznacza flagą.
- **check_if_game_over**: Sprawdza koniec gry.
- **save_to_leaderboard**: Zapisuje wynik.
- **print_leaderboard**: Wyświetla 5 najlepszych wyników.

### Struktury
- **Board**: Plansza, rozmiar, liczba min, pola.
- **Square**: Pole, stan (odkryte, oflagowane, mina), liczba sąsiednich min.

### Testy
- **test_board.c**: Plansza i logika gry.
- **test_game.c**: Główna pętla i inicjalizacja.
- **test_leaderboard.c**: Tabela wyników.
- **test_user_interface.c**: Wejście/wyjście.

### Makefile
- **install_ncurses**:  Instaluje bibliotekę ncurses.
- **Kompilacja**: Kompiluje i linkuje pliki.
- **Clean**: Usuwa pliki obiektowe.

## Podział pracy
- **Członek 1**: Plansza, logika, wejście plikowe.
- **Członek 2**: Interfejs, tabela wyników, testy.

## Podsumowanie
- **Funkcje**: Poziomy trudności, tryb plikowy, tabela wyników.
- **Wyzwania**: Obsługa wejścia, bezpieczeństwo pierwszego ruchu.
- **Wnioski**: Projekt ukończony, funkcjonalności działają.
