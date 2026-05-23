// module: plat-zxylzb_9128S.ko
// function: red_get_queue_status @ 0x1a7e0
// size: 188 bytes
//

undefined4 red_get_queue_status(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | 0x8400000;
      iVar2 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_0002e9a0 = DAT_0002e9a0 + 1;
  return 0xfffffff5;
}

