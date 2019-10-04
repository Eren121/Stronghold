#include <QtTest/QTest>
#include "format/Compressed.h"

class TestCompressed
    : public QObject
{
    Q_OBJECT

private:
    static constexpr const unsigned char testRaw[]
        = { 0x78, 0x9c, 0xcb, 0x4d, 0x2d, 0x2e, 0x4e, 0x4c, 0x4f, 0x05, 0x00, 0x0b, 0xc1, 0x02, 0xe6 }; // "message"
    static constexpr const unsigned char testRawAndDummy[]
        = { 0x78, 0x9c, 0xcb, 0x4d, 0x2d, 0x2e, 0x4e, 0x4c, 0x4f, 0x05, 0x00, 0x0b, 0xc1, 0x02, 0xe6
           /* Dummy data */, 0x01, 0x02, 0x03 }; // "message" + dummy data

    static constexpr const char* const testMessage = "message";

private slots:
    void testFormatRawRead()
    {
        QByteArray message = testMessage;
        QDataStream input(message);
        Primitive<QByteArray> format;

        format.readObject(input);

        QVERIFY(format.get() == message);
    }

    void testFormatRawWrite()
    {
        QByteArray message = testMessage;
        QByteArray outputArray;
        QDataStream output(&outputArray, QIODevice::WriteOnly);
        Primitive<QByteArray> format;

        format.get() = message;
        format.writeObject(output);

        QVERIFY(outputArray == message);
    }

    void testCompressedWriteRead()
    {
        QByteArray outputArray;
        QDataStream output(&outputArray, QIODevice::WriteOnly);

        Compressed<Primitive<QByteArray>> format;

        format.get() = testMessage;
        format.writeObject(output);
        QDataStream input(outputArray);

        format.readObject(input);

        QVERIFY(format.get() == testMessage);
    }

    void testCompressedRead()
    {
        QByteArray raw = reinterpret_cast<const char*>(testRawAndDummy);
        QDataStream input(raw);
        Compressed<Primitive<QByteArray>> format;

        format.readObject(input);

        qDebug() << format.get();
        QVERIFY(format.get() == testMessage);
    }

    void testCompressedWrite()
    {
        QByteArray message = testMessage;
        QByteArray outputArray;
        QDataStream output(&outputArray, QIODevice::WriteOnly);
        Compressed<Primitive<QByteArray>> format;

        format.get() = message;
        format.writeObject(output);

        QVERIFY(outputArray == QByteArray(reinterpret_cast<const char*>(testRaw)));
    }
};

//QTEST_MAIN(TestCompressed)
