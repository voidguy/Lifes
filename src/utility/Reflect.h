
#pragma once

class Reflect {
public:
    typedef uint16_t IdType;
    typedef void *(RfType)();
    Reflect(IdType id, RfType rf) {
        id_rf_map[id] = rf; 
    }   
public:
    template <class T> static T* construct(IdType id) {
        return id < max_id && id_rf_map[id] != 0 ? reinterpret_cast<T*>(id_rf_map[id]()) : 0;
    }   
    template <class T> static void destroy(T *ptr) {
        delete ptr;
    }   
public:
    static const size_t max_id = 0x10000;
private:
    static const RfType* id_rf_map[max_id];
};

const Reflect::RfType* Reflect::id_rf_map[Reflect::max_id] = {0};


#define DECLARE_REFLECT(class_name, classid) private:\
    static void *__rf_func__() {return new class_name;}\
    static const Reflect __rf__;\
    public: static const Reflect::IdType class_id = classid;
#define IMPLIMENT_REFLECT(class_name) \
    const Reflect class_name::__rf__(class_name::class_id, class_name::__rf_func__);