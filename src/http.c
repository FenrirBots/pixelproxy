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

uint32_t http_client_create(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	instance->listener   = INVALID_SOCKET;
	instance->connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (instance->connection == INVALID_SOCKET)
	{
		return HTTP_E_INVALID_SOCKET;
	}

	return HTTP_OK;
}

uint32_t http_client_connect(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}
 
	if (connect(instance->connection, &instance->connection_info, sizeof(instance->connection_info)))
	{
		return HTTP_E_CONNECTION_REFUSED;
	}

	return HTTP_OK;
}

uint32_t http_server_create(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	instance->listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	instance->connection   = INVALID_SOCKET;

	if (instance->listener == INVALID_SOCKET)
	{
		return HTTP_E_INVALID_SOCKET;
	}

	return HTTP_OK;
}

uint32_t http_server_listen(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	if (bind(instance->listener, &instance->connection_info, sizeof(instance->connection_info)))
	{
		return 1; // Add an error
	}
	
	if (listen(instance->listener, instance->queue))
	{
		return 1; // Add an error
	}

	return HTTP_OK;
}

uint32_t http_server_connect(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	instance->connection = accept(instance->listener, NULL, NULL);
	
	if (instance->connection == INVALID_SOCKET)
	{
		return HTTP_E_CONNECTION_REFUSED;
	}

	return HTTP_OK;
}