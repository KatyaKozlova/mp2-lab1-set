// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <cassert>


TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField),  MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= 0 && Elem < MaxPower) {
         return BitField.GetBit(Elem);
    }
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem >= 0 && Elem < MaxPower) {
       BitField.SetBit(Elem);
    }
  
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem >= 0 && Elem < MaxPower) {
      BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return MaxPower == s.MaxPower && BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
   
    return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.BitField.SetBit(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= 0 && Elem < MaxPower) {
        TSet res(*this);
        res.BitField.ClrBit(Elem);
        return res;
    }
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(BitField & s.BitField);
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(~BitField);
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    string str;
    istr >> str;

    assert(str.length() == s.BitField.GetLength());

    for (int i = 0; i < s.BitField.GetLength(); i++) {
        s.BitField.ClrBit(i);
        if (str[i] == '1')
            s.BitField.SetBit(i);
    }

    return istr;
}


ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
 
    for (int i = 0; i < s.BitField.GetLength(); i++)
        ostr << s.BitField.GetBit(i);
    return ostr;
}
