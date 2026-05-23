// module: mt7915.ko
// function: MT_ATESetForceTxPower @ 0x27e8b8
// size: 200 bytes
//

undefined4
MT_ATESetForceTxPower
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = (uint)*(byte *)(param_1 + 0xa3ae36);
  iVar1 = net_ad_wrap_service();
  iVar3 = uVar4 * 0xd18;
  *(char *)(iVar1 + iVar3 + 0x1135) = (char)param_3;
  iVar1 = net_ad_wrap_service(param_1);
  *(char *)(iVar1 + iVar3 + 0x1138) = (char)param_4;
  iVar2 = net_ad_wrap_service(param_1);
  iVar1 = DebugLevel;
  *(undefined1 *)(iVar2 + iVar3 + 0x1136) = param_5;
  if (0 < iVar1) {
    printk("%s: Band(%d), PhyMode(%d), MCS(%d), BW(%d), TxPower(%d)\n","MT_ATESetForceTxPower",uVar4
           ,param_3,param_4,param_5,param_2);
  }
  MtCmdSetForceTxPowerCtrl(param_1,uVar4,param_2,param_3,param_4,param_5);
  return 0;
}

