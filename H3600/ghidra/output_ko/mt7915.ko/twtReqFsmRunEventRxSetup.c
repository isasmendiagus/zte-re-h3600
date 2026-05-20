// module: mt7915.ko
// function: twtReqFsmRunEventRxSetup @ 0x1693a8
// size: 144 bytes
//

void twtReqFsmRunEventRxSetup(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
  if (&DAT_0036db58 + param_1 + iVar1 == (undefined *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: apcli_entry=NULL, please check\n","twtReqFsmRunEventRxSetup");
      return;
    }
  }
  else if (*(int *)(&DAT_00580f3c + param_1 + iVar1) == 2) {
    twtReqFsmSteps();
  }
  return;
}

