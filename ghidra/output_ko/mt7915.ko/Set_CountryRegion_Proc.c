// module: mt7915.ko
// function: Set_CountryRegion_Proc @ 0xd809c
// size: 284 bytes
//

undefined4
Set_CountryRegion_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = *(int *)(*param_1 + 0x38);
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if ((iVar3 - 0x100U & 0xfffffeff) == 0) {
    iVar3 = (uVar4 & 0xff) * 0x160d + 0xadc92;
  }
  else {
    if ((iVar3 != 0x400) && (iVar3 != 0x800)) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("[Set_CountryRegion_Proc]: pObj->ioctl_if_type = %d!!\n",iVar3,iVar3,DebugLevel,param_4
            );
      return 0;
    }
    iVar3 = (uVar4 & 0xff) * 0x84dec + 0xdb6d6;
  }
  iVar1 = RT_CfgSetCountryRegion(param_1,param_2,2);
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = HcGetBandByWdev(param_1 + iVar3);
  uVar2 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar2);
  hc_set_ChCtrlChListStat(uVar2,0);
  BuildChannelList(param_1,param_1 + iVar3);
  if (2 < DebugLevel) {
    printk("Set_CountryRegion_Proc::(CountryRegion=%d)\n",(char)param_1[0x1e5311]);
    return 1;
  }
  return 1;
}

