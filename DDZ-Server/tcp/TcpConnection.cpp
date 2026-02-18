#include "TcpConnection.h"
#include "HttpRequest.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

#include "Codec.h"
#include "RsaCrypto.h"
#include "Log.h"

int TcpConnection::processRead(void* arg) {
	TcpConnection* conn = static_cast<TcpConnection*>(arg);
	// 接收数据
	int socket = conn->m_channel->getSocket();
	int count = conn->m_readBuf->socketRead(socket);

	Debug("接收到的请求数据: %s", conn->m_readBuf->data());
	if (count > 0)
	{
		// 解析斗地主数据
	}
	else if(count <= 0)
	{
		// 断开和客户端的连接诶
		Debug("和客户端的连接已经断开了....");
	}
	return 0;
}

int TcpConnection::processWrite(void* arg) {
	//Debug("开始发送数据了(基于写事件发送)....");
	TcpConnection* conn = static_cast<TcpConnection*>(arg);
	// 发送数据
	int count = conn->m_writeBuf->sendData(conn->m_channel->getSocket());
	 // cout<<"1111111111";
	if (count > 0) {
		if (conn->m_writeBuf->readableSize() == 0)//数据全部发送出去了
		{
			// 1. 不再检测写事件 -- 修改channel中保存的事件
			conn->m_channel->setCurrentEvent(FDEvent::ReadEvent);
			// 2. 修改dispatcher检测的集合 -- 添加任务节点
			conn->m_evLoop->addTask(conn->m_channel, ElemType::MODIFY);
			Debug("数据发送完毕...................");
		}
	}
	return 0;
}

int TcpConnection::destroy(void* arg){
	TcpConnection* conn = static_cast<TcpConnection*>(arg);
	if (conn != nullptr){
		delete conn;
	}
	return 0;
}

TcpConnection::TcpConnection(int fd, EventLoop* evloop) {
	// cout<<"22222222";
	m_evLoop = evloop;
	m_readBuf = new Buffer(10240);
	m_writeBuf = new Buffer(10240);
	m_name = "Connection-" + std::to_string(fd);
    prepareSecretKey();
	// m_request = new HttpRequest;
	// m_response = new HttpResponse;
	//主线程调用子线程对象的函数，代码依然在主线程执行，只是操作了子线程的数据。正因为这是“跨线程操作数据”，所以才需要锁和唤醒机制。
    //主线程调用的，但是用的是子线程的反应堆
	//m_channel = new Channel(fd, FDEvent::ReadEvent, processRead,
							  //processWrite, destroy, this);
	m_channel = new Channel(fd, FDEvent::WriteEvent, processRead,
							processWrite, destroy, this);
	evloop->addTask(m_channel, ElemType::ADD);
}

void TcpConnection::prepareSecretKey() {
	ifstream ifs("public.pem");//打开文件
	stringstream sstr;
	sstr << ifs.rdbuf();
	string data = sstr.str();
	//发送数据
	Message msg;
	msg.rescode = RespondCode::RsaFenFa;
	msg.data1 = data;
	RsaCrypto rsa("private.pem", RsaCrypto::PrivateKey);
	data = rsa.sign(data);
	msg.data2 = data;
	Codec codec(&msg);
	data = codec.encodeMsg();
	// 写数据
	m_writeBuf->appendPackage(data);
}

TcpConnection::~TcpConnection() {
	if (m_readBuf && m_readBuf->readableSize() == 0 &&
		m_writeBuf && m_writeBuf->readableSize() == 0)
	{
		delete m_readBuf;
		delete m_writeBuf;
		// delete m_request;
		// delete m_response;
		m_evLoop->freeChannel(m_channel);
	}
	Debug("连接断开, 释放资源, gameover, connName: %s", m_name.data());
}



