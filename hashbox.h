#ifndef HASHBOX_H
#define HASHBOX_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <openssl/evp.h>
#include "streebog/gost3411-2012-core.h"
#include "grostl/grostl.h"
#include "md6/md6.h"
#include "jh/jh.h"
#include "blake512/blake512.h"
#include "lsh/lsh.h"
#include "skein/SHA3api_ref.h"
#include "keccak3/keccak3.h"
#include "cubehash/cubehash.h"
#include "whirlpool/Whirlpool.h"
#include "fnv512/fnv512.h"

#include "lp_hash.h"

// Return values for 'hashbox_final()'
#define HASHBOX_NO_MATCH 0
#define HASHBOX_SHA512 1
#define HASHBOX_BLAKE2B 2
#define HASHBOX_STREEBOG 3
#define HASHBOX_SHA3 4
#define HASHBOX_FNV0 5
#define HASHBOX_FNV1 6
#define HASHBOX_FNV1A 7
#define HASHBOX_GROSTL 8
#define HASHBOX_MD6 9
#define HASHBOX_JH 10
#define HASHBOX_BLAKE512 11
#define HASHBOX_LSH 12
#define HASHBOX_SKEIN 13
#define HASHBOX_KECCAK3 14
#define HASHBOX_CUBEHASH 15
#define HASHBOX_WHIRLPOOL0 16
#define HASHBOX_WHIRLPOOLT 17
#define HASHBOX_WHIRLPOOL 18

typedef struct {
  EVP_MD_CTX* sha512;
  EVP_MD_CTX* blake2b;
  GOST34112012Context streebog;
  EVP_MD_CTX* sha3;
  fnv512_state_t fnv0;
  fnv512_state_t fnv1;
  fnv512_state_t fnv1a;
  grostl_state_t grostl;
  md6_state md6;
  jh_state_t jh;
  blake512_state_t blake512;
  struct LSH512_Context lsh;
  skein_state_t skein;
  keccak3_ctx_t keccak3;
  cubehash_t cubehash;
  whirlpool_state_t whirlpool0;
  whirlpool_state_t whirlpoolT;
  whirlpool_state_t whirlpool;
} hashbox_t;

typedef struct {
  uint8_t sha512[64];
  uint8_t blake2b[64];
  uint8_t streebog[64];
  uint8_t sha3[64];
  uint8_t fnv0[64];
  uint8_t fnv1[64];
  uint8_t fnv1a[64];
  uint8_t grostl[64];
  uint8_t md6[64];
  uint8_t jh[64];
  uint8_t blake512[64];
  uint8_t lsh[64];
  uint8_t skein[64];
  uint8_t keccak3[64];
  uint8_t cubehash[64];
  uint8_t whirlpool0[64];
  uint8_t whirlpoolT[64];
  uint8_t whirlpool[64];
} hashes_list_t;

// Creates a new hashbox. This hashbox should be freed by calling 'hashbox_final' or 'hashbox_final_hashes'
hashbox_t* hashbox_new();
// Updates all hashes with 'data', of length 'length' bytes
void hashbox_update(hashbox_t* hashbox, uint8_t* data, uint32_t length);
// Computes the digest of each hash, returns HASHBOX_NO_MATCH if none are matching to the DWH,
//  or else the relevant HASHBOX_* constant
unsigned int hashbox_final(hashbox_t* hashbox);
// Same as 'hashbox_final', but returns all hashes in a 'hashes_list_t' instead of a HASHBOX_* constant.
// The returned pointer must be freed using 'free()'
hashes_list_t* hashbox_final_hashes(hashbox_t* hashbox);

#endif
