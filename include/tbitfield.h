// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;


typedef unsigned int elem_t;

class TBitField
{
private:
  size_t  bitLen; // длина битового поля - макс. к-во битов
  size_t  memLen; // к-во эл-тов Мем для представления бит.поля
  elem_t *pMem; // память для представления битового поля

  // методы реализации
  size_t GetMemIndex(const size_t n) const; // индекс в pМем для бита n       (#О2)
  elem_t GetMemMask (const size_t n) const; // битовая маска для бита n       (#О3)

  void verify_index(const size_t n) const;
public:
  TBitField(size_t len);             //                                       (#О1)
  TBitField(const TBitField &bf);    //                                       (#П1)
  ~TBitField();                      //                                        (#С)

  // доступ к битам
  size_t GetLength(void) const;      // получить длину (к-во битов)            (#О)
  void SetBit(const size_t n);       // установить бит                        (#О4)
  void ClrBit(const size_t n);       // очистить бит                          (#П2)
  bool GetBit(const size_t n) const; // получить значение бита                (#Л1)

  // битовые операции
  bool operator==(const TBitField &bf) const noexcept; // сравнение           (#О5)
  bool operator!=(const TBitField &bf) const noexcept; // сравнение
  TBitField& operator=(const TBitField &bf);           // присваивание        (#П3)
  TBitField  operator|(const TBitField &bf);           // операция "или"      (#О6)
  TBitField  operator&(const TBitField &bf);           // операция "и"        (#Л2)
  TBitField  operator~(void);                          // отрицание            (#С)

  friend void swap(TBitField &lhs, TBitField &rhs);

  friend istream &operator>>(istream &istr, TBitField &bf);       //          (#О7)
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); //          (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif // __BITFIELD_H__