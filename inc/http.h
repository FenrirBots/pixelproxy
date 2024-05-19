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
	HTTP_E_UNKNOWN_OPT = 1,
	HTTP_E_INVALID_SOCKET = 2,
	HTTP_E_INVALID_INSTANCE = 3,
	HTTP_E_INVALID_ADDRESS = 4,
	HTTP_E_CONNECTION_REFUSED = 5,
	HTTP_E_DISCONNECT_FAILED = 6
};

enum http_options
{
	HTTP_OPT_IPV4       = 1,
	HTTP_OPT_IPV6       = 2,
	HTTP_OPT_UDP		= 3,
	HTTP_OPT_TCP		= 4,
	HTTP_OPT_NOBLOCK	= 5,
	HTTP_OPT_QUEUE      = 6
};

struct http_instance
{
	uint32_t    family;
	uint32_t    type;
	uint32_t    protocol;
	uint32_t    queue;

	SOCKET      listener;
	SOCKET      connection;
	SOCKADDR_IN connection_info;
};

uint32_t http_startup();
uint32_t http_cleanup();

uint32_t http_instance_init(struct http_instance *instance);
uint32_t http_set_address(struct http_instance *instance, uint8_t *address, uint32_t port);
uint32_t http_set_option(struct http_instance *instance, enum http_options option, uint32_t value);
uint32_t http_disconnect(struct http_instance *instance);

uint32_t http_client_create(struct http_instance *instance);
uint32_t http_client_connect(struct http_instance *instance);

uint32_t http_server_create(struct http_instance *instance);
uint32_t http_server_listen(struct http_instance *instance);
uint32_t http_server_connect(struct http_instance *instance);
#endif