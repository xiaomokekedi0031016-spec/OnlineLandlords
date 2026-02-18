#include "Buffer.h"
#include <string.h>
#include <strings.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Log.h"
#include <arpa/inet.h>


Buffer::Buffer(int size)
	:m_capacity(size)
{
	m_data = (char*)malloc(size);
	bzero(m_data, size);
}

Buffer::~Buffer() {
	if (m_data != nullptr){
		free(m_data);
	}
}

void Buffer::extendRoom(int size) {
	//内存够用-不需要扩容
	if(writeableSize() >= size) {
		return;
	}
	else if (m_readPos + writeableSize() >= size) {
		int readable = readableSize();
		memcpy(m_data, m_data + m_readPos, readable);
		m_readPos = 0;
		m_writePos = readable;
	}
	else {
		void* temp = realloc(m_data, m_capacity + size);
		if (temp == NULL) {
			return;//失败了
		}
		memset((char*)temp + m_capacity, 0, size);
		//更新数据
		m_data = static_cast<char*>(temp);
		m_capacity += size;
	}
}

int Buffer::appendString(const char* data, int size) {
	if(data == nullptr || size <= 0) {
		return -1;
	}
	//扩容
	extendRoom(size);
	memcpy(m_data + m_writePos, data, size);
	m_writePos += size;
	return 0;
}

int Buffer::appendString(const char* data) {
	int size = strlen(data);
	int ret = appendString(data, size);
	return ret;
}

int Buffer::appendString(const std::string data)
{
	int ret = appendString(data.c_str(), data.size());
	return ret;
}

int Buffer::appendHead(const int length) {
	// 转换为大端字节序
	Debug("小端的数据头长度: %d", length);
	int len = htonl(length);
	Debug("大端的数据头长度: %d", len);
	// 类型转换 int -> string
	std::string head(reinterpret_cast<char*>(&len), sizeof(int));
	appendString(head);
	return 0;
}

int Buffer::appendPackage(const std::string data)
{
	appendHead(data.size());
	appendString(data);
	return 0;
}

int Buffer::socketRead(int fd) {
	//readv
	struct iovec vec[2];
	int writeable = writeableSize();//剩余可写的缓冲区大小
	vec[0].iov_base = m_data + m_writePos;//缓冲区可写位置
	vec[0].iov_len = writeable;
	char* tmpbuf = (char*)malloc(65536);//临时缓冲区放的是读到的数据
	vec[1].iov_base = tmpbuf;
	vec[1].iov_len = 40960;
	//readv返回的实际读到的字节数
	int result = readv(fd, vec, 2);
	if (result == -1) {
		return -1;
	}
	else if (result <= writeable) {
		m_writePos += result;
	}
	else {
		m_writePos = m_capacity;
		appendString(tmpbuf, result - writeable);
	}
	free(tmpbuf);
	return result;
}

int Buffer::sendData(int socket){
	int readable = readableSize();
	if (readable > 0) {
		//发送可读的数据
		int count = send(socket, m_data + m_readPos, readable, MSG_NOSIGNAL);
		if (count > 0)
		{
			m_readPos += count;
			usleep(1);//？？？
		}
		return count;
	}
	return 0;
}

char* Buffer::findCRLF() {
	//memmem从大块内存中查找小块内存
	char* ptr = (char*)memmem(m_data + m_readPos, readableSize(), "\r\n", 2);
	return ptr;
}





