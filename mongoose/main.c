#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static int begin_request_handler(struct mg_connection *conn)
{
	const struct mg_request_info *ri = mg_get_request_info(conn);
	char post_data[1024], input1[sizeof(post_data)], input2[sizeof(post_data)];
	int post_data_len;

	if (!strcmp(ri->uri, "/handle_post_request"))
	{
		// User has submitted a form, show submitted data and a variable value
		post_data_len = mg_read(conn, post_data, sizeof(post_data));

		// Parse form data. input1 and input2 are guaranteed to be NUL-terminated
		mg_get_var(post_data, post_data_len, "input_1", input1, sizeof(input1));
		mg_get_var(post_data, post_data_len, "input_2", input2, sizeof(input2));

		// Send reply to the client, showing submitted form values.
		mg_printf(conn, "HTTP/1.0 200 OK\r\n"
				"Content-Type: text/plain\r\n\r\n"
				"Submitted data: [%.*s]\n"
				"Submitted data length: %d bytes\n"
				"input_1: [%s]\n"
				"input_2: [%s]\n", post_data_len, post_data, post_data_len, input1, input2);
	}
	else
	{
		// Show HTML form.
		mg_printf(conn, "HTTP/1.0 200 OK\r\n"
				"Content-Length: %d\r\n"
				"Content-Type: text/html\r\n\r\n%s", (int) strlen(html_form), html_form);
	}
	return 1; // Mark request as processed
}

int main(void)
{
	struct mg_context *ctx;
	struct mg_callbacks callbacks;

	// List of options. Last element must be NULL.
	const char *options[] = { "listening_ports", "8080", NULL };

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

