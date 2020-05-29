# Probabilistic Quadrics

Reference implementation of the Eurographics 2020 paper "Fast and Robust QEF Minimization using Probabilistic Quadrics".

Publication page: https://graphics.rwth-aachen.de/probabilistic-quadrics

Eurographics DL: https://diglib.eg.org/handle/10.1111/cgf13933

```
@article {10.1111:cgf.13933,
    journal = {Computer Graphics Forum},
    title = {{Fast and Robust QEF Minimization using Probabilistic Quadrics}},
    author = {Trettner, Philip and Kobbelt, Leif},
    year = {2020},
    publisher = {The Eurographics Association and John Wiley & Sons Ltd.},
    ISSN = {1467-8659},
    DOI = {10.1111/cgf.13933}
}
```


## Dependencies

* a C++17 compiler


## Usage

```cpp
// our probabilistic quadrics
#include "probabilistic-quadrics.hh"

// some math library (see below for different options)
#include "minimal-math.hh"

// optional: typedef your quadric type
using quadric3 = pq::quadric<pq::minimal_math<float>>;
using dquadric3 = pq::quadric<pq::minimal_math<double>>;

// quadrics are value types with proper operator overloads
quadric3 q;
q = q + q;
q = q - q;
q = q * 3;
q = q / 2.5f;

// quadrics can be evaluated at positions
q(1, 2, 3);
q({1, 2, 3});
q(some_pos);

// quadrics can be created from coefficients
q = quadric3::from_coefficients(some_mat3, some_vec3, some_scalar);

// quadric minimizers can be computed (using matrix inversion internally)
pq::pos3 min_p = q.minimizer();

// some classical quadrics are predefined:
q = quadric3::point_quadric(some_pos);
q = quadric3::plane_quadric(some_pos, some_normal_vec);
q = quadric3::triangle_quadric(p0, p1, p2);

// our probabilistic plane quadrics in isotropic or general form:
float stddev_pos = ...;
float stddev_normal = ...;
pq:mat3 sigma_pos = ...;
pq:mat3 sigma_normal = ...;
q = quadric3::probabilistic_plane_quadric(mean_pos, mean_normal, stddev_pos, stddev_normal);
q = quadric3::probabilistic_plane_quadric(mean_pos, mean_normal, sigma_pos, sigma_normal);

// our probabilistic triangle quadrics in isotropic or general form:
float stddev_pos = ...;
pq:mat3 sigma_p0 = ...;
pq:mat3 sigma_p1 = ...;
pq:mat3 sigma_p2 = ...;
q = quadric3::probabilistic_triangle_quadric(p0, p1, p2, stddev_pos);
q = quadric3::probabilistic_triangle_quadric(p0, p1, p2, sigma_p0, sigma_p1, sigma_p2);
```



## Math Class

Our code is written to be largely agnostic to the choice of the math library.
The `quadric` type is templated on a trait class that abstracts the math code away.
Different types for positions and vectors are supported but not required.

```cpp
template <class ScalarT, class Pos3, class Vec3, class Mat3>
struct math;
```

The following math classes are tested:

* the built-in minimal-math.hh:
  ```cpp
  #include "minimal-math.hh"
  pq::minimal_math<float>
  pq::minimal_math<double>
  ```

* Typed Geometry:
  ```cpp
  #include <typed-geometry/tg.hh>
  pq::math<float, tg::pos3, tg::vec3, tg::mat3>
  pq::math<double, tg::dpos3, tg::dvec3, tg::dmat3>
  ```

* GLM:
  ```cpp
  #include <glm/glm.hpp>
  pq::math<float, glm::vec3, glm::vec3, glm::mat3>
  pq::math<double, glm::dvec3, glm::dvec3, glm::dmat3>
  ```

* Eigen:
  ```cpp
  #include <eigen3/Eigen/Core>
  pq::math<float, Eigen::Vector3f, Eigen::Vector3f, Eigen::Matrix3f>
  pq::math<double, Eigen::Vector3d, Eigen::Vector3d, Eigen::Matrix3d>
  ```

To make your custom math library work, it needs to provide the following operations:
  - `pos - pos -> vec`
  - `pos + vec -> pos`
  - `pos - vec -> pos`
  - `vec + vec -> vec`
  - `vec - vec -> vec`
  - `vec * scalar -> vec`
  - `vec / scalar -> vec`
  - `pos * scalar -> pos`
  - `pos / scalar -> pos`
  - `mat * scalar -> mat`
  - `mat * vec -> vec`
  - `mat + mat -> mat`
  - `mat - mat -> mat`
  - `pos[int-literal] -> scalar&`
  - `vec[int-literal] -> scalar&`
  - `mat[col][row] -> scalar&` OR `mat(row, col) -> scalar&`
  - `mat`, `pos` and `vec` default constructor
  - `mat`, `pos`, `vec`, and `scalar` behave like value types
  - `scalar` must be constructable from integer literals
where
  - pos is a 3D position type
  - vec is a 3D vector type
  - pos and vec can be the same, e.g. glm::vec3
  - mat is a 3x3 matrix type


## License

This code is licensed under the MIT license.

