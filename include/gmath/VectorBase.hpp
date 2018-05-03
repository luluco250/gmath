#ifndef GMATH_VECTORBASE_HPP
#define GMATH_VECTORBASE_HPP

#include <array>

namespace gmath {
	template<class T, size_t N>
	class VectorBase {
	protected:
		T _data[N];

	public:
		template<class... Ta>
		constexpr VectorBase(Ta... args) : _data{args...} {}
		constexpr VectorBase(std::array<T, N> args) : _data(args) {}

		constexpr T& operator [](size_t i) { return _data[i]; }
		constexpr const T& operator [](size_t i) const { return _data[i]; }
		constexpr T* begin() { return _data; }
		constexpr T* end() { return _data + N; }
		constexpr const T* cbegin() const { return _data; }
		constexpr const T* cend() const { return _data + N; }
		constexpr T* data() { return _data; }
		constexpr const T* data() const { return _data; }
	};
}

#endif