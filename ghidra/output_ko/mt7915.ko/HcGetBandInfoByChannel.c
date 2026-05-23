// module: mt7915.ko
// function: HcGetBandInfoByChannel @ 0xa9cc0
// size: 192 bytes
//

bool HcGetBandInfoByChannel(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    return false;
  }
  iVar4 = *(int *)(param_1 + 0xa797a0);
  uVar5 = iVar4 + 0x1000;
  bVar1 = *(byte *)(iVar4 + 0x32d8);
  if (bVar1 != 0) {
    bVar2 = *(byte *)(iVar4 + 0x1360);
    if (((bVar2 & 1) == 0) && ((bVar1 < 2 || ((*(byte *)(iVar4 + 0x16b4) & 1) == 0)))) {
      bVar3 = bVar2 & 2;
      if ((bVar2 & 2) != 0) goto LAB_000a9d3c;
    }
    else {
      if ((bVar2 & 2) != 0) goto LAB_000a9d60;
      bVar3 = 1;
    }
    if (((1 < bVar1) &&
        (uVar5 = (uint)*(byte *)(iVar4 + 0x16b4), (*(byte *)(iVar4 + 0x16b4) & 2) != 0)) &&
       (bVar3 != 0)) {
LAB_000a9d60:
      return 0xe < param_2;
    }
  }
LAB_000a9d3c:
  printk(&_LC27,0x3e4,bVar1,uVar5,param_4);
  dump_stack();
  return false;
}

