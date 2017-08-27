//
// Created by gen on 26/07/2017.
//

#include "ArtBasket.h"
#include <utils/xml/XMLNode.h>
#include <utils/xml/XMLDocument.h>

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
    art->setChapterName(chapter->getName());
    art->setUrl(book->getUrl());
    art->setChapterUrl(chapter->getUrl());
    art->setShopId(book->getShopId());
    art->setThumb(book->getThumb());
    art->setType(0);
    arts->push_back(art);
}

string replace_all_distinct(string str, const string& old_value, const string& new_value)
{
    for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length())   {
        if((pos=str.find(old_value,pos))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else break;
    }
    return str;
}

string Art::html() {
    stringstream ss;
    ss << "<art type='";
    ss << type;
    ss << "' shop='";
    ss << shop_id.str();
    ss << "' thumb='";
    ss << replace_all_distinct(thumb, "\'", "\\\'");
    ss << "' url='";
    ss << replace_all_distinct(url, "\'", "\\\'");
    ss << "' name='";
    ss << replace_all_distinct(name, "\'", "\\\'");
    ss << "'";
    if (type == 0) {
        ss << " c_name='";
        ss << replace_all_distinct(chapter_name, "\'", "\\\'");
        ss << "' c_url='";
        ss << replace_all_distinct(chapter_url, "\'", "\\\'");
        ss << "'";
    }
    ss << " />";
    return ss.str();
}

RefArray Art::parse(const string &content) {
    XMLDocument doc;
    doc.initialize(Data::fromString("<content>"+content+"</content>"), XMLDocument::HTML);
    if (!doc.getRoot()) return RefArray();
    RefArray bodys = doc.xpath("//content");
    if (bodys.size() == 0) return RefArray();
    const RefArray &cs = bodys.at(0).get<XMLNode>()->getChildren();
    RefArray rets;
    for (auto it = cs->begin(), _e = cs->end(); it != _e; ++it) {
        const Ref<XMLNode> &node = *it;
        switch (node->getType()) {
            case 3:
                rets->push_back(node->getContent());
                break;
            case 1: {
                Ref<Art> art(new Art);
                art->setType(atoi(node->getAttribute("type").c_str()));
                art->setShopId(node->getAttribute("shop").c_str());
                art->setThumb(node->getAttribute("thumb"));
                art->setUrl(node->getAttribute("url"));
                art->setName(node->getAttribute("name"));
                if (node->hasAttribute("c_name"))
                    art->setChapterName(node->getAttribute("c_name"));
                if (node->hasAttribute("c_url"))
                    art->setChapterUrl(node->getAttribute("c_url"));
                rets->push_back(art);
                break;
            }
        }
    }
    return rets;
}
