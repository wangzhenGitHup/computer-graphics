#ifndef  __SELF__MATHS__H__
#define __SELF__MATHS__H__

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef EPSILON
#define EPSILON 0.01f
#endif

#define  FLT_ZERO (float)0.000000000000001
#define  FLT_EQUAL(f1, f2) (fabs((f1)-(f2)) <= FLT_ZERO)
#define  FLT_IS_ZERO(d) (fabs((d) - FLT_ZERO) <= FLT_ZERO)


#endif