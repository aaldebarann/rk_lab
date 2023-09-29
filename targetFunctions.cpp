#include "targetFunctions.h"

Pair task3(double x, Pair u) {
    return {u.second, -std::sin(x)};
}
