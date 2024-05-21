#ifndef PROXY_HTTP_H
#define PROXY_HTTP_H
#include <stdint.h>

/* Winsock */
#include <winsock2.h>
#include <ws2tcpip.h>

/* Secure Socket Protocol Interface */
#define SECURITY_WIN32
#include <sspi.h>
#include <schannel.h>

enum http_result
{
	HTTP_OK = 0,
	HTTP_E_INVALID_INSTANCE = 1,
	HTTP_E_INVALID_SOCKET = 2,
	HTTP_E_INVALID_ADDRESS = 3,
	HTTP_E_CONNECTION_REFUSED = 4,
	HTTP_E_DISCONNECT_FAILED = 5,
	HTTP_E_UNKNOWN_OPT = 6
};

enum http_options
{
	HTTP_OPT_NOBLOCK = 1,
	HTTP_OPT_QUEUE = 2
};

struct http_instance
{
	uint32_t    queue;
	SOCKET      listener;
	SOCKET      connection;
	SOCKADDR_IN connection_info;
};


uint32_t http_startup();
uint32_t http_cleanup();

uint32_t http_set_address(struct http_instance *instance, uint8_t *address, uint32_t port);
uint32_t http_set_opt(struct http_instance *instance, uint32_t opt, uint32_t value);	
uint32_t http_disconnect(struct http_instance *instance);


uint32_t http_client_create(struct http_instance *instance);
uint32_t http_client_connect(struct http_instance *instance);

uint32_t http_server_create(struct http_instance *instance);
uint32_t http_server_listen(struct http_instance *instance);
uint32_t http_server_connect(struct http_instance *instance);
#endif