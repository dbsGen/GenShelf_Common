//
// Created by gen on 26/07/2017.
//

#include "ArtBasket.h"

using namespace nl;

RefArray ArtBasket::arts;

void ArtBasket::addBook(const Ref<Book> &book) {
    for (auto it = arts->begin(), _e = arts->end(); it != _e; ++it) {
        Ref<Art> art = *it;
        if (art->getType() == 1 && art->getUrl() == book->getUrl()) {
            return;
        }
    }
    Ref<Art> art = new Art;
    art->setUrl(book->getUrl());
    art->setName(book->getName());
    art->setShopId(book->getShopId());
    art->setThumb(book->getThumb());
    art->setType(1);
    arts->push_back(art);
}

void ArtBasket::addChapter(const Ref<Book> &book, const Ref<Chapter> &chapter) {
    for (auto it = arts->begin(), _e = arts->end(); it != _e; ++it) {
        Ref<Art> art = *it;
        if (art->getType() == 0 && art->getChapterUrl() == chapter->getUrl()) {
            return;
        }
    }
    Ref<Art> art = new Art;
    art->setName(book->getName());

    art->setUrl(book->getUrl());
    art->setChapterUrl(chapter->getUrl());
    art->setShopId(book->getShopId());
    art->setThumb(book->getThumb());
    art->setType(0);
    arts->push_back(art);
}