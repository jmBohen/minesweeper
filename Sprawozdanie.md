# Sprawozdanie z gry Saper

## Instrukcja obsługi

### Zasady gry
Saper to gra, w której gracz odkrywa pola na planszy, unikając trafienia na miny. Każde odkryte pole pokazuje liczbę min na sąsiednich polach (od 0 do 8). Gracz może oznaczać pola flagami, aby zaznaczyć potencjalne miny. Jeśli gracz trafi na minę, lub skończy się mu czas gra się kończy. Gracz wygrywa poprzez zaznaczenie min, oraz odkrycie wszystkich pól bez min.

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

### Opcje uruchomienia:
1. **Tryb standardowy**: `bin/minesweeper`
2. **Tryb wczytania gry z pliku**: `bin/minesweeper -f <ścieżka_do_pliku>`
3. **Tryb strzałkowy**: `bin/minesweeper -t`

### Uruchamianie w trybie wczytania gry z pliku
1. **Uruchom**: `bin/minesweeper -f <ścieżka_do_pliku>`.
2. **Format pliku**: Przykład poprawnego formatu gry znajduje się w pliku `example_game.txt`
3. **Wyjście**: Liczba poprawnych ruchów, wynik i informacja o wygranej/przegranej.

### Uruchamianie w trybie strzałkowym
1. **Uruchom**: `bin/minesweeper -t`
2. **Wybierz poziom trudności**: Wybierz poziom trudności z listy
3. **Sterowanie**:
   - `Strzałka w góre/dół`: Przesuń aktywne pole o wiersz w górę/dół
   - `Strzałka w prawo/lewo`: Przesuń aktywne pole o kolumnę w pewo/lewo
   - `Klawisz 'f'`: Oznacz/odznacz flagą aktywne pole
   - `Klawisz 'r'`: Odkryj aktywne pole

## Szczegóły implementacji

### Moduły
- **board.c**: Plansza, ustawienia, logika gry.
- **leaderboard.c**: Tabela wyników.
- **user_interface.c**: Wejście/wyjście użytkownika.
- **game.c**: Inicjalizacja gry.

### Funkcje
- **create_empty_board**: Inicjalizacja pustej planszy.
- **set_settings**: Ustawienia gry.
- **initialize_board**: Ustawia miny po pierwszym kliknięciu.
- **reveal_square**: Odkrywa pole i sąsiadów.
- **flag_square**: Oznacza/odznacza flagą.
- **check_if_game_over**: Sprawdza czy gra się skończyła.
- **save_to_leaderboard**: Zapisuje wynik.
- **print_leaderboard**: Wyświetla 5 najlepszych wyników.

### Struktury
1. **Board** - Struktura planszy:
   - `int size_r`: Ilość pól w wierszu
   - `int size_c`: Ilość pól w kolumnie
   - `int number_of_mines`: Liczba min na planszy
   - `int time_in_minutes`: Odliczany czas do porażki w minutach
   - `int start_time`: Zapisany moment rozpoczęcia gry
   - `int number_of_revealed_squares`: Liczba odsłoniętych pól
   - `char difficulty`: Poziom trudności, potrzebny do obliczenia wyniku, oraz stworzenia planszy o odpowiedniej wielkości
   - `Square *squares`: Tablica zawierająca instancje struktur pól
3. **Square** - Struktura pola:
   - `int is_mine`: Wartość logiczna określająca czy na danym polu jest mina
   - `int is_revealed`: Wartość logiczna określająca czy dane pole jest odkryte
   - `int is_flagged`: Wartość logiczna określająca czy dane pole jest oznaczone flagą
   - `int number_of_neighbour_mines`: Liczba pól z minami w sasiądztwie danego pola 

### Testy

### Makefile
- **install_ncurses**:  Instaluje bibliotekę ncurses.
- **bin/minesweeper**: Kompiluje i linkuje pliki.
- **clean**: Usuwa pliki binarne.

## Podział pracy
- **Jan Bocheński**: Struktury danych, logika gry, testy, makefile.
- **Mariusz Wakuła**: Interfejs, sterowanie, tabela wyników, wczytywanie gry z pliku.

## Podsumowanie
Udało nam się zaimplementować wszystkie wymagane funkcjonalności, dodatkowo zaimplementowaliśmy sterowanie strzałkami, kolorowe liczby min w sąsiędztwie, oraz limit czasu na grę. Trudniejszymi fragmentami było odsłanianie sąsiędnich min, oraz sterowanie strzałkami. Dodaliśmy bibliotekę `ncurses`, aby umożliwić sterowanie strzałkami, oraz ułatwić zmianę kolorów w konsoli. Projekt był przyjemny w tworzeniu, a efekt końcowy jest satysfakcjonujący.
