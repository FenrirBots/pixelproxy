#include <inc/http.h>
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
	int argc,
	char** argv)
{
	struct http_instance client_instance;
	struct http_instance server_instance;

	print_banner();
	http_startup();

	memset(&client_instance, 0, sizeof(client_instance));
	http_instance_init(&client_instance);
	memset(&server_instance, 0, sizeof(server_instance));
	http_instance_init(&server_instance);
	
	http_set_option(&client_instance, HTTP_OPT_TCP, 0);
	http_set_option(&client_instance, HTTP_OPT_IPV4, 0);
	http_client_create(&client_instance);
	http_set_address(&client_instance, PIXEL_WORLDS_IP, PIXEL_WORLDS_PORT);
	
	http_set_option(&server_instance, HTTP_OPT_TCP, 0);
	http_set_option(&server_instance, HTTP_OPT_IPV4, 0);
	http_server_create(&server_instance);
	http_set_option(&server_instance, HTTP_OPT_QUEUE, 1);
	http_set_address(&server_instance, "127.0.0.1", PIXEL_WORLDS_PORT);
	http_server_listen(&server_instance);

	while (1)
	{
		http_client_connect(&client_instance);
		http_set_option(&client_instance, HTTP_OPT_NOBLOCK, 1);
		http_server_connect(&server_instance);
		http_set_option(&server_instance, HTTP_OPT_NOBLOCK, 1);

		while (1)
		{
		}

		http_disconnect(&client_instance);
		http_disconnect(&server_instance);
	}

	http_instance_cleanup(&client_instance);
	http_instance_cleanup(&server_instance);
	http_cleanup();
}