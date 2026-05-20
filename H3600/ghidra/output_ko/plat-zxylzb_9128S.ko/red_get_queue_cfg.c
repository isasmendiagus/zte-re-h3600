// module: plat-zxylzb_9128S.ko
// function: red_get_queue_cfg @ 0x1a6e8
// size: 248 bytes
//

undefined4 red_get_queue_cfg(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar2 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | 0x8000000;
      iVar1 = tm_base;
      iVar3 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
          param_2[3] = *(undefined4 *)(tm_base + 0x4028);
          iVar2 = tm_base;
          param_2[2] = *(undefined4 *)(iVar1 + 0x4024);
          iVar1 = tm_base;
          param_2[1] = *(undefined4 *)(iVar2 + 0x4020);
          *param_2 = *(undefined4 *)(iVar1 + 0x401c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  DAT_0002e99c = DAT_0002e99c + 1;
  return 0xfffffff5;
}

