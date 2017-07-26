//
// Created by gen on 26/07/2017.
//

#ifndef GSAV2_0_ARTBASKET_H
#define GSAV2_0_ARTBASKET_H

#include <core/Ref.h>
#include <core/Array.h>
#include <vector>
#include "Book.h"
#include "Chapter.h"
#include "../nl_define.h"

using namespace hicore;
using namespace std;

namespace nl {
    CLASS_BEGIN_N(Art, RefObject)
        int type;
        StringName shop_id;
        string url;
        string chapter_url;
        string name;
        string chapter_name;
        string thumb;

    public:
        METHOD _FORCE_INLINE_ void setType(int type) {
            this->type = type;
        }
        METHOD _FORCE_INLINE_ int getType() const {
            return type;
        }
        PROPERTY(type, getType, setType)

        METHOD _FORCE_INLINE_ void setShopId(const StringName &shop_id) {
            this->shop_id = shop_id;
        }
        METHOD _FORCE_INLINE_ const StringName &getShopId() const {
            return shop_id;
        }
        PROPERTY(shop_id, getShopId, setShopId)

        METHOD _FORCE_INLINE_ void setUrl(const string &url) {
            this->url = url;
        }
        METHOD _FORCE_INLINE_ const string &getUrl() const {
            return url;
        }
        PROPERTY(url, getUrl, setUrl)

        METHOD _FORCE_INLINE_ void setName(const string &name) {
            this->name = name;
        }
        METHOD _FORCE_INLINE_ const string &getName() const {
            return name;
        }
        PROPERTY(name, getName, setName)

        METHOD _FORCE_INLINE_ void setThumb(const string &thumb) {
            this->thumb = thumb;
        }
        METHOD _FORCE_INLINE_ const string &getThumb() const {
            return thumb;
        }
        PROPERTY(thumb, getThumb, setThumb)

        METHOD _FORCE_INLINE_ void setChapterUrl(const string &chapter_url) {
            this->chapter_url = chapter_url;
        }
        METHOD _FORCE_INLINE_ const string &getChapterUrl() {
            return chapter_url;
        }
        PROPERTY(chapter_url, getChapterUrl, setChapterUrl);

        METHOD _FORCE_INLINE_ void setChapterName(const string &chapter_name) {
            this->chapter_name = chapter_name;
        }
        METHOD _FORCE_INLINE_ const string &getChapterName() const {
            return chapter_name;
        }
        PROPERTY(chapter_name, getChapterName, setChapterName)

    CLASS_END

    CLASS_BEGIN_N(ArtBasket, RefObject)

        static RefArray arts;

    public:

        METHOD static void addBook(const Ref<Book> &book);
        METHOD static void addChapter(const Ref<Book> &book, const Ref<Chapter> &chapter);

        METHOD _FORCE_INLINE_ static const RefArray &getArts() {
            return arts;
        }

    CLASS_END
}


#endif //GSAV2_0_ARTBASKET_H
