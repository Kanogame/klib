#ifndef KLIB_COMB
#define KLIB_COMB

// cmb_Combination создает подмножества множества, порядок не важен, есть
// повторения - от нуля до srclen подмножества возможно использовать как массивы
// индексов
void cmb_CombinationRepeat(int srclen, int len, int *source);

// cmb_Combination создает подмножества множества, порядок не важен, нет
// повторений - от нуля до srclen подмножества возможно использовать как массивы
// индексов
void cmb_Combination(int srclen, int len, int *source);

#endif
