#ifndef GMATH_VECTOR2_HPP
#define GMATH_VECTOR2_HPP

#include "VectorBase.hpp"
#include <utility>
#include <initializer_list>
#include <cmath>

namespace gmath {
	template<class T>
	class Vector2 : public VectorBase<T, 2> {
	public:
		using Base = VectorBase<T, 2>;

		T& x = Base::_data[0];
		T& y = Base::_data[1];

		template<class Ts>
		Vector2(Ts s) : Base(s, s) {}
		template<class Tx, class Ty>
		Vector2(Tx x, Ty y) : Base(x, y) {}
		template<class To>
		Vector2(const Vector2<To>& o) :
			x(o.x), y(o.y) {}
		Vector2(Vector2&& o) :
			x(std::move(o.x)),
			y(std::move(o.y)) {}
		
		Vector2& operator =(T o) {
			x = o;
			y = o;
			return *this;
		}
		Vector2& operator =(const Vector2& o) {
			x = o.x;
			y = o.y;
			return *this;
		}

		Vector2 operator +() const {
			return {+x, +y};
		}
		Vector2 operator -() const {
			return {-x, -y};
		}
		Vector2 operator ~() const {
			return {~x, ~y};
		}

		auto magnitude() const {
			return sqrt(x * x + y * y);
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
	auto& operator _##=(const Vector2<Tv>& v, Ts s) { \
		v.x _##= s; \
		v.y _##= s; \
		return v; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector2<Ta>& a, const Vector2<Tb>& b) { \
		a.x _##= b.x; \
		a.y _##= b.y; \
		return a; \
	} \
	template<class Ta, class Tb> \
	auto& operator _##=(const Vector2<Ta>& a, const std::initializer_list<Tb>& b) { \
		auto p = b.begin(); \
		a.x _##= *p; \
		a.y _##= *(p + 1); \
		return a; \
	} \
	template<class Tv, class Ts> \
	auto operator _(const Vector2<Tv>& v, Ts s) { \
		return Vector2<decltype(v.x _ s)>(v.x _ s, v.y _ s); \
	} \
	template<class Ta, class Tb> \
	auto operator _(const Vector2<Ta>& a, const Vector2<Tb>& b) { \
		return Vector2<decltype(a.x _ b.x)>(a.x _ b.x, a.y _ b.y); \
	} \
	template<class Ts, class Tv> \
	auto operator _(Ts s, const Vector2<Tv>& v) { \
		return Vector2<decltype(s _ v.x)>(s _ v.x, s _ v.y); \
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