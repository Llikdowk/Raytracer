# Very simple raytracer
Made in C++11.

Features:
* Renders only sphere primitives without shadowing
* Reflection
* Refraction
* Blinn-Phong illumination modified with a fake fresnel
* Multithreaded (used OpenMP to apply a simple SIMD parallelization)

Output image sample:

![img1](http://i.imgur.com/VELcGat.jpg)
