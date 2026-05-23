// module: mt7915.ko
// function: WpaSendEapolStart @ 0x577ac
// size: 232 bytes
//

void WpaSendEapolStart(undefined4 param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  undefined1 local_32;
  undefined1 local_31;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  
  uVar1 = MacTableLookup2();
  if (2 < DebugLevel) {
    printk("-----> WpaSendEapolStart\n");
  }
  __memzero(&local_2e,0xe);
  local_28 = *(undefined4 *)(param_3 + 0x1b);
  local_2a = *(undefined2 *)(param_2 + 1);
  local_2e = *param_2;
  local_24 = *(undefined2 *)(param_3 + 0x1f);
  local_22 = EAPOL;
  __memzero(&local_32,4);
  local_32 = 1;
  local_31 = 1;
  local_30 = 0;
  RTMPToWirelessSta(param_1,uVar1,&local_2e,0xe,&local_32,4,1);
  if (2 < DebugLevel) {
    printk("<----- WpaSendEapolStart\n");
  }
  return;
}

