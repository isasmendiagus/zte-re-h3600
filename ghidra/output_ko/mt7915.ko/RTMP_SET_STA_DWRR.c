// module: mt7915.ko
// function: RTMP_SET_STA_DWRR @ 0xb1478
// size: 292 bytes
//

void RTMP_SET_STA_DWRR(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined1 extraout_r1;
  undefined2 local_44;
  undefined1 local_42;
  undefined1 local_41;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined2 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  os_zero_mem(&local_40,0x28);
  os_zero_mem(&local_44,4);
  uVar1 = *(undefined2 *)(param_2 + 0xe0);
  local_44 = uVar1;
  if (*(char *)(param_1 + 0xa7a2e8) == '\0') {
    __aeabi_idivmod(*(undefined1 *)(*(int *)(param_2 + 8) + 0xe),*(undefined2 *)(param_1 + 0xa7bec8)
                   );
    local_42 = extraout_r1;
  }
  else {
    local_42 = *(undefined1 *)(param_1 + (uint)*(byte *)(param_2 + 0xe4) + 0xa7bea8);
  }
  if (-1 < DebugLevel) {
    printk("%s::GroupID:%u,func_tb_idx:%u,wcid:%u\n","RTMP_SET_STA_DWRR",local_42,
           *(undefined1 *)(param_2 + 0xe4),uVar1);
  }
  local_41 = HcGetWmmIdx(param_1,*(undefined4 *)(param_2 + 8));
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_40 = 0;
  local_38 = local_38 & 0xffffff00;
  local_3c = 0x21;
  local_34 = 0;
  local_28 = 0;
  local_2c = 4;
  local_30 = &local_44;
  HwCtrlEnqueueCmd(param_1,0,0x21,local_38,0,&local_44,4,0,0,0,0);
  return;
}

