// module: mt7915.ko
// function: SetWPAPSKKey @ 0x119d6c
// size: 220 bytes
//

undefined4
SetWPAPSKKey(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 *param_6)

{
  undefined4 uVar1;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  if (param_3 - 8U < 0x39) {
    __memzero(param_6,0x20);
    if (param_3 != 0x40) {
      WPAPasswordHash(param_2,param_4,param_5,&local_40);
      *param_6 = local_40;
      param_6[1] = uStack_3c;
      param_6[2] = uStack_38;
      param_6[3] = uStack_34;
      param_6[4] = local_30;
      param_6[5] = uStack_2c;
      param_6[6] = uStack_28;
      param_6[7] = uStack_24;
      return 1;
    }
    AtoH(param_2,param_6,0x20);
    uVar1 = 1;
  }
  else if (DebugLevel < 0) {
    uVar1 = 0;
  }
  else {
    printk("WPAPSK Key length(%d) error, required 8 ~ 64 characters!(keyStr=%s)\n",param_3,param_2);
    uVar1 = 0;
  }
  return uVar1;
}

