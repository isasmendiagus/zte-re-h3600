// module: mt7915.ko
// function: twtReqFsmRunEventRxTeardown @ 0x16943c
// size: 144 bytes
//

void twtReqFsmRunEventRxTeardown(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
  if (&DAT_0036db58 + param_1 + iVar1 == (undefined *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: apcli_entry=NULL, please check\n","twtReqFsmRunEventRxTeardown");
      return;
    }
  }
  else if (*(int *)(&DAT_00580f3c + param_1 + iVar1) == 0) {
    twtReqFsmSteps(param_1,param_2,7,param_3,0);
  }
  return;
}

