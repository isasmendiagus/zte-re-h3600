// module: mt7915.ko
// function: twtPlannerDrvAgrtAdd @ 0x169b70
// size: 196 bytes
//

undefined4
twtPlannerDrvAgrtAdd
          (int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined1 *param_5)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev=NULL, please check\n","twtPlannerDrvAgrtAdd");
    }
  }
  else {
    uVar1 = 0;
    do {
      uVar2 = uVar1 + 1;
      if ((&DAT_00581100)[param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x2137b0 + uVar1 * 0x20] ==
          '\0') {
        twtPlannerDrvAgrtInsert
                  (&DAT_00581100 + param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x2137b0,
                   *(undefined1 *)(param_2 + 0x999),param_3,param_4,uVar1 & 0xff);
        *param_5 = (char)uVar1;
        return 0;
      }
      uVar1 = uVar2;
    } while (uVar2 != 0x10);
  }
  return 1;
}

