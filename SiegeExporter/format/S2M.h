#ifndef S2M_H
#define S2M_H

#include "Serializable.h"
#include "Header.h"

class S2M
    : public Serializable
{
private:
    Header header;

public:
    S2M();
    ~S2M() override;

    inline Header& getHeader() { return header; }
};

#endif // S2M_H
