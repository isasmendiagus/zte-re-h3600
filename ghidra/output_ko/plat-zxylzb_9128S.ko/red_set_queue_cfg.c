// module: plat-zxylzb_9128S.ko
// function: red_set_queue_cfg @ 0x1a618
// size: 208 bytes
//

undefined4 red_set_queue_cfg(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(tm_base + 0x4028) = param_2[3];
      *(undefined4 *)(tm_base + 0x4024) = param_2[2];
      *(undefined4 *)(tm_base + 0x4020) = param_2[1];
      *(undefined4 *)(tm_base + 0x401c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_0002e998 = DAT_0002e998 + 1;
  return 0xfffffff5;
}

