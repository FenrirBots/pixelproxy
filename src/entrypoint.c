#include <inc/http.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

/* The domain which we redirect to our proxy */
#define PIXEL_WORLDS_DOMAIN "prod.gamev90.portalworldsgame.com"

/* The ip and port used for logging into pixel worlds */
#define PIXEL_WORLDS_IP "44.194.163.69"
#define PIXEL_WORLDS_PORT 10001

void print_banner(
	)
{
	#define VERSION_MAJOR 1
	#define VERSION_MINOR 0
	#define VERSION_PATCH 0
	
	printf("Pixel Proxy v%i.%i.%i (tags/%s)\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, "beta");
  	printf("Type 'help', 'copyright', 'credits' or 'license' for more information\n");
}

int main(
	uint32_t argc,
	uint8_t *argv[])
{
	struct http_instance client_instance;
	struct http_instance server_instance;

	print_banner();
	http_startup();

	http_client_create(&client_instance);
	http_set_address(&client_instance, PIXEL_WORLDS_IP, PIXEL_WORLDS_PORT);

	http_server_create(&server_instance);
	http_set_address(&server_instance, "127.0.0.1", PIXEL_WORLDS_PORT);
	http_set_opt(&server_instance, HTTP_OPT_QUEUE, 1);
	http_server_listen(&server_instance);

	while (1)
	{
		if (http_client_connect(&client_instance))
		{
			printf("Failed to connect to the server\n");
			return 0;
		}
		http_set_opt(&client_instance, HTTP_OPT_NOBLOCK, 1);

		if (http_server_connect(&server_instance))
		{
			printf("Failed to connect to the server\n");
			return 0;
		}
		http_set_opt(&server_instance, HTTP_OPT_NOBLOCK, 1);

		while (1)
		{
		}

		http_disconnect(&client_instance);
		http_disconnect(&server_instance);

		printf("Disconnected, Attempting to reconnect in 5 seconds...");
		Sleep(5000);
	}

	http_cleanup();
}