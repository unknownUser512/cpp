 ///////////_________#1_WPROWADZANIE_IP_________/////////// 

 Wprowadzanie adresu IP, nic nadzwyczajnego - sprawdzanie, czy liczba podana mieści
 się w przedziale 0-255, jeśli nie to jest wpisywane tam "0" oraz inkrementacja.

 I tutaj zaznaczę: można byłoby zastosować tam "break", lecz to wypali w przypadku kiedy
 użytkownik będzie wprowadzał każdy oktet osobno (czyli dla każdego da "ENTER").
 Natomiast kiedy użytkownik wprowadzi ciągłość, np. 192 300 128 0 (czyli 2 oktet jest niepoprawny)
to wtedy do tablicy zapisze się mimo wszystko trzeci i czwarty oktet i program będzie
wymagał wprowadzenia 2 oktetów zamiast 4 - co skutkowałoby wprowadzeniem złego IP.
Tak samo w przypadku wprowadzania maski.



 ///////////_________#2_WPROWADZANIE_MASKI_________/////////// 

 Ok, więc z maską już jest nieco bardziej złożony problem.

1 oktet(i==0): hmm, przy wprowadzeniu pierwszego oktetu jest najmniejszy problem.
Mianowicie trzeba tylko i wyłącznie sprawdzić, czy podana liczba wynosi minimum "128", ponieważ
nie może wynosić "0". Wtedy załącza się pętla od j=1. I jeżeli się znajdzie "odpowiednik" to
jest wywołana funkcja "provide_mask" (ale o niej dalej), następnie inkrementowane "i" oraz
zostaje przerwana pętla. 
Natomiast w tym samym "ifie" jest jeszcze jeden, który sprawdza czy "i" wynosi nadal "0", ponieważ
jeśl nie znalazł się "odpowiednik" wprowadzonej liczby przez użytkownika w tablicy to znaczy,
że "i" wynosi nadal "0" - czyli jest wartość wprowadzona niepoprawna. I dzieje się to co jest
w tym "ifie", czyli: wpisanie do maski "-1", iteracja maski, inkrementacja control oraz
ustawienie wrong na "true". 
Jeżeli ogólnie wprowadzona wartość przez użytkownika jest mniejsza od 128 lub większa od 255
to wykona się "else", czyli: wpisanie do maski "-1", iteracja maski, inkrementacja control oraz 
ustawienie wrong na "true". 
Wpisując "-1" - ma to pewne zadanie/funkcję. Mówi to nam, że wprowadzona maska w tym momencie
jest już niepoprawna i dzięki temu w dalszych "ifach" po iteracji przeskakujemy od razu
do ostatniego "else".

2/3 oktet(i==1 || i==2): Wiadomo: sprawdzamy na początku, czy poprzednia maska nie ma wartości
"-1" (o tym wyżej pisałem) oraz czy mieści się w zakresie.

Jeżeli "if" jest ok: to przechodzimy do tego "ifa" w środku. Sprawdzamy, czy poprzednia
maska ma wartość "255" - jeżeli tak to odpala się pętla i sprawdzamy.
Jeśli natomiast podana wartość mieści się w zakresie, natomiast nie jest poprawna to
o tym mówi nam "loop_counter" - bo jeśli będzie on miał wartość "8" - to znaczy, że wartość
wprowadzona była niepoprawna.

Jeżeli maska poprzednia jest mniejsza od "255" to jej wartość może wynosić tylko i wyłącznie
"0". I jest to sprawdzane.

4 oktet(i==3): Tutaj sprawdzamy tak jak poprzednio, z tym że ostatnia maksymalna wartość
tego oktetu może wynosić "252".

Jeżeli jakikolwiek oktet został wpisany z niepoprawną wartością to po wyjściu z pętli
"while" jest sprawdzany stan zmiennej "wrong". Jeżeli zwróci prawdę to resetujemy do 
wartości "0": control, short_mask, "i" oraz ustawiamy "wrong" na "false".

Działanie "provide_mask()"
Przyjmuje ona następujące argumenty(parametry): maskę, maskę negatywną, adres ip, 
adres sieciowy, adres rozgłoszeniowy, skróconą maskę oraz zmienną "control".

Także przy wprowadzaniu maski zostaje już tak na prawdę wyliczany adres sieciowy, adres rozgłoszeniowy,
maska negatywna oraz skrócona maska (na której tak na prawdę później bazujemy jeśli chodzi
o poprawne tworzenie podsieci).

..............

Po tym (jeżeli wszystko jest poprawne) to wyświetlają się te adresy w konsoli, skrócona maska
oraz maksymalna ilość "hostów" za pomocą funkcji "display_net_br()".

 ///////////_________#3_PODZIAŁ SIECI_________///////////

 Tutaj zaczyna się tak na prawdę "przygoda".

 Na początek sprawdzamy czy skrócona maska (short_mask) jest mniejsza bądź równa "29", ponieważ
 jeżeli ma "30" to nie możemy już dodać żadnej sieci (maksymalna skrócona maska to "30").

 Jeżeli jest ok to wyświetlają się poprawne możliwe ilości podsieci do aktualnej sieci, 
 za pomocą "display_correct_quantity(short_mask)".

 Następnie jest "if", który sprawdza, czy "if(compare_shortMask(short_mask, choice))" zwróci
 prawdę. Jest tam sprawdzane w zależności od wartości wprowadzonej przez użytkownika, czy
 może podzielić na taką ilość daną sieć. Np. jeśli ma skróconą maskę aktualną o wartości "28"
