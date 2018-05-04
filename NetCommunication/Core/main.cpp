 #include <stdio.h>
 //#include "ParseDictImp.h"
//int main()
//{
//	printf("¿ª·¢ÖÐ¡£¡£¡£\n");
//	//ParseDictImp parse;
//	//parse.ParseFile("./Dict.xml");
//	return 0;
//}

//#include "Poco/Net/SocketAddress.h"
//#include "Poco/Net/StreamSocket.h"
//#include "Poco/Net/SocketStream.h"
//#include "Poco/StreamCopier.h"
//#include <iostream>
//#include <Windows.h>
//int main(int argc, char** argv)
//{
//	Poco::Net::SocketAddress sa("www.baidu.com", 80);
//	Poco::Net::StreamSocket socket(sa);
//		Poco::Net::SocketStream str(socket);
//	str << "GET / HTTP/1.1\r\n"
//		"Host: www.baidu.com\r\n"
//		"\r\n";
//	str.flush();
//	Poco::StreamCopier::copyStream(str, std::cout);
//	return 0;
//}


// #include "Poco/Net/ServerSocket.h"
// #include "Poco/Net/StreamSocket.h"
// #include "Poco/Net/SocketStream.h"
// #include "Poco/Net/SocketAddress.h"
int main(int argc, char** argv)
{
// 	Poco::Net::SocketAddress sa("localhost", 8080);
// 	Poco::Net::ServerSocket srv(sa);// does bind + listen
// 	for (;;)
// 	{
// 		Poco::Net::StreamSocket ss = srv.acceptConnection();
// 		Poco::Net::SocketStream str(ss);
// 		str << "HTTP/1.0 200 OK\r\n"
// 			"Content-Type: text/html\r\n"
// 			"\r\n"
// 			"<html><head><title>My 1st Web Server</title></head>"
// 			"<body><h1>Hello, world!</h1></body></html>"
// 			<< std::flush;
// 	}
	return 0;
}