// module: mt7915.ko
// function: MT_ATESetTxPowerX @ 0x27e784
// size: 288 bytes
//

void MT_ATESetTxPowerX(int param_1,undefined4 param_2,undefined4 param_3,uint param_4,int param_5,
                      uint param_6)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = net_ad_wrap_service();
  bVar1 = *(byte *)(iVar3 + param_5 * 0xd18 + 0x1130);
  iVar3 = net_ad_wrap_service(param_1);
  if (param_4 == 0) {
    param_4 = (uint)bVar1;
  }
  uVar4 = (uint)*(byte *)(iVar3 + param_5 * 0xd18 + 0x1131);
  if (uVar4 != 0) {
    param_6 = uVar4;
  }
  if (0xe < param_4) {
    param_6 = 1;
  }
  if (2 < DebugLevel) {
    printk("%s: Channel:%d Power:%x Ch_Band:%d Ant:%d\n","MT_ATESetTxPowerX",param_4,param_3,param_6
           ,param_2);
  }
  uVar2 = (undefined1)param_3;
  switch(param_2) {
  case 0:
    *(undefined1 *)(param_1 + 0xa3ac1c) = uVar2;
    break;
  case 1:
    *(undefined1 *)(param_1 + 0xa3ac1d) = uVar2;
    break;
  case 2:
    *(undefined1 *)(param_1 + 0xa3ac1e) = uVar2;
    break;
  case 3:
    *(undefined1 *)(param_1 + 0xa3ac1f) = uVar2;
  }
  MtCmdSetTxPowerCtrl(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

