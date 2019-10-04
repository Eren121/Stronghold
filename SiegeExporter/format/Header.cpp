#include "Header.h"

void Header::removeAuthor()
{
    auto& vec = stringOptions.get();

    for(int i = 0; i < vec.size(); i++) {

        if(vec[i].getKey().get() == std::string("author")) {

            vec.remove(i);
        }
    }
}

bool Header::set(const std::string &key, const std::string &value)
{
    auto& vec = stringOptions.get();

    for(int i = 0; i < vec.size(); i++) {

        if(vec[i].getKey().get() == key) {

            vec[i].setValue(UnicodeString(value));
            return true;
        }
    }

    return false;
}

template<typename T>
static void loadVectorIntoView(QTreeWidgetItem *widget, T& vec)
{
    for(int i = 0; i < vec.size(); i++) {

        QTreeWidgetItem* subItem = new QTreeWidgetItem;
        widget->addChild(subItem);

        subItem->setText(0, QString::fromStdString(vec[i].getKey().get()));
        subItem->setText(1, QVariant(vec[i].getValue().get()).toString());
    }
}

void Header::loadIntoView(QTreeWidget &widget)
{
    widget.clear();

    QTreeWidgetItem* item = new QTreeWidgetItem(&widget);
    item->setText(0, "Header");
    loadVectorIntoView(item, intOptions.get());
    loadVectorIntoView(item, stringOptions.get());

}
