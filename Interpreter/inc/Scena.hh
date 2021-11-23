#ifndef SCENA_HH
#define SCENA_HH


#include <string>
#include "Vector3D.hh"
#include "MobileObj.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Scena
 *
 * Plik zawiera definicję klasy Scena.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */




   /*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    */
    class Scena {

     public:
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
	MobileObj* FindMobileObj(const char *sName);
	void AddMobileObj(MobileObj *pMobObj);
#endif
