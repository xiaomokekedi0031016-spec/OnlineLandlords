#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "TcpServer.h"
#include "Log.h"
#include "MyTest.h"

//argc表示命令行参数的个数
//argv表示命令行参数的数组
int main(int argc, char* argv[])
{
	//8888 /home/wz/luffy
#if 0
	if (argc < 3) {
		printf("./a.out port path\n");
		return -1;
	}
	unsigned short port = atoi(argv[1]);
	//切换服务器的工作路径
	chdir(argv[2]);

#else
	unsigned short port = 8888;
	chdir("/home/wz/luffy");
#endif
	//启动服务器
	//Debug("main....");
	// MyTest t;
	// t.test();


	TcpServer* server = new TcpServer(port, 4);
	server->run();

	return 0;
}