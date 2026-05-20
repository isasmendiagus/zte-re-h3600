// module: mt7915.ko
// function: HW_BEACON_UPDATE @ 0xb1ae0
// size: 104 bytes
//

void HW_BEACON_UPDATE(undefined4 param_1,int param_2,undefined4 param_3)

{
  int local_10;
  undefined1 local_c;
  
  local_c = (undefined1)param_3;
  local_10 = param_2;
  if (2 < DebugLevel) {
    printk("%s, wdev(%d), Update reason = %x\n","HW_BEACON_UPDATE",*(undefined1 *)(param_2 + 0xc),
           param_3);
  }
  FUN_000b0a74(param_1,0,0xf,8,&local_10);
  return;
}

