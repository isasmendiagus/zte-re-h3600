// module: mt7915.ko
// function: HW_SET_PROTECT @ 0xb1bb4
// size: 156 bytes
//

void HW_SET_PROTECT(undefined4 param_1,int param_2,int param_3,undefined1 param_4,undefined4 param_5
                   )

{
  undefined2 uVar1;
  
  *(int *)(param_2 + 0x403c) = param_2;
  *(int *)(param_2 + 0x4040) = param_3;
  if (param_3 == 1) {
    *(int *)(param_2 + 0x4044) = param_2;
    *(undefined1 *)(param_2 + 0x4048) = param_4;
    *(undefined4 *)(param_2 + 0x404c) = param_5;
  }
  else if (param_3 == 0) {
    *(undefined4 *)(param_2 + 0x4044) = *(undefined4 *)(param_2 + 0x8dc);
  }
  else {
    if (param_3 != 2) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s, incorrect prot_service_type:%d\n","HW_SET_PROTECT");
      return;
    }
    uVar1 = wlan_operate_get_he_txop_dur_rts_thld(param_2);
    *(undefined2 *)(param_2 + 0x4044) = uVar1;
  }
  FUN_000b0a74(param_1,7,0x36,0x14);
  return;
}

