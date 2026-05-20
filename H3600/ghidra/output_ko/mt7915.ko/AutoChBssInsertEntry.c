// module: mt7915.ko
// function: AutoChBssInsertEntry @ 0x1f980
// size: 512 bytes
//

uint AutoChBssInsertEntry
               (undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4,byte param_5,
               byte param_6,byte param_7,undefined4 param_8)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  
  uVar1 = HcGetBandByWdev(param_8);
  iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
  pbVar4 = *(byte **)(iVar2 + 4);
  if (pbVar4 == (byte *)0x0) {
    if (DebugLevel < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      printk("pAd->pBssInfoTab equal NULL.\n");
      uVar3 = 0xffffffff;
    }
  }
  else {
    uVar3 = AutoChBssSearchWithSSID(param_1,param_2,param_3,param_4,param_5,param_8);
    if (uVar3 == 0xffffffff) {
      uVar3 = (uint)*pbVar4;
      *(undefined4 *)(pbVar4 + uVar3 * 0x2a + 1) = *param_2;
      *(undefined2 *)(pbVar4 + uVar3 * 0x2a + 5) = *(undefined2 *)(param_2 + 1);
      if ((param_4 - 1 < 0x20) && (iVar2 = memcmp(param_3,ZeroSsid,param_4), iVar2 != 0)) {
        memmove(pbVar4 + uVar3 * 0x2a + 8,param_3,param_4);
        pbVar4[uVar3 * 0x2a + 7] = (byte)param_4;
      }
      pbVar4[uVar3 * 0x2a + 0x28] = param_5;
      pbVar4[uVar3 * 0x2a + 0x29] = param_6;
      pbVar4[uVar3 * 0x2a + 0x2a] = param_7;
      *pbVar4 = *pbVar4 + 1;
      return uVar3;
    }
    uVar5 = uVar3 & 0xff;
    *(undefined4 *)(pbVar4 + uVar5 * 0x2a + 1) = *param_2;
    *(undefined2 *)(pbVar4 + uVar5 * 0x2a + 5) = *(undefined2 *)(param_2 + 1);
    if ((param_4 - 1 < 0x20) && (iVar2 = memcmp(param_3,ZeroSsid,param_4), iVar2 != 0)) {
      memmove(pbVar4 + uVar5 * 0x2a + 8,param_3,param_4);
      pbVar4[uVar5 * 0x2a + 7] = (byte)param_4;
    }
    pbVar4[uVar5 * 0x2a + 0x28] = param_5;
    pbVar4[uVar5 * 0x2a + 0x29] = param_6;
    pbVar4[uVar5 * 0x2a + 0x2a] = param_7;
  }
  return uVar3;
}

