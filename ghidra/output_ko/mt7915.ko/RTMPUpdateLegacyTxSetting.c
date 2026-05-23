// module: mt7915.ko
// function: RTMPUpdateLegacyTxSetting @ 0x131810
// size: 340 bytes
//

void RTMPUpdateLegacyTxSetting(int param_1,int param_2)

{
  undefined2 uVar1;
  byte bVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort uVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  
  if (2 < param_1 - 1U) {
    return;
  }
  uVar7 = *(byte *)(param_2 + 0xbc) & 0x3f;
  uVar5 = (ushort)uVar7;
  if (param_1 == 3) {
    uVar4 = ((uint)*(ushort *)(param_2 + 0xbe) << 0x17) >> 0x1e;
    uVar8 = *(byte *)(param_2 + 0xbc) & 0xf;
    sVar6 = (short)uVar8;
    if (uVar4 == 0) {
      if (8 < uVar8) {
        sVar6 = 8;
      }
    }
    else if (uVar4 == 1) {
      if (8 < uVar8) {
        sVar6 = 9;
      }
    }
    else if (uVar4 == 2) {
      if (uVar8 < 10) {
        if (uVar7 >> 4 == 2 && uVar8 == 6) {
          sVar6 = 5;
        }
      }
      else {
        sVar6 = 9;
      }
    }
    bVar2 = 4;
    uVar5 = (ushort)(uVar4 << 7) | 0x8000 | sVar6 + (short)(uVar7 >> 4) * 0x10 & 0x3fU;
  }
  else {
    if (param_1 == 1) {
      if (3 < uVar7) {
        uVar5 = 3;
      }
      goto LAB_001318a0;
    }
    bVar2 = 1;
    uVar5 = uVar5 | 0x2000;
    if (7 < uVar7) {
      uVar5 = 0x2007;
    }
  }
  if (*(byte *)(param_2 + 0xbd) >> 5 < bVar2) {
    if (-1 < DebugLevel) {
      printk("%s : the fixed TxMode is invalid\n","RTMPUpdateLegacyTxSetting");
      return;
    }
    return;
  }
LAB_001318a0:
  *(ushort *)(param_2 + 0xbc) = uVar5;
  if (2 < DebugLevel) {
    uVar1 = *(undefined2 *)(param_2 + 0xe0);
    uVar3 = get_phymode_str(*(byte *)(param_2 + 0xbd) >> 5);
    printk("RTMPUpdateLegacyTxSetting : wcid-%d, MODE=%s, MCS=%d\n",uVar1,uVar3,
           *(byte *)(param_2 + 0xbc) & 0x3f);
    return;
  }
  return;
}

