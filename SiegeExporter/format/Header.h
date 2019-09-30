#ifndef HEADER_H
#define HEADER_H

#include <QVector>
#include <QString>
#include <QTreeWidget>
#include "Serializable.h"
#include "HeaderOption.h"
#include "List.h"
#include "UnicodeString.h"

class Header
    : public Serializable
{
private:
    List<HeaderOption<UnicodeString>> stringOptions;
    List<HeaderOption<Primitive<qint32>>> intOptions;

public:

    inline decltype(stringOptions)& getStrings()
    {
        return stringOptions;
    }

    inline decltype(intOptions)& getInts()
    {
        return intOptions;
    }

    inline void readObject(QDataStream &stream) override
    {
        stringOptions.readObject(stream);
        intOptions.readObject(stream);
    }

    inline void writeObject(QDataStream &stream) override
    {
        stringOptions.writeObject(stream);
        intOptions.writeObject(stream);
    }

    void removeAuthor();
    bool set(const std::string& key, const std::string& value);
    void loadIntoView(QTreeWidget& widget);
};

#endif // HEADER_H
