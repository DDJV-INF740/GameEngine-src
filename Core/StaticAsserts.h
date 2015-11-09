#pragma once

namespace engine
{
	//-------------------------------------------------------------------------
	// ensures that provided types support a TypeId() method
	namespace _internal
	{
		template <typename T>
		class has_typeid_static_method
		{
			using one = char;
			using two = long;

			template <typename C> static one test(decltype(C::TypeId()));
			template <typename C> static two test(...);

		public:
			enum { value = sizeof(test<T>("")) == sizeof(one) };
		};
	} // namespace _internal

	namespace _internal {
		template <typename T>
		class has_ref_method
		{
			using one = char;
			using two = long;

			template <typename C> static one test(decltype(&C::ref));
			//template <typename C> static two test(...);

		public:
			enum { value = sizeof(test<T>(0)) == sizeof(one) };
		};
	}

}