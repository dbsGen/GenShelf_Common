//
// Created by mac on 2017/8/27.
//

#include "History.h"
#include <Renderer.h>

using namespace nl;

const int History_count_per_page = 20;

History::History() {

}

void History::visit(const Ref<Book> &book) {
    if (book && !book->getUrl().empty()) {
        const string &url = book->getUrl();

        RefArray arr = query()->equal("url", url)->results();
        Ref<History> his;
        if (arr.size() > 0) {
            his = arr.at(0).ref();
        }else {
            his = new History;
            JSONNODE *node = book->unparse();
            char *str = json_write(node);
            his->setContent(str);
            his->setUrl(url);
            json_free(str);
            json_delete(node);
        }
        long long time = (long long)(Renderer::time() * 1000);
        his->setDate(time);
        his->save();
    }
}

RefArray History::histories(long long from) {
    Ref<Query> q = query()->less("date", from)->sortBy("date")->limit(History_count_per_page);
    q->setSortAsc(false);
    return q->results();
}

Ref<Book> History::getBook() const {
    JSONNODE *node = json_parse(getContent().c_str());
    Book *book = Book::parse(node);
    json_delete(node);
    return book;
}

void History::clear() {
    query()->remove();
}