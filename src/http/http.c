#include <inc/http.h>

uint32_t http_startup(
	)
{
	struct WSAData wsadata;
	return WSAStartup(MAKEWORD(2, 2), &wsadata);
}


uint32_t http_cleanup(
	)
{
	return WSACleanup();
}

uint32_t http_set_address(
	struct http_instance *instance,
	uint8_t *address,
	uint32_t port)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	memset(&instance->connection_info, 0, sizeof(instance->connection_info));
	instance->connection_info.sin_addr.s_addr = inet_addr(address);
	instance->connection_info.sin_port        = htons(port);
	instance->connection_info.sin_family      = AF_INET;

	if (instance->connection_info.sin_addr.s_addr == INADDR_NONE)
	{
		return HTTP_E_INVALID_ADDRESS;
	}

	return HTTP_OK;
}

uint32_t http_set_opt(
	struct http_instance *instance,
	uint32_t opt,
	uint32_t value)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	switch (opt)
	{
		case HTTP_OPT_NOBLOCK:
			ioctlsocket(instance->connection, FIONBIO, &(u_long)value);
			break;
		case HTTP_OPT_QUEUE:
			instance->queue = value;
		
		default:
			return HTTP_E_UNKNOWN_OPT;
	}

	return HTTP_OK;
}

uint32_t http_disconnect(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}
	
	if (shutdown(instance->connection, SD_BOTH) == SOCKET_ERROR)
	{
		return HTTP_E_DISCONNECT_FAILED;
	}

	if (closesocket(instance->connection) == SOCKET_ERROR)
	{
		return HTTP_E_DISCONNECT_FAILED;
	}

	return HTTP_OK;
}