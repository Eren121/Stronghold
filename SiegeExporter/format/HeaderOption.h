#ifndef HEADEROPTION_H
#define HEADEROPTION_H

#include "Serializable.h"
#include "String.h"

template<typename T>
class HeaderOption
    : public Serializable
{
private:
    String key;
    T value;

public:

    inline void readObject(QDataStream &stream) override
    {
        key.readObject(stream);
        value.readObject(stream);
    }

    inline void writeObject(QDataStream &stream) override
    {
        key.writeObject(stream);
        value.writeObject(stream);
    }

    inline String& getKey() { return key; }
    inline T& getValue() { return value; }
    inline void setKey(const String& key) { this->key = key; }
    inline void setValue(const T& value) { this->value = value; }
};

#endif // HEADEROPTION_H
