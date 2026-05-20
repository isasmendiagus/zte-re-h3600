// module: mt7915.ko
// function: MT_ATESetTxFreqOffset @ 0x27e718
// size: 104 bytes
//

void MT_ATESetTxFreqOffset(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar2 + 0x4cc);
  iVar3 = net_ad_wrap_service(param_1);
  iVar2 = DebugLevel;
  *(undefined4 *)((uint)bVar1 * 0xd18 + iVar3 + 0x1148) = param_2;
  if (2 < iVar2) {
    printk(&_LC65,"MT_ATESetTxFreqOffset");
  }
  MtCmdSetFreqOffset(param_1,param_2,(uint)bVar1);
  return;
}

