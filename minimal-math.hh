#pragma once

#include "probabilistic-quadrics.hh"

/// This header contains a minimal vector math library needed to use probabilistic-quadrics.hh
/// Note that many other 3rd party libraries are also supported
///
/// Usage:
///   minimal_math<float>
///   minimal_math<double>

namespace pq
{
// ============== Forward Declarations ==============

template <int D, class ScalarT>
struct vec;
template <int D, class ScalarT>
struct pos;
template <int C, int R, class ScalarT>
struct mat;

using vec3 = vec<3, float>;
using pos3 = pos<3, float>;
using mat3 = mat<3, 3, float>;

using dvec3 = vec<3, double>;
using dpos3 = pos<3, double>;
using dmat3 = mat<3, 3, double>;

template <class ScalarT>
using minimal_math = math<ScalarT, pos<3, ScalarT>, vec<3, ScalarT>, mat<3, 3, ScalarT>>;


// ============== Types ==============

template <class ScalarT>
struct vec<3, ScalarT>
{
    ScalarT x = ScalarT(0);
    ScalarT y = ScalarT(0);
    ScalarT z = ScalarT(0);

    ScalarT& operator[](int i) { return (&x)[i]; }
    ScalarT const& operator[](int i) const { return (&x)[i]; }
};

template <class ScalarT>
struct pos<3, ScalarT>
{
    ScalarT x = ScalarT(0);
    ScalarT y = ScalarT(0);
    ScalarT z = ScalarT(0);

    ScalarT& operator[](int i) { return (&x)[i]; }
    ScalarT const& operator[](int i) const { return (&x)[i]; }
};

template <int C, int R, class ScalarT>
struct mat
{
private:
    vec<R, ScalarT> m[C];

public:
    vec<R, ScalarT>& operator[](int i) { return m[i]; }
    vec<R, ScalarT> const& operator[](int i) const { return m[i]; }
};


// ============== Operations ==============

template <class T>
vec<3, T> operator*(vec<3, T> const& v, T const& s)
{
    return {v.x * s, v.y * s, v.z * s};
}

template <class T>
vec<3, T> operator*(mat<3, 3, T> const& A, vec<3, T> const& b)
{
    return {
        A[0][0] * b.x + A[1][0] * b.y + A[2][0] * b.z, //
        A[0][1] * b.x + A[1][1] * b.y + A[2][1] * b.z, //
        A[0][2] * b.x + A[1][2] * b.y + A[2][2] * b.z, //
    };
}

template <class T>
mat<3, 3, T> operator*(mat<3, 3, T> m, T const& s)
{
    m[0] = m[0] * s;
    m[1] = m[1] * s;
    m[2] = m[2] * s;
    return m;
}

template <class T>
vec<3, T> operator+(vec<3, T> const& a, vec<3, T> const& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

template <class T>
vec<3, T> operator-(vec<3, T> const& a, vec<3, T> const& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <class T>
mat<3, 3, T> operator+(mat<3, 3, T> const& a, mat<3, 3, T> const& b)
{
    mat<3, 3, T> r;
    r[0] = a[0] + b[0];
    r[1] = a[1] + b[1];
    r[2] = a[2] + b[2];
    return r;
}

template <class T>
mat<3, 3, T> operator-(mat<3, 3, T> const& a, mat<3, 3, T> const& b)
{
    mat<3, 3, T> r;
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
    r[2] = a[2] - b[2];
    return r;
}

} // namespace pq
