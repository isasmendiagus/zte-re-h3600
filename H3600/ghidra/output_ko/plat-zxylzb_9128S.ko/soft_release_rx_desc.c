// module: plat-zxylzb_9128S.ko
// function: soft_release_rx_desc @ 0x1a8e8
// size: 176 bytes
//

undefined4 soft_release_rx_desc(int param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_3 != 0;
  bVar2 = param_3 == 1;
  if (param_3 < 2) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
  }
  if (!bVar3 || bVar2) {
    iVar1 = 0x1e;
    do {
      if ((*(uint *)(tm_base + 0x4064) & 1) == 0) {
        *(uint *)(tm_base + 0x4068) = param_1 << 0xe | param_4 << 4 | param_2 | param_3 << 3;
        *(undefined4 *)(tm_base + 0x4064) = 1;
        return 0;
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    printk("failed to rls rx desc\n");
    DAT_0002e994 = DAT_0002e994 + 1;
    return 0xfffffff5;
  }
  return 0xffffffea;
}

