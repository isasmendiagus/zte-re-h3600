// module: mt7915.ko
// function: GetRegulatoryMaxTxPwr @ 0x13e2f8
// size: 236 bytes
//

byte GetRegulatoryMaxTxPwr(int param_1,uint param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  
  iVar2 = GetChRegion(param_1 + 0x794c31);
  if ((iVar2 == 0) || (pbVar6 = *(byte **)(iVar2 + 8), pbVar6 == (byte *)0x0)) {
    if (-1 < DebugLevel) {
      printk("%s(): pChRegion is NULL\n","GetRegulatoryMaxTxPwr");
      return 0xff;
    }
  }
  else {
    uVar5 = (uint)*pbVar6;
    bVar1 = pbVar6[1];
    if (uVar5 != 0) {
      uVar3 = 0;
      do {
        uVar4 = 0;
        if (bVar1 != 0 && uVar5 <= param_2) {
          do {
            uVar4 = uVar4 + 1;
            if (uVar5 < 0xf) {
              iVar2 = 1;
            }
            else {
              iVar2 = 4;
            }
            if (param_2 == uVar5) {
              return pbVar6[uVar3 * 5 + 2];
            }
            uVar5 = iVar2 + uVar5 & 0xff;
          } while (uVar4 < bVar1);
        }
        uVar3 = uVar3 + 1 & 0xff;
        uVar5 = (uint)pbVar6[uVar3 * 5];
        bVar1 = pbVar6[uVar3 * 5 + 1];
      } while (uVar5 != 0);
    }
  }
  return 0xff;
}

