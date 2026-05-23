// module: mt7915.ko
// function: vow_init_CR_offset @ 0x42468
// size: 308 bytes
//

void vow_init_CR_offset(int param_1)

{
  if (*(char *)(param_1 + 0xa797a4) == '\0') {
    *(undefined4 *)(param_1 + 0xa797ac) = 0;
    *(undefined4 *)(param_1 + 0xa797b4) = 0;
    *(undefined4 *)(param_1 + 0xa797b0) = 0x10;
    *(undefined4 *)(param_1 + 0xa797b8) = 0x10;
    *(undefined4 *)(param_1 + 0xa797c0) = 3;
    *(undefined4 *)(param_1 + 0xa797c4) = 4;
    *(undefined4 *)(param_1 + 0xa797c8) = 6;
    *(undefined4 *)(param_1 + 0xa797cc) = 8;
    *(undefined4 *)(param_1 + 0xa797bc) = 0x20;
    *(undefined4 *)(param_1 + 0xa797d0) = 10;
    *(undefined4 *)(param_1 + 0xa797d4) = 0xc;
    *(undefined4 *)(param_1 + 0xa797d8) = 0xe;
    return;
  }
  if (*(char *)(param_1 + 0xa797a4) != '\x01') {
    *(undefined4 *)(param_1 + 0xa797ac) = 0x1c;
    *(undefined4 *)(param_1 + 0xa797b8) = 0x1c;
    *(undefined4 *)(param_1 + 0xa797b0) = 0x3c;
    *(undefined4 *)(param_1 + 0xa797b4) = 0xc;
    *(undefined4 *)(param_1 + 0xa797cc) = 0xc;
    *(undefined4 *)(param_1 + 0xa797bc) = 0;
    *(undefined4 *)(param_1 + 0xa797c0) = 2;
    *(undefined4 *)(param_1 + 0xa797c4) = 4;
    *(undefined4 *)(param_1 + 0xa797c8) = 8;
    *(undefined4 *)(param_1 + 0xa797d0) = 0x10;
    *(undefined4 *)(param_1 + 0xa797d4) = 0x14;
    *(undefined4 *)(param_1 + 0xa797d8) = 6;
    return;
  }
  *(undefined4 *)(param_1 + 0xa797ac) = 0x44;
  *(undefined4 *)(param_1 + 0xa797b8) = 0x44;
  *(undefined4 *)(param_1 + 0xa797b4) = 0x34;
  *(undefined4 *)(param_1 + 0xa797bc) = 0;
  *(undefined4 *)(param_1 + 0xa797c0) = 2;
  *(undefined4 *)(param_1 + 0xa797c4) = 4;
  *(undefined4 *)(param_1 + 0xa797c8) = 8;
  *(undefined4 *)(param_1 + 0xa797cc) = 0xc;
  *(undefined4 *)(param_1 + 0xa797b0) = 100;
  *(undefined4 *)(param_1 + 0xa797d0) = 0x10;
  *(undefined4 *)(param_1 + 0xa797d4) = 0x14;
  *(undefined4 *)(param_1 + 0xa797d8) = 6;
  return;
}

