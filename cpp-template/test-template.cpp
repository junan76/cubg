#include <iostream>
#include <cmath>
#include <gtest/gtest.h>

using namespace std;

template <typename T, typename RetType, typename... ArgsType>
class Functor
{
public:
    typedef RetType (T::*method_type)(ArgsType... args);

    Functor(T *obj, method_type method) : _obj(obj), _method(method)
    {
    }

    RetType operator()(ArgsType... args)
    {
        return (_obj->*_method)(args...);
    }

    static Functor<T, RetType, ArgsType...> bind(T *obj, method_type method)
    {
        return Functor(obj, method);
    }

private:
    T *_obj;
    method_type _method;
};

class Vector2d
{
public:
    Vector2d() : _x(0), _y(0)
    {
    }

    Vector2d(double x, double y) : _x(x), _y(y)
    {
    }

    double length(void)
    {
        return sqrt(_x * _x + _y * _y);
    }

private:
    double _x;
    double _y;
};

TEST(test_template, test1)
{

    Vector2d v1(3, 4);
    Vector2d v2(6, 8);

    Functor<Vector2d, double> f1(&v1, &Vector2d::length);
    auto f2 = Functor<Vector2d, double>::bind(&v2, &Vector2d::length);

    cout << f1() << endl
         << f2() << endl;
}
