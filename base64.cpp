#include "base64.h"
#include <string.h>
#include <openssl/evp.h>  
#include <openssl/bio.h>  
#include <openssl/buffer.h>

using namespace std;

std::string base64::base64Encode(const char *buffer, int length, bool newLine)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }

    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);

    string result;
    result.resize(bptr->length + 1);
    memcpy(&result[0], bptr->data, bptr->length);
    result.resize(bptr->length);
    BIO_free_all(b64);

    return result;
}

std::string base64::base64Decode(char *input, int length, bool newLine)
{
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    string result;
    result.resize(length);

    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, &result[0], length);
    BIO_free_all(bmem);
    return result;
}