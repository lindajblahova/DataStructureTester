#pragma once

#include "ds_structure_types.h";

#include <limits>

namespace structures {

	/// <summary> 
	/// Kniznicna trieda obsahujuca rutinne metody pre pracu s pamatou.
	/// </summary
	template<typename T>
	class MemoryRoutines
	{
	public:
		/// <summary> MAximalna hodnota T-u. </summary>
		//const static T MAX_T = 255;

		/// <summary> Nastavi vsetky bity v T na 1. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TSet(T& B);

		/// <summary> Nastavi vsetky bity v T na 0. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TReset(T& B);

		/// <summary> Vykona operaciu XOR nad T. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TXOR(T& B);

		/// <summary> Vykona operaciu AND nad T. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T TAND(T B, T A);


		/// <summary> Vykona operaciu OR nad T. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T TOR(T B, T A);

		/// <summary> Posunie T o 1 dolava. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TSHL(T& B);

		/// <summary> Posunie T o 1 doprava. </summary>
		/// <param name = "B"> T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TSHR(T& B);

		/// <summary> Vrati hodnotu n-teho bitu v T. </summary>
		/// <param name = "B"> T. </param>
		/// <param name = "n"> Poradie bitu v T. </param>
		/// <returns> Hodnota n-teho bitu v T. </returns>
		static bool TNthBitGet(T B, int n);

		/// <summary> Nastavi hodnotu n-teho bitu v T na 0. </summary>
		/// <param name = "B"> T. </param>
		/// <param name = "n"> Poradie bitu v T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TNthBitTo0(T& B, int n);

		/// <summary> Nastavi hodnotu n-teho bitu v na 1. </summary>
		/// <param name = "B"> T. </param>
		/// <param name = "n"> Poradie bitu v T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TNthBitTo1(T& B, int n);

		/// <summary> Prepne hodnotu n-teho bitu v T (teda z 0 na 1 a opacne). </summary>
		/// <param name = "B"> T. </param>
		/// <param name = "n"> Poradie bitu v T. </param>
		/// <returns> Upraveny T. </returns>
		static T& TNthBitToggle(T& B, int n);
	private:
		/// <summary> Sukromny konstruktor znemoznuje vytvorenie instancie kniznicnej triedy. </summary>
		MemoryRoutines();
	};

	template<typename T>
	T& MemoryRoutines<T>::TSet(T& B)
	{
		B = std::numeric_limits<T>::max();
		return B;
	}

	template<typename T>
	T& MemoryRoutines<T>::TReset(T& B)
	{
		// vynuluj cely T
		B = 0;
		return B;
	}

	template<typename T>
	T& MemoryRoutines<T>::TXOR(T& B)
	{
		// urob xor na T a vrat ho
		B ^= B;
		return B;
	}

	template<typename T>
	T MemoryRoutines<T>::TAND(T B, T A)
	{
		// urob and na B a A a vrat B
		return B & A;
	}

	template<typename T>
	T MemoryRoutines<T>::TOR(T B, T A)
	{
		// urob or na B a A a vrat B
		return B | A;
	}

	template<typename T>
	T& MemoryRoutines<T>::TSHL(T& B)
	{
		// urob posun o 1 vlavo 
		B <<= 1;
		return B;
	}

	template<typename T>
	T& MemoryRoutines<T>::TSHR(T& B)
	{
		// urob posun o 1 vpravo 
		B >>= 1;
		return B;
	}

	template<typename T>
	bool MemoryRoutines<T>::TNthBitGet(T B, int n)
	{
		// posun kopiu B o n miest a and s 1 , iba 1&1 je 1
		return (B >> n) & 1;
	}

	template<typename T>
	T& MemoryRoutines<T>::TNthBitTo0(T& B, int n)
	{
		//posun si 1 o n miest, zneguj (11101111) a urob &, vrat B
		B &= ~(1 << n);
		return B;
	}

	template<typename T>
	T& MemoryRoutines<T>::TNthBitTo1(T& B, int n)
	{
		//posun si 1 o n miest a urob or (1|0, 0|1, 1|1 = 1), vrat B
		B |= 1 << n;
		return B;
	}

	template<typename T>
	T& MemoryRoutines<T>::TNthBitToggle(T& B, int n)
	{
		// posun si 1 o n miest a urob xor (0^1 = 1, 1^1 = 0)
		B ^= 1 << n;
		return B;
	}

	template<typename T>
	MemoryRoutines<T>::MemoryRoutines()
	{
	}

}

