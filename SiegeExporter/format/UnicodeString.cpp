#include "UnicodeString.h"

UnicodeString::UnicodeString(const std::string& value)
    : value(value)
{
}

void UnicodeString::readObject(QDataStream &stream)
{
    qint32 size;
    stream >> size;

    std::vector<char> unicodeBuffer(size * 2, 0);
    stream.readRawData(unicodeBuffer.data(), unicodeBuffer.size());

    std::vector<char> buffer(size, 0);
    for(int i = 0; i < buffer.size(); i++) {
        buffer[i] = unicodeBuffer[i * 2];
    }

    value = {buffer.begin(), buffer.end()}; // Care: Vector is not null-terminated, cannot deduce size and send .data() directly
}

void UnicodeString::writeObject(QDataStream &stream)
{
    char raw[2] = {0};
    qint32 size = static_cast<qint32>(value.size());
    stream << size;

    for(size_t i = 0; i < value.size(); i++) {

        raw[0] = value[i];
        stream.writeRawData(raw, sizeof(raw));
    }
}
