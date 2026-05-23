// module: mt7915.ko
// function: net_ad_set_tmr @ 0x25e1a8
// size: 224 bytes
//

undefined4 net_ad_set_tmr(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char acStack_20 [8];
  char acStack_18 [12];
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    iVar3 = param_2[1];
    if (iVar3 == 100) {
      param_2[1] = 0;
    }
    else if (iVar3 == 0x96) {
      param_2[1] = 1;
    }
    else {
      if (iVar3 != 200) {
        printk("%s: wrong version %d!!\n","net_ad_set_tmr");
        return 0x60a;
      }
      param_2[1] = 2;
    }
    snprintf(acStack_20,8,"%d",*param_2);
    sprintf(acStack_18,"%d",param_2[1]);
    iVar3 = TmrUpdateParameter(iVar1,*(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3));
    if ((iVar3 == 0) && (iVar3 = setTmrVerProc(iVar1,acStack_18), iVar3 == 0)) {
      uVar2 = setTmrEnableProc(iVar1,acStack_20);
    }
    else {
      uVar2 = 0x600;
    }
  }
  return uVar2;
}

