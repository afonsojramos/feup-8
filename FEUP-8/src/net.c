// MIT License

// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "net.h"
#include "tic.h"
#include "SDL_net.h"
#include "web_comunication_api.h"
#include "cJSON.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MEGABYTE 1024*1024

struct Net
{
	struct
	{
		u8* buffer;
		s32 size;
		char path[FILENAME_MAX];
	} cache;
};


typedef void(*NetResponse)(u8* buffer, s32 size, void* data);

#if defined(__EMSCRIPTEN__)

static void getRequest(Net* net, const char* path, NetResponse callback, void* data)
{
	callback(NULL, 0, data);
}

#else

static void netClearCache(Net* net)
{
	if(net->cache.buffer)
		free(net->cache.buffer);

	net->cache.buffer = NULL;
	net->cache.size = 0;
	memset(net->cache.path, 0, sizeof net->cache.path);
}

/**
* Changes the pointer to the returned data in http reponse, in order to get only the data, placed after the double /r/n.
* @param buf The struct Buffer that contains the data received, of which the pointer will be changed.
*/
static void getDataFromHttpResponse(Buffer *buf)
{
	char *ocurrence = strstr(buf->data, "\r\n\r\n");
	ocurrence += sizeof(char) * strlen("\r\n\r\n");
	size_t new_size = sizeof(char) * (strlen(ocurrence) + 1);
	char *new_data = malloc(new_size);
	memcpy(new_data, ocurrence, new_size);
	new_data[new_size - 1] = '\0';
	free(buf->data);
	buf->data = new_data;
	buf->size = new_size;
}

/**
* Builds a string to send as http parameter according to the key and value received as parameters.
* @param key A strin representing the key to be sent as http parameter.
* @param value A stringg representing the value to be sent as http parameter.
* @return A string representing what should be sent through the socket according to the http standard.
*/
char *buildHttpParameter(const char *key, const char *value)
{
	size_t key_size = sizeof(char) * (strlen(key) + 1);
	char *parameter = malloc(key_size);
	memcpy(parameter, key, key_size);
	parameter = concateStrings(parameter, value);
	parameter = concateStrings(parameter, "\r\n");

	return parameter;
}

/**
* Creates a string being the concate of two string
* @param string1, the left side of the resultante string.
* @param string2, the right side of the resultante string.
* @return A string, the concate string.
*/
char* concateStrings(const char *string1, const char *string2)
{
    size_t resultSize = sizeof(char) * (strlen(string1) + strlen(string2) + 1);
    char *result = malloc(resultSize);
    memset(result, 0, resultSize);
    sprintf(result, "%s%s", string1, string2);

    return result;
}

/**
* Sends a http request of type GET to adress:port/path with the data in the dataToSend paramater. Returns the received response, also a BUffer* with the data.
* @param address The address of the server.
* @param port The port of the server.
* @param path The path to the request.
* @param dataToSend The data to be sent to the server.
* @param timeout The timeout it waits to the request be done.
* @return A Buffer with the data received from the server as response.
* Example: GET api/exercises?auth_token=hjfkhkasj HTTP/1.1\r\nHost: server.pt\r\n\r\n
*/
Buffer sendHttpGetRequest(const char* address, int port, const char* path, Buffer *dataToSend, char *additionalHeaderString, s32 timeout)
{
	if (additionalHeaderString == NULL)
		additionalHeaderString = "";
	Buffer dataToSend_;
	if (dataToSend == NULL)
	{
		dataToSend_.data = "";
		dataToSend_.size = 0;
		dataToSend = &dataToSend_;
	}
	int GET_MESSAGE_DEFAULT_SIZE = 26;
	int messageSize = GET_MESSAGE_DEFAULT_SIZE + strlen(path) + dataToSend->size + strlen(address) + strlen(additionalHeaderString);
	char message[messageSize];
	memset(message, 0, sizeof message);
	sprintf(message, "GET %s?%s HTTP/1.1\r\nHost: %s\r\n%s\r\n", path, dataToSend->data, address, additionalHeaderString);
	return sendHttpRequest(address, port, path, message, messageSize, timeout);
}

/**
* Sends a http request of type POST to adress:port/path with the data in the dataToSend paramater. Returns the received response, also a BUffer* with the data.
* @param address The address of the server.
* @param port The port of the server.
* @param path The path to the request.
* @param dataToSend The data to be sent to the server.
* @param timeout The timeout it waits to the request be done.
* @return A Buffer with the data received from the server as response.
* Example: "POST api/exercises HTTP/1.1\r\nHost: server.pt\r\nContent-type: application/x-www-form-urlencoded\r\nContent-Length: 20\r\n\r\nauth_token=hjfkhkasj"
*/
Buffer sendHttpPostRequest(const char* address, int port, const char* path, Buffer *dataToSend, char *additionalHeaderString, s32 timeout)
{
	if (additionalHeaderString == NULL)
		additionalHeaderString = "";
	Buffer dataToSend_;
	if (dataToSend == NULL)
	{
		dataToSend_.data = "";
		dataToSend_.size = 0;
		dataToSend = &dataToSend_;
	}
	int POST_MESSAGE_DEFAULT_SIZE = 103;
	size_t dataToSend_size_size = (log10(dataToSend->size) + 1);
	int messageSize = POST_MESSAGE_DEFAULT_SIZE + strlen(path) + strlen(address) + dataToSend_size_size + strlen(additionalHeaderString) + dataToSend->size;
	char message[messageSize];
	memset(message, 0, messageSize);
	sprintf(message, "POST %s HTTP/1.1\r\nHost: %s\r\nContent-type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\n%s\r\n%s", path, address, dataToSend->size, additionalHeaderString, dataToSend->data);

	return sendHttpRequest(address, port, path, message, messageSize, timeout);
}

