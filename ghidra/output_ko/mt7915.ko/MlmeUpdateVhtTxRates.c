// module: mt7915.ko
// function: MlmeUpdateVhtTxRates @ 0x12c858
// size: 392 bytes
//

void MlmeUpdateVhtTxRates(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s(): invalid wdev (%p)\n","MlmeUpdateVhtTxRates",0,param_4);
    return;
  }
  iVar1 = GetStaCfgByWdev(param_1,param_3);
  if ((*(ushort *)(param_3 + 0x18) & 0x20) == 0) {
    return;
  }
  if (*(byte *)(param_3 + 0x1a) < 0xf) {
    return;
  }
  if ((*(byte *)(param_2 + 0xbfe) & 8) == 0) {
    return;
  }
  if (*(ushort *)(param_2 + 0xc0e) == 0) {
    if (*(ushort *)(param_2 + 0xc0c) == 0) {
      if (*(ushort *)(param_2 + 0xc0a) == 0) {
        bVar2 = 0;
        if (*(ushort *)(param_2 + 0xc08) != 0) {
          if ((*(ushort *)(param_2 + 0xc08) & 0x200) == 0) {
            bVar2 = 7;
          }
          else {
            bVar2 = 9;
          }
        }
      }
      else if ((*(ushort *)(param_2 + 0xc0a) & 0x200) == 0) {
        bVar2 = 0x17;
      }
      else {
        bVar2 = 0x19;
      }
    }
    else if ((*(ushort *)(param_2 + 0xc0c) & 0x200) == 0) {
      bVar2 = 0x27;
    }
    else {
      bVar2 = 0x29;
    }
  }
  else if ((*(ushort *)(param_2 + 0xc0e) & 0x200) == 0) {
    bVar2 = 0x37;
  }
  else {
    bVar2 = 0x39;
  }
  *(byte *)(param_3 + 0x8b5) = *(byte *)(param_3 + 0x8b5) & 0x1f | 0x80;
  *(byte *)(param_3 + 0x8b4) = *(byte *)(param_3 + 0x8b4) & 0xc0 | bVar2;
  if (iVar1 != 0) {
    uVar3 = (uint)*(byte *)(iVar1 + 0x40f3);
    if (uVar3 == 1) {
      *(ushort *)(param_3 + 0x8b4) = *(ushort *)(param_3 + 0x8b4) & 0xfe7f | 0x100;
      uVar3 = (uint)*(byte *)(iVar1 + 0x40f3);
    }
    if (uVar3 - 2 < 2) {
      *(ushort *)(param_3 + 0x8b4) = *(ushort *)(param_3 + 0x8b4) | 0x180;
    }
  }
  iVar1 = DebugLevel;
  *(undefined2 *)(param_3 + 0x8b2) = *(undefined2 *)(param_3 + 0x8b4);
  if (iVar1 < 3) {
    return;
  }
  printk("%s() MaxHTPhyMode=%x\n","MlmeUpdateVhtTxRates",*(undefined2 *)(param_3 + 0x8b4),param_4);
  return;
}

