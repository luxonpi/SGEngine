

#ifndef SGENGINE_BASE_H
#define SGENGINE_BASE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <memory>
#include <bitset>
#include <set>
#include <unordered_map>
#include <list>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix.h"
#include "Quaternion.h"

#include "Color.h"

#include "SMath.h"
#include "SString.h"

#include "GraphicDevice.h"
#include "GraphicDeviceDefines.h"

inline float clamp(float v, float min, float max){
    
    if(v<min) return min;
    if(v>max) return max;
    
    return v;
    
}

#endif 

// Common
#ifndef NULL
#define NULL     0
#endif

#ifndef NO
#define NO     0
#endif

#ifndef YES
#define YES    1
#endif

typedef int32_t SEnum;
typedef unsigned int SUint;
typedef int SInt;
typedef uint8_t SByte;
typedef uint16_t SShort;
typedef float_t SFloat;


void _Error(const char* file, int line, const std::string& message);
void _Log(const std::string& message);

#define log(string) _Log(string)
#define error(string) _Error(__FILE__, __LINE__, string)