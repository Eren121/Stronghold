#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QDataStream>
#include <iostream>
#include <QDebug>
#include <QString>

class Serializable
{
public:
    Serializable();
    virtual ~Serializable();

    virtual void writeObject(QDataStream& stream) = 0;
    virtual void readObject(QDataStream& stream) = 0;

    inline void log(const std::string& message) {
        log(QString(message.c_str()));
    }

    inline void log(const QString& message) {
        qDebug() << "Serializable: " << message;
    }
};

template<typename T>
class Primitive
    : public Serializable
{
private:
    T value;

public:
    Primitive()
    {
    }

    Primitive(T value)
        : value(value)
    {
    }

    void readObject(QDataStream &stream) override
    {
        stream >> value;
    }

    void writeObject(QDataStream &stream) override
    {
        stream << value;
    }

    inline T& get()
    {
        return value;
    }
};

template<>
class Primitive<QByteArray>
    : public Serializable
{
private:
    QByteArray value;

public:
    Primitive()
    {
    }

    Primitive(const QByteArray& value)
        : value(value)
    {
    }

    void readObject(QDataStream &stream) override
    {
        value = stream.device()->readAll();
    }

    void writeObject(QDataStream &stream) override
    {
        stream.writeRawData(value.data(), value.size());
    }

    inline QByteArray& get()
    {
        return value;
    }
};

#endif // SERIALIZABLE_H
