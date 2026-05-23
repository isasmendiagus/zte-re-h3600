// module: plat-zxylzb_9128S.ko
// function: usch_ram_get @ 0x1ab34
// size: 140 bytes
//

undefined4 usch_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
      *(uint *)(tm_base + 0x14014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 5;
      do {
        if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x1401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0xfffffff5;
}

