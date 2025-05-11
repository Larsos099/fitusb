#include "main.hpp"

template <typename T>
bool findInVec(const v<T> &vec, const T &val){
    return std::find(vec.begin(), vec.end(), val) != vec.end();
    
}
bool findInVec(const v<s>  &vec, const s &val){

    return std::find(vec.begin(), vec.end(), val) != vec.end();
}
bool findInStr(const s &stfi, const s &val){
    return stfi.find(val) != std::string::npos;
}