#include <inc/http.h>

uint32_t http_client_create(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	instance->listener = INVALID_SOCKET;
	instance->connection = socket(instance->family, instance->type, instance->protocol);

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
