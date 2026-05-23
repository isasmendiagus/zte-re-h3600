// module: mt7915.ko
// function: MAP_Init @ 0x1603ac
// size: 148 bytes
//

void MAP_Init(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  if (param_3 == 1) {
    uVar1 = 0x20;
  }
  else if (param_3 == 2) {
    uVar1 = 0x80;
  }
  else if (DebugLevel < 4) {
    uVar1 = 0;
  }
  else {
    printk("%s():AP Role not set (Fixed me)\n","MAP_CheckDevRole");
    uVar1 = 0;
  }
  *(undefined1 *)(param_2 + 0x3f5d) = uVar1;
  *(undefined1 *)(param_2 + 0x3f5a) = 1;
  *(undefined1 *)(param_2 + 0x3f5b) = 0;
  (&DAT_0036da90)[param_1] = 0;
  (&DAT_0036da91)[param_1] = 0;
  (&DAT_0036da92)[param_1] = 0;
  __memzero(param_2 + 0x3f5e,0x80,0,param_4);
  return;
}

