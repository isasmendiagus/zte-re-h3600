// module: mt7915.ko
// function: MT_ATESetBW @ 0x27c184
// size: 204 bytes
//

undefined4 MT_ATESetBW(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 uVar5;
  uint uVar6;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  uVar5 = (undefined1)param_2;
  if (param_3 == 10) {
    if (param_2 == 6) {
      param_3 = 3;
      uVar5 = 6;
      uVar6 = param_3;
    }
    else {
      param_3 = param_2;
      uVar6 = param_2 & 0xff;
    }
  }
  else {
    if (param_2 <= param_3) {
      param_3 = param_2;
    }
    uVar6 = param_3 & 0xff;
  }
  iVar2 = net_ad_wrap_service(param_1);
  iVar4 = (uint)bVar1 * 0xd18;
  *(undefined1 *)(iVar2 + iVar4 + 0x1136) = uVar5;
  iVar3 = net_ad_wrap_service(param_1);
  iVar2 = DebugLevel;
  *(char *)(iVar3 + iVar4 + 0x1137) = (char)uVar6;
  if (2 < iVar2) {
    printk("%s: System BW=%d, Per Packet BW=%d, control_band_idx=%d\n","MT_ATESetBW",param_2,param_3
           ,(uint)bVar1);
  }
  return 0;
}

