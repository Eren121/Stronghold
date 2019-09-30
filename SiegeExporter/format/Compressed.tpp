#include "Compressed.h"

template<typename T>
Compressed<T>::Compressed()
{
}

template<typename T>
Compressed<T>::~Compressed()
{
}

template<typename T>
void Compressed<T>::writeObject(QDataStream& stream)
{
    QByteArray bytes;
    QDataStream toCompress(&bytes, QIODevice::WriteOnly);
    QByteArray compressed = qCompress(bytes);

    stream.writeRawData(compressed, compressed.size());
}

template<typename T>
void Compressed<T>::readObject(QDataStream& stream)
{

}
