// Implementation of TypeSafeEnum is my interpretation of code from http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum
#pragma once


namespace Lizurd
{
	template<typename T, typename U = typename T::type>
	class TypeSafeEnum : public T
	{
	public:
		TypeSafeEnum() : mValue() {}
		TypeSafeEnum(U v) : mValue(v) {}

		U Underlying() const { return mValue; }

		bool operator == (const TypeSafeEnum &other) const { return mValue == other.mValue; }
		bool operator != (const TypeSafeEnum &other) const { return mValue != other.mValue; }
		bool operator <  (const TypeSafeEnum &other) const { return mValue <  other.mValue; }
		bool operator <= (const TypeSafeEnum &other) const { return mValue <= other.mValue; }
		bool operator >  (const TypeSafeEnum &other) const { return mValue >  other.mValue; }
		bool operator >= (const TypeSafeEnum &other) const { return mValue >= other.mValue; }

	private:
		U mValue;
	};

}