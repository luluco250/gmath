#ifndef GMATH_VECTOR3_HPP
#define GMATH_VECTOR3_HPP

#include "VectorBase.hpp"
#include <utility>
#include <initializer_list>
#include <cmath>

namespace gmath {
	template<class T>
	class Vector3 : public VectorBase<T, 3> {
	public:
		using Base = VectorBase<T, 3>;

		T& x = Base::_data[0];
		T& y = Base::_data[1];
		T& z = Base::_data[2];

		template<class Ts>
		Vector3(Ts s) : Base(s, s, s) {}
		template<class Tx, class Ty, class Tz>
		Vector3(Tx x, Ty y, Tz z) : Base(x, y, z) {}
		template<class To>
		Vector3(const Vector3<To>& o) :
			x(o.x), y(o.y), z(o.z) {}
		Vector3(Vector3&& o) :
			x(std::move(o.x)),
			y(std::move(o.y)),
			z(std::move(o.z)) {}
		
		Vector3& operator =(T o) {
			x = o;
			y = o;
			z = o;
			return *this;
		}
		Vector3& operator =(const Vector3& o) {
			x = o.x;
			y = o.y;
			z = o.z;
			return *this;
		}

		Vector3 operator +() const {
			return {+x, +y, +z};
		}
		Vector3 operator -() const {
			return {-x, -y, -z};
		}
		Vector3 operator ~() const {
			return {~x, ~y, ~z};
		}

		auto magnitude() const {
			return sqrt(x * x + y * y + z * z);
		}
		template<class T>
		void magnitude(T arg) {
			*this /= magnitude();
			*this *= arg;
		}

		auto normalized() {
			return *this / magnitude();
		}
	};

	#define MAKE_OP(_) \
	template<class Tv, class Ts> \
	auto& operator _##=(const Vector3<Tv>& v, Ts s) { \
		v.x _##= s; \
		v.y _##= s; \
		v.z _##= s; \
		return v; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector3<Ta>& a, const Vector3<Tb>& b) { \
		a.x _##= b.x; \
		a.y _##= b.y; \
		a.z _##= b.z; \
		return a; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector3<Ta>& a, const std::initializer_list<Tb>& b) { \
		auto p = b.begin(); \
		a.x _##= *p; \
		a.y _##= *(p + 1); \
		a.z _##= *(p + 2); \
		return a; \
	} \
	template<class Tv, class Ts> \
	auto operator _(const Vector3<Tv>& v, Ts s) { \
		return Vector3<decltype(v.x _ s)>(v.x _ s, v.y _ s, v.z _ s); \
	} \
	template<class Ta, class Tb> \
	auto operator _(const Vector3<Ta>& a, const Vector3<Tb>& b) { \
		return Vector3<decltype(a.x _ b.x)>(a.x _ b.x, a.y _ b.y, a.z _ b.z); \
	} \
	template<class Ts, class Tv> \
	auto operator _(Ts s, const Vector3<Tv>& v) { \
		return Vector3<decltype(s _ v.x)>(s _ v.x, s _ v.y, s _ v.z); \
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