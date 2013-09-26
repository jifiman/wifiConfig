#include <stdio.h>
#include <string.h>
#include "mongoose.h"
static void GetEssids(char *cAessid, int iLength)
{

	FILE *fp;
	int status;
	char path[4096];
	/* Open the command for reading. */
	cAessid[0] = 0;

	fp = popen("./scan.sh", "r");
	if (fp == NULL)
	{
		printf("Failed to run command\n");
		exit(0);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, iLength - 1, fp) != NULL)
	{
		if (strlen(path) > 0)
		{
			printf("%s\n", path);
			strcat(cAessid, path);
			strcat(cAessid, " ");
		}
	}

	/* close */
	pclose(fp);
}
static int begin_request_handler(struct mg_connection *conn)
{
	const struct mg_request_info *ri = mg_get_request_info(conn);
	char post_data[1024], input1[sizeof(post_data)], input2[sizeof(post_data)];
	int post_data_len;
	char cAessid[4096];
	char cAsid[1024];
	int iCount;
	int iPos;
	int iConsumed;

	if (!strcmp(ri->uri, "/wireless.json"))
	{
		//mg_printf(conn, "{ \"0\":\"a\",\"1\":\"b\" }");
		GetEssids(cAessid, sizeof(cAessid));

		iPos=0;
		iCount=0;
		while (sscanf(&cAessid[iPos],"%s%n",cAsid,&iConsumed)==1)
		{
			if (iCount==0)
				mg_printf(conn,"{");
			else
				mg_printf(conn,",");
			iPos+=iConsumed;
			//mg_print(conn,"{ \"%d\":\"%s\",",iCount++,cAsid);
			mg_printf(conn,"\"%d\":\"%s\"",iCount++,cAsid);

		}
		if (iCount>0)
			mg_printf(conn,"}");
		else
			mg_printf(conn,"{ \"0\":\"Scan failed\"}");
		return 1; // Mark request as processed
	}
	return 0;
}

int main(void)
{
	struct mg_context *ctx;
	struct mg_callbacks callbacks;

	printf("Current directory %s\n", getcwd(NULL, 0));
	// List of options. Last element must be NULL.
	const char *options[] = { "listening_ports", "8080", "document_root", "../www", NULL };

	// Prepare callbacks structure. We have only one callback, the rest are NULL.
	memset(&callbacks, 0, sizeof(callbacks));
	callbacks.begin_request = begin_request_handler;

	// Start the web server.
	ctx = mg_start(&callbacks, NULL, options);

	// Wait until user hits "enter". Server is running in separate thread.
	// Navigating to http://localhost:8080 will invoke begin_request_handler().
	getchar();

	// Stop the server.
	mg_stop(ctx);

	return 0;
}