static Buffer sendHttpRequest(const char* address, int port, const char* path, char *message, int messageSize, s32 timeout)
{
	Buffer buffer = {.data = NULL, .size = 0};
{
		IPaddress ip;
		if (SDLNet_ResolveHost(&ip, address, port) >= 0)
		{
			TCPsocket sock = SDLNet_TCP_Open(&ip);

			if (sock)
			{

				SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);

				if(set)
				{
					SDLNet_TCP_AddSocket(set, sock);

					{
						SDLNet_TCP_Send(sock, message, (s32)strlen(message));
					}

					if(SDLNet_CheckSockets(set, timeout) == 1 && SDLNet_SocketReady(sock))
					{
						enum {Size = MEGABYTE};
						buffer.data = malloc(Size);
						s32 size = 0;

						for(;;)
						{
							size = SDLNet_TCP_Recv(sock, buffer.data + buffer.size, Size-1);

							if(size > 0)
							{
								buffer.size += size;
								buffer.data = realloc(buffer.data, buffer.size + Size);
							}
							else break;
						}

						getDataFromHttpResponse(&buffer);
						buffer.data[buffer.size] = '\0';
					}

					SDLNet_FreeSocketSet(set);
				}

				SDLNet_TCP_Close(sock);
			}
		}
	}

	return buffer;
}

static Buffer httpRequest(const char* path, s32 timeout)
{
	Buffer buffer = {.data = NULL, .size = 0};

	{
		IPaddress ip;

		if (SDLNet_ResolveHost(&ip, TIC_HOST, 80) >= 0)
		{
			TCPsocket sock = SDLNet_TCP_Open(&ip);

			if (sock)
			{
				SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);

				if(set)
				{
					SDLNet_TCP_AddSocket(set, sock);

					{
						char message[FILENAME_MAX];
						memset(message, 0, sizeof message);
						sprintf(message, "GET %s HTTP/1.0\r\nHost: " TIC_HOST "\r\n\r\n", path);
						SDLNet_TCP_Send(sock, message, (s32)strlen(message) + 1);
					}

					if(SDLNet_CheckSockets(set, timeout) == 1 && SDLNet_SocketReady(sock))
					{
						enum {Size = 4*1024+1};
						buffer.data = malloc(Size);
						s32 size = 0;

						for(;;)
						{
							size = SDLNet_TCP_Recv(sock, buffer.data + buffer.size, Size-1);

							if(size > 0)
							{
								buffer.size += size;
								buffer.data = realloc(buffer.data, buffer.size + Size);
							}
							else break;
						}

						buffer.data[buffer.size] = '\0';
					}

					SDLNet_FreeSocketSet(set);
				}

				SDLNet_TCP_Close(sock);
			}
		}
	}

	return buffer;
}

static void getRequest(Net* net, const char* path, NetResponse callback, void* data)
{
	if(strcmp(net->cache.path, path) == 0)
	{
		callback(net->cache.buffer, net->cache.size, data);
	}
	else
	{
		netClearCache(net);

		bool done = false;

		enum {Timeout = 3000};
		Buffer buffer = httpRequest(path, Timeout);

		if(buffer.data && buffer.size)
		{
			if(strstr((char*)buffer.data, "200 OK"))
			{
				s32 contentLength = 0;

				{
					static const char ContentLength[] = "Content-Length:";

					char* start = strstr((char*)buffer.data, ContentLength);

					if(start)
						contentLength = atoi(start + sizeof(ContentLength));
				}

				static const char Start[] = "\r\n\r\n";
				u8* start = (u8*)strstr((char*)buffer.data, Start);

				if(start)
				{
					strcpy(net->cache.path, path);
					net->cache.size = contentLength ? contentLength : buffer.size - (s32)(start - buffer.data);
					net->cache.buffer = (u8*)malloc(net->cache.size);
					memcpy(net->cache.buffer, start + sizeof Start - 1, net->cache.size);
					callback(net->cache.buffer, net->cache.size, data);
					done = true;
				}
			}

			free(buffer.data);
		}

		if(!done)
			callback(NULL, 0, data);
	}
}

#endif

typedef struct
{
	void* buffer;
	s32* size;
} NetGetData;

static void onGetResponse(u8* buffer, s32 size, void* data)
{
	NetGetData* netGetData = (NetGetData*)data;

	netGetData->buffer = malloc(size);
	*netGetData->size = size;
	memcpy(netGetData->buffer, buffer, size);
}

void* netGetRequest(Net* net, const char* path, s32* size)
{
	NetGetData netGetData = {NULL, size};
	getRequest(net, path, onGetResponse, &netGetData);

	return netGetData.buffer;
}

Net* createNet()
{
	SDLNet_Init();

	Net* net = (Net*)malloc(sizeof(Net));

	*net = (Net)
	{
		.cache =
		{
			.buffer = NULL,
			.size = 0,
			.path = {0},
		},
	};

	return net;
}

void closeNet(Net* net)
{
	free(net);

	SDLNet_Quit();
}
