// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cassert>
static constexpr int BitsinElem = numeric_limits<TELEM>::digits; 
inline void TBitField::IsIndex(const int index) const {  // проверяем индекс
	if (index < 0 || index >= BitLen) 
		throw exception("error index");
}
TBitField::TBitField(int len): MemLen((len / BitsinElem) + ((len % BitsinElem) != 0))
	{
		if (len < 0)
			throw exception("incorrect length");
		BitLen = len;
		pMem = new TELEM[MemLen]();
	}


TBitField::TBitField(const TBitField &bf) 
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen]();
	copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	
	return n/BitsinElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & (BitsinElem - 1));

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	IsIndex(n); 
	pMem[GetMemIndex(n)] |= GetMemMask(n); // побитовое сложение 

}

void TBitField::ClrBit(const int n) // очистить бит
{
	IsIndex(n);
	pMem[GetMemIndex(n)] &= ~GetMemMask(n); // побитовое умножение 
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	IsIndex(n);
  return pMem[GetMemIndex(n)]&GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	return true;
	
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
  
}
TBitField TBitField::operator|(const TBitField & bf) // операция "или"
		{
			const TBitField* rhs;
		TBitField res(1);
		if (BitLen > bf.BitLen) {
			rhs = &bf;
			res = *this;
		}
		else {
			res = bf;
			rhs = this;
		} 
			for (int i = 0; i < res.MemLen; i++) {
				res.pMem[i] |= rhs->pMem[i];
			}

		return res;
	
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField res(max(BitLen, bf.BitLen));
	const int less = min(MemLen, bf.MemLen);

	for (int i = 0; i < less; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return res;
	return 0;

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField out(*this);
	for (int i = 0; i < BitLen; i++)
		if (out.GetBit(i) > 0)
			out.ClrBit(i);
		else
			out.SetBit(i);
	return out;
	return 0;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string str;
	istr >> str;

	assert(str.length() == bf.BitLen);

	for (int i = 0; i < bf.BitLen; i++) {
		bf.ClrBit(i);
		if (str[i] == '1')
			bf.SetBit(i);
	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
