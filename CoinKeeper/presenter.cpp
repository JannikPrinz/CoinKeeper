#include "presenter.hpp"

Presenter::Presenter(Database* base, QObject * parent) : QObject(parent) {
    database = base;
}

Presenter::~Presenter() {
    
}
