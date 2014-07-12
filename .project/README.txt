Zanim pogrążysz się w szaleńczym transie kodzenia, uspokój się i przeczytaj dokładnie co tutaj jest
napisane:

1) Upewnij się, że masz zainstalowany kompilator g++, make i premake4 (ten ostatni musi być w wersji
czwartej, wcześniejsze nie trawią skryptów w Lui)
2) Tak, jest to konieczne i nie będziemy korzystali z Makefile'a od Witka
3) Nie, nie możesz robić na Windowsie, tam na pewno nie uda ci się premake4 zainstalować

Jak wygenerować Makefile?
1) Musisz przejść do katalogu .project
2) Wydaj polecenie premake4 gmake
3) Jeśli wszystko poszło dobrze to powinieneś nie mieć błędów i w bieżącym katalogu pliki
Castle.make i Makefile

UWAGA!!!
Na przyszłość: po każdym dodaniu pliku do projektu MUSISZ wykonać tę komendę: premake4 gmake
aby Makefile był zaktualizowany

Jak kompilować?
Po prostu wydajesz komendę make
Aby wyczyścić katalog projektu ze zbędnych plików piszesz make clean
