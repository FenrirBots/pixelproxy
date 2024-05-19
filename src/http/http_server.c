#include <inc/http.h>

uint32_t http_server_create(
	struct http_instance *instance)
{
	if (instance == NULL)
	{
		return HTTP_E_INVALID_INSTANCE;
	}

	instance->listener = socket(instance->family, instance->type, instance->protocol);
	instance->connection = INVALID_SOCKET;

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