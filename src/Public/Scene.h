#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class Scene {
public:
    using value = std::unique_ptr<Object>;
    using data_t = std::vector<value>;
    //using iterator = data_t::iterator;
    //using const_iterator = data_t::const_iterator;

    Scene& addObject(Object* obj) {
        objects.push_back(value(obj));
        return *this;
    }

    const data_t& getObjects() const { return objects; }

    /*
    iterator begin() { return objects.begin(); }
    iterator end() { return objects.end(); }
    const_iterator begin() const { return objects.begin(); }
    const_iterator end() const { return objects.end(); }
     */

private:
    data_t objects;
};