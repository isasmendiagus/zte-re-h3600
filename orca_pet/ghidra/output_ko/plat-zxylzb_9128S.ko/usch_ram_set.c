// module: plat-zxylzb_9128S.ko
// function: usch_ram_set @ 0x1b0b4
// size: 96 bytes
//

undefined4 usch_ram_set(uint param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
      *(uint *)(tm_base + 0x14014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(tm_base + 0x1401c) = param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0xfffffff5;
}

