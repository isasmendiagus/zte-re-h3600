// module: mt7915.ko
// function: WtcInit @ 0xad910
// size: 120 bytes
//

void WtcInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  
  iVar5 = *(int *)(param_1 + 0x4328);
  os_zero_mem(param_1 + 0x1a28,0x120c,param_3,param_1 + 0x4000,param_4);
  uVar4 = 0;
  *(undefined4 *)(param_1 + 0x2c30) = 0;
  puVar3 = (undefined1 *)(param_1 + 0x1a30);
  while( true ) {
    uVar2 = uVar4 & 0xffff;
    uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar5 + 0xa797a0));
    uVar4 = uVar4 + 1;
    bVar6 = 0x11e < uVar2;
    if (uVar2 < 0x120) {
      bVar6 = uVar1 <= uVar2;
    }
    if (bVar6) break;
    *puVar3 = 0;
    puVar3[6] = 0;
    puVar3 = puVar3 + 0x10;
  }
  return;
}

