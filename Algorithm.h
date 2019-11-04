//
// Created by Mairenn on 2019-06-03.
//

#ifndef LAB4_ALGORITHM_H
#define LAB4_ALGORITHM_H

template <typename _IterIn, typename _Pred>
_IterIn findIf(_IterIn first, _IterIn last, _Pred pred)
{
    for (; first != last; ++first) {
        if (pred(*first))
            break;
    }

    return first;
}

template <typename _IterIn>
_IterIn minElement(_IterIn first, _IterIn last)
{
    if (first == last) return last;

    _IterIn min = first;
    ++first;
    for (; first != last; ++first) {
        if (*first < *min)
            *min = *first;
    }

    return min;
}

template <typename _IterIn>
_IterIn maxElement(_IterIn first, _IterIn last)
{
    if (first == last) return last;

    _IterIn max = first;
    ++first;
    for (; first != last; ++first) {
        if (*first > *max)
            *max = *first;
    }

    return max;
}


template <typename _IterIn, typename _Operation>
void forEach(_IterIn first, _IterIn last, _Operation op)
{
    for (; first != last; ++first) {
        op(*first);
    }
}

template <typename _IterIn, typename _IterOut, typename _Pred>
_IterOut copyIf(_IterIn first, _IterIn last, _IterOut result, _Pred pred)
{
    for (; first != last; ++first) {
        if (pred(*first)) {
            *result = *first;
            ++result;
        }
    }

    return result;
}

template <typename _IterIn, typename _Pred>
size_t countIf(_IterIn first, _IterIn last, _Pred pred)
{
    size_t count = 0;
    for (; first != last; ++first) {
        if (pred(*first)) {
            count++;
        }
    }
    return count;
}

template <typename _FreeTerator,typename _Comparator>
void sort(_FreeTerator start,_FreeTerator end,_Comparator compare){
    for(_FreeTerator current=start;current!=end;current++){
        for(_FreeTerator inCurrent = start;inCurrent!=end-1;inCurrent++){
            if(compare(*(inCurrent),*(inCurrent+1))){
                auto temp = *inCurrent;
                *inCurrent=*(inCurrent+1);
                *(inCurrent+1) = temp;
            }
        }
    }
}

/*
 * В отдельном файле Algorithm.h разработать следующие алгоритмы на базе шаблонных функций:

1. Алгоритм findIf(beg, end, pred) для поиска по диапазону [beg, end) произвольного контейнера при заданном условии. Возвращает итератор на найденный элемент или итератор на элемент, следующий за последним, в противном случае.

2. Алгоритм minElement(beg, end) для определения минимального элемента в диапазоне [beg, end) произвольного контейнера. Возвращает итератор на найденный элемент или итератор на элемент, следующий за последним, в противном случае.

3. Алгоритм maxElement(beg, end) для определения максимального элемента в произвольном контейнере. Возвращает итератор на найденный элемент или итератор на элемент, следующий за последним, в противном случае.

4. Алгоритм forEach(beg, end, op) для выполнения произвольной операции над элементами диапазона [beg, end) произвольного контейнера. Ничего не возвращает.

5. Алгоритм сортировки Sort(beg, end) заданного диапазона [beg, end) произвольного контейнера (метод сортировки выбрать самостоятельно). Ничего не возвращает.

6. Алгоритм copyIf(sourceBeg, sourceEnd, destBeg, pred) для копирования элементов диапазона [sourceBeg, sourceEnd) произвольного контейнера-источника в контейнер-приемник, начиная с позиции итератора destBeg, удовлетворяющих предикату pred.

Основные требования по алгоритмам:

1. Алгоритмы должны быть построены таким образом, чтобы они взаимодействовали с контейнерами только посредством итераторов.

2. Логические условия ряда алгоритмов (например, условие отбора нужного элемента при поиске, копировании и т.д.) должны быть реализованы в виде предикатов (на базе функторов или лямбда-функций).
 */

#endif //LAB4_ALGORITHM_H
