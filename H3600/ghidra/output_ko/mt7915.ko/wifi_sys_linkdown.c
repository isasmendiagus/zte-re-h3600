// module: mt7915.ko
// function: wifi_sys_linkdown @ 0x105628
// size: 364 bytes
//

undefined4 wifi_sys_linkdown(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_230;
  int local_22c [10];
  undefined1 local_204;
  undefined2 local_202;
  undefined4 local_200;
  undefined1 local_1fc;
  undefined4 local_1f8;
  int local_138;
  undefined1 auStack_12c [13];
  undefined1 local_11f;
  undefined2 local_118;
  undefined4 local_110;
  undefined4 local_f0;
  undefined1 local_26;
  
  iVar2 = *(int *)(param_1 + 8);
  local_230 = 0;
  if (0 < DebugLevel) {
    printk("%s(), wdev idx = %d\n","wifi_sys_linkdown",*(undefined1 *)(param_1 + 0xc));
  }
  os_zero_mem(local_22c + 2,0x214);
  if ((*(int *)(param_1 + 0x994) != 0) && (*(int *)(param_1 + 0x990) != 0)) {
    *(undefined4 *)(param_1 + 0x990) = 1;
    os_move_mem(auStack_12c,(void *)(param_1 + 0x98c),0x114);
    FUN_00104254(param_1,local_110,local_118,&local_230);
    local_f0 = local_230;
    local_26 = HcGetBandByWdev(param_1);
    if ((*(int *)(param_1 + 0x14) != 8) &&
       (iVar1 = (uint)*(ushort *)(param_1 + 0x10) * 0x620,
       *(char *)(iVar2 + iVar1 + 0x2fa88) != '\0')) {
      local_1f8 = 1;
      local_138 = iVar2 + iVar1 + 0x2f6a0;
      local_202 = local_118;
      local_200 = 0x10020;
      local_204 = local_11f;
      local_1fc = 0;
    }
    local_22c[1] = 0;
    local_22c[0] = param_1;
    local_22c[2] = param_1;
    mt_notify_call_chain(*(int *)(param_1 + 8) + 0xa7bef8,5,local_22c);
    HW_WIFISYS_LINKDOWN(iVar2,local_22c + 2);
    return 1;
  }
  return 1;
}

