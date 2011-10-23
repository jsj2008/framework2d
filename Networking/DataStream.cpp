#include "DataStream.h"
#include <Log/Log.h>
#include <cstring>
#include <sys/socket.h>

DataStream::DataStream(char* _data, int _contentLength, int _bufferLength)
{
	bufferStart = _data;
	bufferLength = _bufferLength;
	iter = 0;
	contentLength = _contentLength;
}


DataStream::~DataStream(void)
{
}

void DataStream::read(void* _dest, int _length)
{
	if (_length + iter > contentLength)
	{
        g_Log.error("End of DataStream, cannot read any more");
	}
	memcpy(_dest, bufferStart + iter, _length);
	iter += _length;
}
void DataStream::write(const void* _src, int _length)
{
	if (_length + contentLength > bufferLength)
	{
        g_Log.error("End of DataStream buffer, cannot write any more");
	}
	memcpy(bufferStart + contentLength, _src, _length);
	contentLength += _length;
}

void DataStream::append(DataStream* _source, int _startIter)
{
    const void* start = _source->bufferStart + _startIter;
    write(start, _source->iter - _startIter);
}
void DataStream::resetIter()
{
	iter = 0;
}

void DataStream::transmit(SOCKET _socket)
{
	int length = contentLength;
	send(_socket, bufferStart, length, 0);
}
