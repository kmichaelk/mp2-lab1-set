// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

#include "tbitfield.h"

class TSet
{
private:
  size_t maxPower;       // максимальная мощность множества
  TBitField bitField; // битовое поле для хранения характеристического вектора
public:
  TSet(size_t mp);
  TSet(const TSet &s);       // конструктор копирования
  TSet(const TBitField &bf); // конструктор преобразования типа
  operator TBitField();      // преобразование типа к битовому полю
  // доступ к битам
  size_t GetMaxPower(void) const;         // максимальная мощность множества
  void InsElem(const size_t elem);        // включить элемент в множество
  void DelElem(const size_t elem);        // удалить элемент из множества
  bool IsMember(const size_t elem) const; // проверить наличие элемента в множестве
  // теоретико-множественные операции
  bool operator== (const TSet &s) const; // сравнение
  bool operator!= (const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);     // присваивание
  TSet operator+ (const size_t elem); // объединение с элементом
                                      // элемент должен быть из того же универса
  TSet operator- (const size_t elem); // разность с элементом
                                      // элемент должен быть из того же универса
  TSet operator+ (const TSet &s);     // объединение
  TSet operator* (const TSet &s);     // пересечение
  TSet operator~ (void);              // дополнение

  friend void swap(TSet &lhs, TSet &rhs);

  friend istream &operator>>(istream &istr, TSet &bf);
  friend ostream &operator<<(ostream &ostr, const TSet &bf);
};

#endif // __SET_H__
