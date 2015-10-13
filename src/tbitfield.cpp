// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len<=0)
		throw len;
	BitLen = len;
	MemLen = (len/(sizeof(TELEM)*8))+1;
	pMem = new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
		pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen= bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int Pos=n%(sizeof(TELEM)*8);
	TELEM tmp=1;
	tmp=tmp<<Pos;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0)||(n>=BitLen))
		throw n;
	int Ind = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[Ind] = pMem[Ind]|mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0)||(n>=BitLen))
		throw n;
	int Ind = GetMemIndex(n);
	TELEM mask = ~GetMemMask(n);
	pMem[Ind] = pMem[Ind]&mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0)||(n>=BitLen))
		throw n;
	int Ind = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	if (pMem[Ind]&mask)
        return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen!=bf.BitLen)
	{
		delete [] pMem;
		pMem = new TELEM[bf.MemLen];
		MemLen = bf.MemLen;
		BitLen=bf.BitLen;
	}
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
	return (*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen!=bf.BitLen)
		return 0;
	for (int i=0;i<BitLen;i++)
		if (GetBit(i)!=bf.GetBit(i))
			return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen!=bf.BitLen)
		return 1;
	for (int i=0;i<BitLen;i++)
		if (GetBit(i)!=bf.GetBit(i))
			return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int _BitLen;
	if (BitLen>bf.BitLen)
		_BitLen=BitLen;
	else
		_BitLen=bf.BitLen;
	TBitField cbf(_BitLen);
	for (int i=0;i<MemLen;i++)
		cbf.pMem[i] = pMem[i]|bf.pMem[i];
	return cbf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int _BitLen;
	if (BitLen>bf.BitLen)
		_BitLen=BitLen;
	else
		_BitLen=bf.BitLen;
	TBitField cbf(_BitLen);
	for (int i=0;i<MemLen;i++)
		cbf.pMem[i] = pMem[i]&bf.pMem[i];
	return cbf;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField cbf(BitLen);
	for (int i=0;i<MemLen;i++)
		cbf.pMem[i] = ~pMem[i];
	return cbf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char n='0';
	istr>>n;
	while (((n=='0')||(n=='1'))&&(i<bf.BitLen))
	{
		if (n=='0')
			bf.ClrBit(i);
		else bf.SetBit(i);
		i++;
		istr>>n;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0;i<bf.BitLen;i++)
		ostr<<bf.GetBit(i);
	return ostr;
}
