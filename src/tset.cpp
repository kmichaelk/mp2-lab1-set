// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(size_t mp)
    : maxPower(mp), bitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s)
    : maxPower(s.maxPower), bitField(s.bitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf)
    : maxPower(bf.GetLength()), bitField(bf)
{
}

TSet::operator TBitField()
{
  return bitField;
}

size_t TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

bool TSet::IsMember(const size_t elem) const // элемент множества?
{
  return bitField.GetBit(elem);
}

void TSet::InsElem(const size_t elem) // включение элемента множества
{
  bitField.SetBit(elem);
}

void TSet::DelElem(const size_t elem) // исключение элемента множества
{
  bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet &TSet::operator=(const TSet &s) // присваивание
{
  if (this == &s)
  {
    return *this;
  }

  TSet tmp(s);
  swap(*this, tmp);
  return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
  return maxPower == s.maxPower && bitField == s.bitField;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
  return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  return TSet(bitField | s.bitField);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  return TSet(bitField & s.bitField);
}

TSet TSet::operator+(const size_t Elem) // объединение с элементом
{
  TSet res(*this);
  res.InsElem(Elem);
  return res;
}

TSet TSet::operator-(const size_t Elem) // разность с элементом
{
  TSet res(*this);
  res.DelElem(Elem);
  return res;
}

TSet TSet::operator~(void) // дополнение
{
  return TSet(~bitField);
}

// перегрузка ввода/вывода

void swap(TSet &lhs, TSet &rhs)
{
  swap(lhs.maxPower, rhs.maxPower);
  swap(lhs.bitField, rhs.bitField);
}

istream &operator>>(istream &istr, TSet &s) // ввод
{
  istr >> s.bitField;
  return istr;
}

ostream &operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << s.bitField;
  return ostr;
}
