// module: mt7915.ko
// function: mt_BfSoundingAdjust @ 0x850fc
// size: 464 bytes
//

void mt_BfSoundingAdjust(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = GetAssociatedAPByWdev(param_1,param_3);
  if (param_3 == 0 || iVar1 == 0) {
    return;
  }
  uVar3 = (uint)*(ushort *)(iVar1 + 0xe0);
  if (2 < DebugLevel) {
    printk("[%s]WlanIdx=%d, ConnectionState=%d\n","mt_BfSoundingAdjust",uVar3,param_2);
  }
  uVar2 = HcGetMaxStaNum(param_1);
  if (uVar2 <= uVar3) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[%s]pEntry is NULL!!\n","mt_BfSoundingAdjust");
    return;
  }
  if (param_2 == 1) {
    if (DebugLevel < 3) {
      if ((*(byte *)(uVar3 * 0x14c0 + param_1 + 0xa295d) & 1) != 0) {
LAB_00085204:
        CmdETxBfSoundingPeriodicTriggerCtrl(param_1,1,0,4,0,0);
        return;
      }
    }
    else {
      iVar1 = uVar3 * 0x14c0 + param_1;
      printk("[%s][ETxBfCap=%d\n","mt_BfSoundingAdjust",*(byte *)(iVar1 + 0xa295d) & 1);
      if ((*(byte *)(iVar1 + 0xa295d) & 1) != 0) {
        if (2 < DebugLevel) {
          printk("[%s][STA mode][Conn]Start BF process timer\n","mt_BfSoundingAdjust");
        }
        goto LAB_00085204;
      }
      if (2 < DebugLevel) {
        printk("[%s][STA mode][Conn]Stop BF process timer\n","mt_BfSoundingAdjust");
      }
    }
  }
  else {
    if (param_2 != 0) {
      return;
    }
    if ((*(byte *)(uVar3 * 0x14c0 + param_1 + 0xa295d) & 1) == 0) {
      return;
    }
    if (2 < DebugLevel) {
      printk("[%s][STA mode][DisConn]Stop BF process timer\n","mt_BfSoundingAdjust");
    }
  }
  CmdETxBfSoundingPeriodicTriggerCtrl(param_1,0,0,4,0,0);
  return;
}

