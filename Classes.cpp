//
// Created by gen on 09/08/2017.
//


#include "controllers/Controller.h"
#include <utils/xml/XMLDocument.h>
#include <utils/network/HTTPClient.h>
#include <core/Data.h>
#include <core/Callback.h>
#include <core/Map.h>
#include <core/Array.h>
#include <utils/NotificationCenter.h>
#include <script/java/JScript.h>
#include <script/java/JClass.h>
#include <script/java/JInstance.h>

using namespace hicore;

void ClassDB::loadClasses() {
#ifdef USING_SCRIPT
    class_loaders[h("hirender::HTTPClient")] = (void*)&hirender::HTTPClient::getClass;
    class_loaders[h("hicore::Callback")] = (void*)&hicore::Callback::getClass;
    class_loaders[h("hirender::XMLDocument")] = (void*)&hirender::XMLDocument::getClass;
    class_loaders[h("hirender::XMLNode")] = (void*)&hirender::XMLNode::getClass;
    class_loaders[h("hicore::FileData")] = (void*)&hicore::FileData::getClass;
    class_loaders[h("hirender::NotificationCenter")] = (void*)&hirender::NotificationCenter::getClass;
    class_loaders[h("hicore::Map")] = (void*)&hicore::Map::getClass;
    class_loaders[h("hicore::Array")] = (void*)&hicore::Array::getClass;

//    class_loaders[h("hirender::Animator")] = (void*)&hirender::Animator::getClass;
//    class_loaders[h("hirender::AnimatorMethod")] = (void*)&hirender::AnimatorMethod::getClass;
//    class_loaders[h("hirender::AnimatorAction")] = (void*)&hirender::AnimatorAction::getClass;
//    class_loaders[h("hirender::Ease")] = (void*)&hirender::Ease::getClass;
#ifdef __ANDROID__
    void *load_jscript = (void*)&hiscript::JScript::instance;
    class_loaders[h("hiscript::JClass")] = (void*)&hiscript::JClass::getClass;
    class_loaders[h("hiscript::JInstance")] = (void*)&hiscript::JInstance::getClass;
#endif

#endif
}
