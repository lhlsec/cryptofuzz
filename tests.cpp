#include "tests.h"
#include <fuzzing/datasource/id.hpp>
#include <cryptofuzz/repository.h>
#include <cryptofuzz/util.h>

namespace cryptofuzz {
namespace tests {

template <class ResultType, class OperationType>
void verifyKeySize(const OperationType& op, const ResultType& result) {
    if ( result != std::nullopt && op.keySize != result->GetSize() ) {
        /* TODO include module name in abort message */
        util::abort({op.Name(), "invalid keySize"});
    }
}

void test(const operation::Digest& op, const std::optional<component::Digest>& result) {
    (void)op;
    (void)result;
}

void test(const operation::HMAC& op, const std::optional<component::MAC>& result) {
    (void)op;
    (void)result;
}

static void test_ChaCha20_Poly1305_IV(const operation::SymmetricEncrypt& op, const std::optional<component::Ciphertext>& result) {
    using fuzzing::datasource::ID;

    /*
     * OpenSSL CVE-2019-1543
     * https://www.openssl.org/news/secadv/20190306.txt
     */

    if ( op.cipher.cipherType.Get() != CF_CIPHER("CHACHA20_POLY1305") ) {
        return;
    }

    if ( result == std::nullopt ) {
        return;
    }

    if ( op.cipher.iv.GetSize() > 12 ) {
        abort();
    }
}

void test(const operation::SymmetricEncrypt& op, const std::optional<component::Ciphertext>& result) {
    test_ChaCha20_Poly1305_IV(op, result);
}

void test(const operation::SymmetricDecrypt& op, const std::optional<component::Cleartext>& result) {
    (void)op;
    (void)result;
}

void test(const operation::CMAC& op, const std::optional<component::MAC>& result) {
    (void)op;
    (void)result;
}

void test(const operation::KDF_SCRYPT& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_HKDF& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_TLS1_PRF& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_PBKDF& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_PBKDF1& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_PBKDF2& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_ARGON2& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_SSH& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::KDF_X963& op, const std::optional<component::Key>& result) {
    verifyKeySize(op, result);
}

void test(const operation::Sign& op, const std::optional<component::Signature>& result) {
    (void)op;
    (void)result;
}

void test(const operation::Verify& op, const std::optional<bool>& result) {
    (void)op;
    (void)result;
}

void test(const operation::ECC_PrivateToPublic& op, const std::optional<component::ECC_PublicKey>& result) {
    (void)op;
    (void)result;
}

void test(const operation::ECC_GenerateKeyPair& op, const std::optional<component::ECC_KeyPair>& result) {
    (void)op;
    (void)result;
}

void test(const operation::ECDSA_Sign& op, const std::optional<component::ECDSA_Signature>& result) {
    (void)op;
    (void)result;
}

void test(const operation::ECDSA_Verify& op, const std::optional<bool>& result) {
    (void)op;
    (void)result;
}

void test(const operation::ECDH_Derive& op, const std::optional<component::Secret>& result) {
    (void)op;
    (void)result;
}

void test(const operation::BignumCalc& op, const std::optional<component::Bignum>& result) {
    (void)op;
    (void)result;
}

} /* namespace tests */
} /* namespace cryptofuzz */
