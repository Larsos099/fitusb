#pragma once
#include "main.hpp"

template <typename T>
bool findInVec(const v<T> &vec, const T &val){
    return std::find(vec.begin(), vec.end(), val) != vec.end();
    
}
template <typename T>
int whereInVec(const v<T> &vec, const T &val){
    auto element = std::find(vec.begin(), vec.end(), val);
    if(element == vec.end()) throw std::runtime_error("Element " + s(val) + " not found in Vector.");
    return std::distance(vec.begin(), element);
}
int whereInVec(const v<s> &vec, const s &val){
    auto element = std::find(vec.begin(), vec.end(), val);
    if(element == vec.end()) throw std::runtime_error("Element " + val + " not found in Vector.");
    return std::distance(vec.begin(), element);
}
bool findInVec(const v<s>  &vec, const s &val){

    return std::find(vec.begin(), vec.end(), val) != vec.end();
}
bool findInStr(const s &stfi, const s &val){
    return stfi.find(val) != std::string::npos;
}
std::pair<bool, int> findInArgs(v<s> &argl, s &val) {
    bool e = findInVec(argl, val);
    int p = whereInVec(argl, val);
    return {e, p};
}