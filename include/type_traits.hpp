#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	//////////// is_integral /////////////////////
    template <typename T>
    struct is_integral
    {
        static const bool value = false;
    };

    template <>
    struct is_integral<long long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<short int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned short int>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };
	///////////////// is_pointer ////////////////////

	template <typename T>
	struct is_pointer
	{
		static const bool value = false;
	};

	template <typename T>
	struct is_pointer<T *>
	{
		static const bool value = true;
	};

	template <bool Cond, typename T = void>
	struct enable_if
	{
	};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T>
	struct is_void
	{
		static const bool value = false;
	};
	template <>
	struct is_void<void>
	{
		static const bool value = true;
	};
}
#endif