// module: mt7915.ko
// function: entrytb_aid_bitmap_free @ 0x14acf8
// size: 36 bytes
//

void entrytb_aid_bitmap_free(int *param_1)

{
  if (*param_1 != 0) {
    os_free_mem();
  }
  *param_1 = 0;
  return;
}

