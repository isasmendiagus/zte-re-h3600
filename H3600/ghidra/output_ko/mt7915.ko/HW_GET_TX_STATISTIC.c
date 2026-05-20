// module: mt7915.ko
// function: HW_GET_TX_STATISTIC @ 0xb1d8c
// size: 136 bytes
//

void HW_GET_TX_STATISTIC(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_48;
  undefined2 local_44;
  undefined1 auStack_40 [44];
  
  if (3 < DebugLevel) {
    printk("%s(): Field = 0x%x, Wcid = %d\n","HW_GET_TX_STATISTIC",param_2,param_3);
  }
  os_zero_mem(auStack_40,0x28);
  os_zero_mem(&local_48,8);
  local_44 = (undefined2)param_3;
  local_48 = param_2;
  FUN_000b0a74(param_1,5,0x31,8,&local_48);
  return;
}

