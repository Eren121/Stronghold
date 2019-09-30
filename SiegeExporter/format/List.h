#ifndef LIST_H
#define LIST_H

#include <QVector>
#include <QString>
#include "Serializable.h"

template<typename T>
class List
    : public Serializable
{
private:
    QVector<T> list;

public:
    void readObject(QDataStream &stream) override;
    void writeObject(QDataStream &stream) override;

    inline QVector<T>& get() { return list; }
    inline QVector<T>* operator->() { return &list; }
};

#include "List.tpp"

#endif // LIST_H
