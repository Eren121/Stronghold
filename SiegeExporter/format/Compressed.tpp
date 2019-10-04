#include "Compressed.h"
#include <QtZlib/zlib.h>

template<typename T>
Compressed<T>::Compressed()
    : compressed(true)
{
}

template<typename T>
Compressed<T>::~Compressed()
{
}

template<typename T>
void Compressed<T>::writeObject(QDataStream& stream)
{
    if(compressed) {

        QByteArray bytes;
        QDataStream toCompress(&bytes, QIODevice::WriteOnly);
        toCompress.setByteOrder(QDataStream::LittleEndian);

        T::writeObject(toCompress);

        QDataStream input(bytes);
        input.setByteOrder(QDataStream::LittleEndian);

        int status;
        if((status = compressKeepStreamClean(input, stream)) != Z_OK) {

            qDebug() << __FUNCSIG__ << " zlib not returning Z_OK: " << status;
        }
    }
    else {

        T::writeObject(stream);
    }
}

template<typename T>
void Compressed<T>::readObject(QDataStream& stream)
{
    if(compressed) {

        QByteArray bytes;
        QDataStream uncompressed(&bytes, QIODevice::WriteOnly);
        uncompressed.setByteOrder(QDataStream::LittleEndian);

        int status;
        if((status = uncompressKeepStreamClean(stream, uncompressed)) != Z_OK) {

            qDebug() << __FUNCSIG__ << " zlib not returning Z_OK: "
                     << status
                     << " "
                     << stream.device()->errorString();
        }

        QDataStream input(&bytes, QIODevice::ReadOnly);
        input.setByteOrder(QDataStream::LittleEndian);
        T::readObject(input);
    }
    else {

        T::readObject(stream);
    }
}

template<typename T>
int Compressed<T>::compressKeepStreamClean(QDataStream &input, QDataStream& output)
{
    constexpr int CHUNK = 1024;
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[1];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK)
        return ret;

    /* compress until end of file */
    do {
        strm.avail_in = input.readRawData((char*)in, sizeof(in));

        if(strm.avail_in != 0 && input.status() == QDataStream::ReadCorruptData) {
            deflateEnd(&strm);
            return Z_ERRNO;
        }

        flush = input.status() == QDataStream::ReadPastEnd ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = sizeof(out);
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = sizeof(out) - strm.avail_out;

            if(output.writeRawData((char*)out, have) != have || output.status() == QDataStream::WriteFailed) {
                deflateEnd(&strm);
                return Z_ERRNO;
            }

        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);

    return Z_OK;
}

template<typename T>
int Compressed<T>::uncompressKeepStreamClean(QDataStream &input, QDataStream& output)
{
    constexpr int CHUNK = 1024;
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[1];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {

        strm.avail_in = input.readRawData((char*)in, sizeof(in));

        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = sizeof(out);
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                return ret;
            }
            have = sizeof(out) - strm.avail_out;

            if(output.writeRawData((char*)&out, have) != have) {
                inflateEnd(&strm);
                return Z_ERRNO;
            }

        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);

    return Z_OK;
}
