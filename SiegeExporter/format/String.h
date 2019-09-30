#ifndef STRING_H
#define STRING_H

#include <string>
#include "Serializable.h"

class String
    : public Serializable
{
private:
    std::string value;

public:
    String(const std::string& value = {});

    void readObject(QDataStream &stream) override;
    void writeObject(QDataStream &stream) override;

    inline const char* get() { return value.c_str(); }
    inline void set(const std::string& value) { this->value = value; }
};

#endif // STRING_H