to może mieć max łącznie "4 sieci" (poprzez tą funkcję), 
ponieważ 4 sieci to 2 bity w tym określonym przypadku. 
Po tym skrócona maska będzie miała wartość 30 (28b+2b). 

 Następnie jest funkcja "change_mask(mask, short_mask)".
 Ona sprawdza za pomocą switcha, jaka wartość skróconej maski jest akutalnie.
 I tak np. dla skróconej maski z przedziału 2-8 wiemy, że działamy na oktecie pierwszym.
 Dla przedziału 9-16 wiemy, że działamy na oktecie 2 i tam modyfikujemy wartość. 
 Analogicznie jest dalej.


 Dalej zostaje wywołana "network_division()"

 W niej na początku wywołana zostaje funkcja "restart_maskAndBroad()".
 Wykonuje się tutaj pętla typu "for" 4 razy.
 Działa ona w następujący sposób:
 Tak na prawdę, skoro mamy już nową skróconą maskę to mamy również zmodyfikowaną zwykłą
 maskę (co wyżej było wspomniane). Wiemy też, że pierwszy adres sieciowy oraz rozgłoszeniowy
 wyznaczamy tak: adres sieciowy nie ulega zmianie natomiast musimy zresetować adres rozgłoszeniowy
 do adresu sieciowego, zrobić negację maski oraz dodać do zresetowanego adresu rozgłoszeniowego
 nową znegowaną maskę. Wtedy mamy pierwsze 2 adresy (sieciowy i rozgłoszeniowy) - na których
 bazujemy dalej.

 Nastepnie sprawdzamy jaka była odpowiedź wprowadzona przez użytkownika.
 I w zależności od wprowadzonej długości ustawiamy zmienną "userChoice" na prawdiłową
 wartość, typu: "1, 2, 4, 8". 
Jakie to ma zadanie? 
Otóż każda pętla zwraca 2 adresy (adres sieciowy + rozgłoszeniowy).
Np. jeśli odpowiedź użytkownika wynosi "2" to pętla wykona się tylko 2 razy, 
jeśli wynosi "16" to pętla wykona się 8 razy. Więc tak na prawdę ta zmienna wyznacza nam
ile dana pętla ma się razy wykonać.

----------------------------------

Następnie są "ify", które sprawdzają wartośc aktualnej maski sieciowej.

Pierwszy przypadek jeżeli skrócona maska ma aktualną wartość od 25 do 30:
tak na prawdę jest to najłatwiejszy podział, ponieważ działamy tutaj tylko i wyłącznie
na jednym, ostatnim (czwartym) oktecie.

Wiemy, że każdy następny adres sieciowy to tak na prawdę adres rozgłoszeniowy z wartością
"+1" dla czwartego oktetu, a każdy adres rozgłoszeniowy to adres rozgłoszeniowy + negacja
maski.

I wyznacza się to tak: tak na prawdę przy "userChoice" równe "2" wykona się tylko raz
gdzie te adresy zostały już ustawione w "restart_maskAndBroad()".
Jeżeli "userChoice" wynosiło załóżmy "4" to pętla wykona się 2 krotnie, ale:
najpierw zostaną wyświetlone adresy już z funkcji "restart_maskAndBroad()", a później
po pierwszym przebiegu pętli jest "if", który sprawdza i wykonuje się tak na prawdę
tylko od 2giego przebiegu pętli (i to w przypadku każdego podziału[zakresu maski]).

Jest tam funkcja: "new_network()" - która wpisuje nam tak jak wyżej wspomniałem.
Przed jej wywołaniem zwiększamy wartość 4 oktetu o "+1".
Do adresu sieciowego wpisuje adres rozgłoszeniowy, a do adresu rozgłoszeniowego dodaje negacje maski.

----------------------------------

Drugi przypadek: sprawdzamy, czy maska mieści się w przedziale 17-24.
Tutaj juz sprawa wygląda inaczej. Wiemy, że z podaną maską będziemy działać na 2ch
ostatnich oktetach. Czyli, przy dodawaniu sieci wygląda to tak: 

Przed wywołaniem funkcji "new_network()" musimy zresetować wartość 4 oktetu na "0".
Oraz dodać wtedy wartość "+1" do 3 oktetu. Wtedy następuje poprawne wyliczanie.

Trzeci przypadek: sprawdzamy, czy maska mieści się w przedziale 9-16.
Wiemy tutaj, że działamy na 3ech oktetach (oczywiście liczymy od "prawego" - ostatniego).
Przed wywołaniem funckji "new_network()" musimy zresetować wartość 4 oraz 3 oktetu na "0".
Natoamiast do 2 oktetu dodać wartość "+1".

Czwarty przypadek: sprawdzamy, czy maska mieści się w przedziale 1-8.
Wiemy tutaj, że działamy na wszystkich 4ech oktetach.
Przed wywołaniem funkcji "new_network()" musimy zresetować wartości 4, 3 oraz 2 oktetu na "0".
Natomiast do 1 oktetu dodać wartość "+1".

----------------------------------

I teraz po każdym z tych przypadków sprawdzamy, czy wartość skróconej maski jest mniejsza
bądź równa "29". Jeżeli tak, to pytamy, czy użytkownik chce "dodać" jeszcze jedną sieć.
Tak na prawdę to podzielić ostatnia z podsieci na osobne, dwie podsieci. 

Jeżeli tak to wywołana zostaje "add_another()".
Na początku inkrementujemy skróconą maskę (ponieważ 2 sieci to 1 bit).
Zmieniamy maskę za pomocą funkcji "change_mask()", dalej "restart_maskAndBroad()", 
"display_net_br()" - więc mamy pierwsze adresy (sieciowy + rozgłoszeniowy).
Następnie dla każdego z tych przypadków - w zależności od długości maski resetujemy podane
oktety i dodajemy do prawdiłowego wartość "+1".







 

