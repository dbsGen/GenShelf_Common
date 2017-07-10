//
// Created by mac on 2017/7/10.
//

#include "KeyValue.h"

using namespace nl;

map<string, Ref<KeyValue> > KeyValue::caches;

string KeyValue::get(const string &key) {
    auto it = caches.find(key);
    if (it != caches.end()) {
        return it->second->getValue();
    }
    RefArray arr = query()->equal("key", key)->results();
    Ref<KeyValue> kv;
    if (arr.size() > 0) {
        kv = arr.at(0).ref();
        pushCache(key, kv);
    }
    if (kv) {
        return kv->getValue();
    }
    return string();
}

void KeyValue::set(const string &key, const string &value) {
    auto it = caches.find(key);
    if (it != caches.end()) {
        const Ref<KeyValue> &kv = it->second;
        kv->setValue(value);
        kv->save();
        return;
    }
    RefArray arr = query()->equal("key", key)->results();
    Ref<KeyValue> kv;
    if (arr.size() > 0) {
        kv = arr.at(0).ref();
        pushCache(key, kv);
    }else {
        kv = new KeyValue;
        kv->setKey(key);
        pushCache(key, kv);
    }
    kv->setValue(value);
    kv->save();
}

void KeyValue::pushCache(const string &key, const Ref<KeyValue> &kv) {
    while (caches.size() > 100) {
        caches.erase(caches.begin());
    }
    caches[key] = kv;
}