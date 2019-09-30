#ifndef COMPRESSED_H
#define COMPRESSED_H

#include "Serializable.h"

template<typename T>
class Compressed
    : public Serializable,
      public T
{
public:
    Compressed();
    ~Compressed() override;

    void writeObject(QDataStream& stream) override;
    void readObject(QDataStream& stream) override;
};

#include "Compressed.tpp"

#endif // COMPRESSED_H
