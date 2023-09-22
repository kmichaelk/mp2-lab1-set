// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#include <stdexcept>
#include <algorithm>
#include <limits>

static constexpr size_t maxElem = numeric_limits<elem_t>::max();
static constexpr size_t bitsInElem = numeric_limits<elem_t>::digits;

TBitField::TBitField(size_t len)
    : bitLen(len), memLen((len / bitsInElem) + ((len % bitsInElem) != 0))
{
  pMem = new elem_t[memLen]();
}

TBitField::TBitField(const TBitField &bf)
    : bitLen(bf.bitLen), memLen(bf.memLen)
{
  pMem = new elem_t[memLen];
  copy(bf.pMem, bf.pMem + bf.memLen, pMem);
}

TBitField::~TBitField()
{
  delete[] pMem;
}

size_t TBitField::GetMemIndex(const size_t n) const // индекс Мем для бита n
{
  return n / bitsInElem;
}

elem_t TBitField::GetMemMask(const size_t n) const // битовая маска для бита n
{
  //return 1 << (n % bitsInElem);
  return 1 << (n & (bitsInElem - 1));
}

inline void TBitField::verify_index(const size_t n) const
{
  if (n >= bitLen)
  {
    throw out_of_range("bit index is out of range");
  }
}

// доступ к битам битового поля

size_t TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const size_t n) // установить бит
{
  verify_index(n);

  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const size_t n) // очистить бит
{
  verify_index(n);
  
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

bool TBitField::GetBit(const size_t n) const // получить значение бита
{
  verify_index(n);
  
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField &TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
  {
    return *this;
  }

  TBitField tmp(bf);
  swap(*this, tmp);
  return *this;
}

bool TBitField::operator==(const TBitField &bf) const noexcept // сравнение
{
  if (bitLen != bf.bitLen)
  {
    return false;
  }

  for (size_t i = 0; i < memLen; i++)
  {
    if (pMem[i] != bf.pMem[i])
    {
      return false;
    }
  }

  return true;
}

bool TBitField::operator!=(const TBitField &bf) const noexcept // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  const bool lhs_larger = bitLen > bf.bitLen;
  const TBitField* rhs = lhs_larger ? &bf : this;

  TBitField res(lhs_larger ? *this : bf);
  for (size_t i = 0; i < res.memLen; i++)
  {
    res.pMem[i] |= rhs->pMem[i];
  }
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField res(max(bitLen, bf.bitLen));
  const size_t minmem = min(memLen, bf.memLen);
  for (size_t i = 0; i < minmem; i++)
  {
    res.pMem[i] = pMem[i] & bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(bitLen);

  for (size_t i = 0; i < memLen - 1; i++)
  {
    res.pMem[i] = ~pMem[i];
  }
  res.pMem[memLen - 1] = pMem[memLen - 1] ^ (maxElem >> (bitsInElem - (bitLen & (bitsInElem - 1))));

  return res;
}

// ввод/вывод

void swap(TBitField &lhs, TBitField &rhs)
{
  swap(lhs.bitLen, rhs.bitLen);
  swap(lhs.memLen, rhs.memLen);
  swap(lhs.pMem, rhs.pMem);
}

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char c;
  for (size_t i = 0; i < bf.bitLen; i++)
  {
    istr >> c;
    if (c == '0')
    {
      bf.ClrBit(i);
    }
    else
    {
      bf.SetBit(i);
    }
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (size_t i = 0; i < bf.bitLen; i++)
  {
    ostr << bf.GetBit(i) ? '1' : '0';
  }
  return ostr;
}
