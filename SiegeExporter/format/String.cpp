#include "String.h"

String::String(const std::string& value)
    : value(value)
{
}

void String::readObject(QDataStream &stream)
{
    qint32 size;
    stream >> size;

    std::vector<char> buffer(static_cast<size_t>(size), 0);
    stream.readRawData(buffer.data(), buffer.size());

    value = {buffer.begin(), buffer.end()}; // Care: Vector is not null-terminated, cannot deduce size and send .data() directly

    log(QString("Read String: '%1'").arg(value.c_str()));
}

void String::writeObject(QDataStream &stream)
{
    qint32 size = static_cast<qint32>(value.size());
    stream << size;
    stream.writeRawData(value.c_str(), size);

    log(QString("Write String: '%1'").arg(value.c_str()));
}
