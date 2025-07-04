
#pragma once 

#include "HTTPRequest.hpp"
#include "HTTPAction.hpp"
#include "Cgi.hpp"

#include <string>

class	ConnectionHandler 
{
	private:
		HTTPRequest _request; //nog handlen: onvolledige requests binnenkrijgen, check wat recv doet exact
		Cgi *_cgi;
		const ServerConfig *_serverConfig;

		bool _shouldClose;
		std::string _serverKey;
		int _connectionSocketFD;

		ConnectionHandler(const ConnectionHandler &other);
		ConnectionHandler &operator=(const ConnectionHandler &other);

		int _getConnectionSocketFD();

		void _createRequest();
		void _sendResponse(const std::string &responseString);
		void _setServerConfig();

		void _handleErrorRecv(int bytesRead);
		bool _delegateToHTTPAction(HTTPAction &Action);

	public:
		ConnectionHandler(std::string &serverKey, int fd);
		~ConnectionHandler();

		bool epolloutShouldOpen;
		bool epolloutShouldClose;

		void handleHTTP();
		void sendCgiResponse();
		bool shouldClose();

		bool isCgiRunning() { return (this->_cgi != NULL); }
		Cgi *getCgi() { return (this->_cgi); }
		void killCgi();
};
