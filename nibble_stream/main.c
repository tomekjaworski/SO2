#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>

/*
 * Zadanie: Napisz program, który na wejściu otrzymuje strumień liczb typu uint32_t jącą liczbę tetrad znaczących.
 * Uzyskiwany strumień tetrad należy zapisywać w ciągu bajtów. Ciąg bajtów jest wyjściem programu.
 * Za koniec strumienia uznawana jest tetrada nagłówkowa o wartości 0xF.
 * W przypadku zakończenia strumienia liczb wejściowych w takim momencie, że liczba tetrad wyjściowych jest nieparzysta,
 * należy dopełnić je tetradami 0xF (symbol końca strumienia).
 *
 * Pojęcie tetrad znaczących i tetard nieznaczących jest identyczne z pojęciem cyfr znaczących i zer nieznaczących.
 * W liczbie 000001230 mamy cztery cyfry znaczące ("1230") oraz pięć zer nieznaczących ("00000").
 * Zadaniem w/w programu, w odniesieniu do takiego przykłądu, byłoby m.in. skrócenie tekstu "000001230" do "1230".
 *
 * Przykłady:

 * Liczba: 0x0000abcd; liczba tetrad znaczących: 4, liczba tetrad (zer) nieznaczących: 16 - 4
 * Wyjście: 4a bc df
 *          ^      ^ tetrady nagłówkowe
 *
 * 0x00000234
 * 32 34 FF
 * ^     ^ dwie tetrady nagłówkowe + wypełniacz (ostatni F)
 * 0x00000234, 0x0000000F
 * 32 34 1F FF
 * ^     ^  ^
 * 0x00000234, 0x0000000F, 0x000000AB
 * 32 34 1F 2A BF
 * ^     ^  ^   ^ cztery tetrady i brak wypełniacza (nie jest potrzebny)
 * 0x00000234, 0x0000000F, 0x000000AB, 0x000000CD
 * 32 34 1F 2A B2 CD FF
 * ^     ^  ^   ^    ^
 * 0x00000234, 0x0000000F, 0x000000AB, 0x000000CD, 0x00000000
 * 32 34 1F 2A B2 CD 0F
 * ^     ^  ^   ^    ^^
 * 0x00000234, 0x0000000F, 0x000000AB, 0x000000CD, 0x00000000, 0xa5b6c7d8
 * 32 34 1F 2A B2 CD 08 a5 b6 c7 d8 ff
 * ^     ^  ^   ^    ^^             ^
 */

void store_nibble(int nibble_value, int *nibble_pointer, void** destination) {
    if (*nibble_pointer % 2 == 0) {
        // Od razu dodaj terminator (F) na końcu; jeżeli dane się skończą
        // to on juz tam będzie; jeżeli nie, to kod w 'else' zastąpi go nową wartością
        *(uint8_t *) *destination = ((nibble_value & 0xF) << 4) | 0x0F;
        (*nibble_pointer)++;
    } else {
        // Ustaw młodszą tetradę pozostawiając starszą nienaruszoną (została ona ustawiona wcześniej)
        *(uint8_t *) *destination = (*(uint8_t *) *destination & 0xF0) | (nibble_value & 0xF);
        *destination = (uint8_t *) *destination + 1;
        (*nibble_pointer)++; // zwięsz wskazywaną wartość
    }
}


void convert(const uint32_t * source, int count, void* destination) {
    if (source == NULL || count <= 0)
        return; // nie ma co robić

    int nibble_pointer = 0;

    while (count-- > 0) {
        uint32_t data = *source++;

        // policz liczbę tetrad ZNACZĄCYCH; rozwiązanie nie jest wyjątkowo optymalne, za to jest czytelne
        uint32_t mask = 0;
        int nibbles = 8;
        for (; nibbles > 0; nibbles--) {
            mask = (mask >> 4) | 0xF0000000; // 0xF0000000, 0xFF000000, 0xFFF00000, itd...
            if ((data & mask) != 0)
                break;
        }

        // zapisz liczbę znaczących tetrad
        store_nibble(nibbles, &nibble_pointer, &destination);

        // zapisz znaczące tetrady
        for (; nibbles > 0; nibbles--) {
            mask = 0xF << 4 * (nibbles - 1);
            int nibble = (data & mask) >> 4 * (nibbles - 1);
            store_nibble(nibble, &nibble_pointer, &destination);
        }
    }

    // Jeżeli liczba tetrad jest parzysta, do dodaj terminator na końcu
    if (nibble_pointer % 2 == 0)
        *(uint8_t*)destination = 0xFF;

}

int main() {
    uint32_t data1[] = {0x00000234};
    uint32_t data2[] = {0x00000234, 0x0000000F};
    uint32_t data3[] = {0x00000234, 0x0000000F, 0x000000AB};
    uint32_t data4[] = {0x00000234, 0x0000000F, 0x000000AB, 0x000000CD};
    uint32_t data5[] = {0x00000234, 0x0000000F, 0x000000AB, 0x000000CD, 0x00000000};
    uint32_t data6[] = {0x00000234, 0x0000000F, 0x000000AB, 0x000000CD, 0x00000000, 0xa5b6c7d8};

    uint8_t output[128];

    convert(data1, 1, output);
    assert(memcmp(output, "\x32\x34\xFF", 3) == 0);

    convert(data2, 2, output);
    assert(memcmp(output, "\x32\x34\x1F\xFF", 4) == 0);

    convert(data3, 3, output);
    assert(memcmp(output, "\x32\x34\x1F\x2A\xBF", 5) == 0);

    convert(data4, 4, output);
    assert(memcmp(output, "\x32\x34\x1F\x2A\xB2\xCD\xFF", 7) == 0);

    convert(data5, 5, output);
    assert(memcmp(output, "\x32\x34\x1F\x2A\xB2\xCD\x0F", 7) == 0);

    convert(data6, 6, output);
    assert(memcmp(output, "\x32\x34\x1F\x2A\xB2\xCD\x08\xa5\xb6\xc7\xd8\xff", 12) == 0);

    return 0;
}
