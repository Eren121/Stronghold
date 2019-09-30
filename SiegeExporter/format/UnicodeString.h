#ifndef UNICODESTRING_H
#define UNICODESTRING_H

#include <string>
#include "Serializable.h"

class UnicodeString
    : public Serializable
{
private:
    std::string value;

public:
    UnicodeString(const std::string& value = {});

    inline const char* get() { return value.c_str(); }

    void readObject(QDataStream &stream) override;
    void writeObject(QDataStream &stream) override;
};

#endif // UNICODESTRING_H
