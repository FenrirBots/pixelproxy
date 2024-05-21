#include <inc/http.h>

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

/*
	struct http_instance client_instance;
	struct http_instance server_instance;
	struct WSAData       wsadata;
	
	print_banner();
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	memset(&client_instance.connection_info, 0, sizeof(client_instance.connection_info));
	client_instance.connection_info.sin_addr.s_addr = inet_addr(PIXEL_WORLDS_IP);
	client_instance.connection_info.sin_port        = htons(PIXEL_WORLDS_PORT);
	client_instance.connection_info.sin_family      = AF_INET;

	if (client_instance.connection_info.sin_addr.s_addr == INADDR_NONE)
	{
		printf("Invalid address\n");
		exit(0);
	}

	client_instance.connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_instance.connection == INVALID_SOCKET)
	{
		printf("Invalid socket\n");
		exit(0);
	}

	if (connect(client_instance.connection, &client_instance.connection_info, sizeof(client_instance.connection_info)))
	{
		printf("Invalid connection\n");
		exit(0);
	}

	printf("Connected\n");
*/