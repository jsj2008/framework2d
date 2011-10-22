#pragma once

#define DEFAULT_BUFFER_SIZE 256
typedef unsigned int SOCKET;

/// To use this class, allocate a buffer on the stack and pass it to this to handle as a stream
class DataStream
{
public:
	DataStream(char* _data, int _contentLength, int _bufferLength = DEFAULT_BUFFER_SIZE);
	~DataStream(void);

	template <typename T>
    void encode(const T& _data);
	template <typename Container, typename Datatype>
	void encodeString(const Container* _container)const; /// Max length 256 (size indicator is a single byte)
	template <typename T>
	T decode();
	template <typename Container, typename Datatype>
	void decodeString(Container* _container); /// Max length 256
	void resetIter();

	void transmit(SOCKET _socket);

	int getIter(){return iter;}
	void append(DataStream* _source, int _startIter);

	int getContentLength(){return contentLength;}
private:
	void read(void* _dest, int _length);
	void write(const void* _src, int _length);

	char* bufferStart;
	int bufferLength;

	int iter;
	int contentLength;
};


template <typename T>
void DataStream::encode(const T& _data)
{
	write(&_data, sizeof(T));
}
template <typename Container, typename Datatype>
void DataStream::encodeString(const Container* _container)const
{
	unsigned char length = _container->size();
	encode<unsigned char>(length);
	write(&(*_container)[0], sizeof(Datatype)*length);
}
template <typename Container, typename Datatype>
void DataStream::decodeString(Container* _container)
{
	unsigned char length = decode<unsigned char>();
	_container->resize(length);
	read(&(*_container)[0], sizeof(Datatype)*length);
}
template <typename T>
T DataStream::decode()
{
	T ret;
	read(&ret, sizeof(T));
	return ret;
}
