#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class Scene {
public:
    using ptr_t = std::unique_ptr<Object>;
    using data_t = std::vector<ptr_t>;
    using iterator = data_t::iterator;
    using const_iterator = data_t::const_iterator;

    Scene& addObject(Object* obj) {
        objects.push_back(ptr_t(obj));
        return *this;
    }

    iterator begin() { return objects.begin(); }
    iterator end() { return objects.end(); }
    const_iterator begin() const { return objects.begin(); }
    const_iterator end() const { return objects.end(); }

private:
    data_t objects;
    //Camera camera;
    //data_t lights;
};