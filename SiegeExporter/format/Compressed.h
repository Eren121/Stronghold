#ifndef COMPRESSED_H
#define COMPRESSED_H

#include "Serializable.h"

template<typename T>
class Compressed
    : public T
{
private:
    bool compressed;

public:
    Compressed();
    ~Compressed() override;

    void writeObject(QDataStream& stream) override;
    void readObject(QDataStream& stream) override;

    // Deflate but not read bytes after the compressed data in the stream
    int compressKeepStreamClean(QDataStream& input, QDataStream& output);
    int uncompressKeepStreamClean(QDataStream& input, QDataStream& output);

    inline bool getWriteCompressed() const { return compressed; }
    inline void setCompressed(bool writeCompressed) { this->compressed = writeCompressed; }
};

#include "Compressed.tpp"

#endif // COMPRESSED_H
