//
// Created by lunar on 02/11/18.
//

#include "init.hpp"

#include <openssl/ssl.h>

namespace SSLWrap {

	void init() {
		OpenSSL_add_ssl_algorithms();
		SSL_load_error_strings();
	}

	void cleanup() {
		FIPS_mode_set(0);
		EVP_cleanup();
		CRYPTO_cleanup_all_ex_data();

	}

}