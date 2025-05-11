#include "main.hpp"

template <typename T>
bool findInVec(const v<T> &vec, const T &val){
    return std::find(vec.begin(), vec.end(), val) != vec.end();
    
}