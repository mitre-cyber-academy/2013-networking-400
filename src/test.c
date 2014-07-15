#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <string.h>


int main()
{
	char* message = "136934373096c70ab05a922178e0668ba5402160d7";
	char buff[SHA256_DIGEST_LENGTH];
	SHA256(message, strlen(message), buff);
	write(0, buff, SHA256_DIGEST_LENGTH);
	return 0;
}
