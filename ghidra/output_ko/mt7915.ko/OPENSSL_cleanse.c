// module: mt7915.ko
// function: OPENSSL_cleanse @ 0x20cffc
// size: 12 bytes
//

void OPENSSL_cleanse(void *ptr,size_t len)

{
  if (len == 0) {
    return;
  }
  __memzero();
  return;
}

