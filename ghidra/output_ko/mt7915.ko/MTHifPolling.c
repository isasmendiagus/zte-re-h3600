// module: mt7915.ko
// function: MTHifPolling @ 0x19a0cc
// size: 164 bytes
//

void MTHifPolling(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_20;
  int local_1c;
  
  iVar1 = 1;
  local_20 = 0;
  local_1c = 0;
  do {
    AsicExtWifiHifCtrl(param_1,param_2,1,&local_20);
    if (local_1c == 0) {
      return;
    }
    if (iVar1 == 2) {
      if (-1 < DebugLevel) {
        printk("%s(): Failed to poll RX path empry.\n","MTHifPolling");
      }
      printk(&_LC1,0x57);
      dump_stack();
    }
    else if (iVar1 == 10) {
      return;
    }
    iVar1 = iVar1 + 1;
  } while( true );
}

