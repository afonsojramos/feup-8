#ifndef base64_enc_dec__h
#define base64_enc_dec__h

#include <stdio.h>

size_t b64_encoded_size(size_t inlen);
char *b64_encode(const unsigned char *in, size_t len);
size_t b64_decoded_size(const char *in);
void b64_generate_decode_table();
int b64_isvalidchar(char c);
int b64_decode(const char *in, unsigned char *out, size_t outlen);
void testBase64EncodeAndDecode();

int hexchr2bin(const char hex, char *out);
char *bin2hex(const unsigned char *bin, size_t len);
size_t hexs2bin(const char *hex, unsigned char **out);

#endif