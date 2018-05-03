#ifndef GMATH_VECTOR4_HPP
#define GMATH_VECTOR4_HPP

#include "VectorBase.hpp"
#include <utility>
#include <cmath>
#include <initializer_list>
#include "Vector3.hpp"
#include "Vector2.hpp"

namespace gmath {
	template<class T>
	class Vector4 : public VectorBase<T, 4> {
	public:
		using Base = VectorBase<T, 4>;

		T& x = Base::_data[0];
		T& y = Base::_data[1];
		T& z = Base::_data[2];
		T& w = Base::_data[3];

		template<class Ts>
		constexpr Vector4(Ts s) : Base(s, s, s, s) {}
		template<class Tx, class Ty, class Tz, class Tw>
		constexpr Vector4(Tx x, Ty y, Tz z, Tw w) : Base(x, y, z, w) {}
		template<class To>
		constexpr Vector4(const Vector4<To>& o) :
			x(o.x), y(o.y), z(o.z), w(o.w) {}
		constexpr Vector4(Vector4&& o) :
			x(std::move(o.x)),
			y(std::move(o.y)),
			z(std::move(o.z)),
			w(std::move(o.w)) {}
		
		template<class To>
		Vector4& operator =(To o) {
			x = o;
			y = o;
			z = o;
			w = o;
			return *this;
		}
		template<class To>
		Vector4& operator =(const Vector4<To>& o) {
			x = o.x;
			y = o.y;
			z = o.z;
			w = o.w;
			return *this;
		}

		Vector4 operator +() const {
			return {+x, +y, +z, +w};
		}
		Vector4 operator -() const {
			return {-x, -y, -z, -w};
		}
		Vector4 operator ~() const {
			return {~x, ~y, ~z, ~w};
		}

		auto magnitude() const {
			return sqrt(x * x + y * y + z * z + w * w);
		}
		template<class T>
		void magnitude(T arg) {
			*this /= magnitude();
			*this *= arg;
		}

		auto normalized() {
			return *this / magnitude();
		}

		template<int x>
		constexpr T swizzle() const {
			return *(Base::cbegin() + x);
		}

		template<int x, int y>
		constexpr Vector2<T> swizzle() const {
			auto p = Base::cbegin();
			return {
				*(p + x),
				*(p + y)
			};
		}

		template<int x, int y, int z>
		constexpr Vector3<T> swizzle() const {
			auto p = Base::cbegin();
			return {
				*(p + x),
				*(p + y),
				*(p + z)
			};
		}

		template<int x, int y, int z, int w>
		constexpr Vector4 swizzle() const {
			auto p = Base::cbegin();
			return {
				*(p + x),
				*(p + y),
				*(p + z),
				*(p + w)
			};
		}
	};

	#define MAKE_OP(_) \
	template<class Tv, class Ts> \
	auto& operator _##=(const Vector4<Tv>& v, Ts s) { \
		v.x _##= s; \
		v.y _##= s; \
		v.z _##= s; \
		v.w _##= s; \
		return v; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector4<Ta>& a, const Vector4<Tb>& b) { \
		a.x _##= b.x; \
		a.y _##= b.y; \
		a.z _##= b.z; \
		a.w _##= b.w; \
		return a; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector4<Ta>& a, const std::initializer_list<Tb>& b) { \
		auto p = b.begin(); \
		a.x _##= *p; \
		a.y _##= *(p + 1); \
		a.z _##= *(p + 2); \
		a.w _##= *(p + 3); \
		return a; \
	} \
	template<class Tv, class Ts> \
	auto operator _(const Vector4<Tv>& v, Ts s) { \
		return Vector4<decltype(v.x _ s)>(v.x _ s, v.y _ s, v.z _ s, v.w _ s); \
	} \
	template<class Ta, class Tb> \
	auto operator _(const Vector4<Ta>& a, const Vector4<Tb>& b) { \
		return Vector4<decltype(a.x _ b.x)>(a.x _ b.x, a.y _ b.y, a.z _ b.z, a.w _ b.w); \
	} \
	template<class Ts, class Tv> \
	auto operator _(Ts s, const Vector4<Tv>& v) { \
		return Vector4<decltype(s _ v.x)>(s _ v.x, s _ v.y, s _ v.z, s _ v.w); \
	} \
	template<class Ts, class Tv> \
	auto operator _(Ts s, const std::array<Tv, 4>& v) { \
		return Vector4<decltype(s _ v[0])>(s _ v.x, s _ v.y, s _ v.z, s _ v.w); \
	}

	MAKE_OP(+)
	MAKE_OP(-)
	MAKE_OP(*)
	MAKE_OP(/)
	MAKE_OP(%)
	MAKE_OP(&)
	MAKE_OP(|)
	MAKE_OP(^)
	MAKE_OP(<<)
	MAKE_OP(>>)

	#undef MAKE_OP
}

#endif