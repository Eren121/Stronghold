#include "List.h"

template<typename T>
void List<T>::readObject(QDataStream &stream)
{
    T item;
    qint32 size;
    stream >> size;

    for(int i = 0; i < size; i++) {

        item.readObject(stream);
        list.push_back(item);
    }
}

template<typename T>
void List<T>::writeObject(QDataStream &stream)
{
    const qint32 size(list.size());
    stream << size;

    for(int i = 0; i < size; i++) {

        list[i].writeObject(stream);
    }
}
