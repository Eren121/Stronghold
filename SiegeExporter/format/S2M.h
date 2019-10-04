#ifndef S2M_H
#define S2M_H

#include "Compressed.h"
#include "Header.h"

class S2M
    : public Serializable
{
private:
    Header header;
    Compressed<Primitive<QByteArray>> data[3];

public:
    S2M();
    ~S2M() override;

    inline Header& getHeader() { return header; }

    inline Compressed<Primitive<QByteArray>>& getData(int i) { return data[i]; }

    inline void readObject(QDataStream &stream) override
    {
        header.readObject(stream);

        for(int i = 0; i < 3; i++)
            data[i].readObject(stream);
    }

    inline void writeObject(QDataStream &stream) override
    {
        header.writeObject(stream);

        for(int i = 0; i < 3; i++)
            data[i].writeObject(stream);
    }
};

#endif // S2M_H
