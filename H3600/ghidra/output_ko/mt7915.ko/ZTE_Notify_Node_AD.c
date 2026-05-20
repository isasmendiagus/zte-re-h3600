// module: mt7915.ko
// function: ZTE_Notify_Node_AD @ 0x157c30
// size: 816 bytes
//

void ZTE_Notify_Node_AD(int param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_15c;
  undefined4 *local_158;
  uint local_154;
  undefined4 local_150;
  undefined2 local_14c;
  undefined1 local_14a;
  int local_148;
  int local_d8;
  undefined1 local_cc;
  undefined1 local_cb;
  
  memset(&local_154,0,0x134);
  local_15c = 0;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("ZTE_Notify_Node_AD parameter error null ptr\n");
    return;
  }
  puVar3 = (undefined4 *)(param_2 + 0xec);
  local_150 = *puVar3;
  local_154 = (uint)*(byte *)(param_2 + 0xe5);
  local_14c = *(undefined2 *)(param_2 + 0xf0);
  if (2 < DebugLevel) {
    printk("ZTE_Notify_Node_AD emEvent = %d idx=%d MAC[%02x:%02x:%02x:%02x:%02x:%02x]\n",param_1,
           local_154,*(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
           *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
           *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
  }
  ZTE_GetAssocRate(param_2,&local_15c);
  if (*(byte *)(param_2 + 0xbf) < 0xa0) {
LAB_00157ca8:
    local_148 = local_15c * 1000;
    *(int *)(param_2 + 0x14) = local_148;
  }
  else {
    cVar1 = *(char *)(*(int *)(param_2 + 8) + 0x405c);
    if (cVar1 == '\x02') {
      local_148 = local_15c * 0x3b0;
      *(int *)(param_2 + 0x14) = local_148;
    }
    else {
      if (cVar1 != '\x03') goto LAB_00157ca8;
      local_148 = local_15c * 0x352;
      *(int *)(param_2 + 0x14) = local_148;
    }
  }
  local_14a = (undefined1)param_1;
  if (param_1 == 1) {
    if (*(byte *)(param_2 + 0xbd) < 0x80) {
      if ((*(byte *)(param_2 + 0xbd) & 0xc0) == 0x40) {
        local_d8 = (((uint)*(byte *)(param_2 + 0xbc) << 0x1a) >> 0x1d) + 1;
      }
      else {
        local_d8 = 1;
      }
    }
    else {
      local_d8 = (((uint)*(byte *)(param_2 + 0xbc) << 0x1a) >> 0x1e) + 1;
    }
    local_cc = *(undefined1 *)(param_2 + 0xd22);
    local_cb = (*(byte *)(param_2 + 0x11ec) & 0x30) != 0;
    Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa420,&local_154,0x134,0,0);
    os_alloc_mem(0,&local_158,0x418);
    if (local_158 != (undefined4 *)0x0) {
      __memzero(local_158,0x418);
      puVar2 = local_158;
      *(undefined1 *)(local_158 + 3) = 1;
      *(undefined4 *)((int)local_158 + 6) = *(undefined4 *)(param_2 + 0xae0);
      *(undefined2 *)((int)local_158 + 10) = *(undefined2 *)(param_2 + 0xae4);
      *local_158 = *puVar3;
      *(undefined2 *)(local_158 + 1) = *(undefined2 *)(param_2 + 0xf0);
      memcpy(local_158 + 5,(void *)(param_2 + 0x11f4),*(size_t *)(param_2 + 0x12f4));
      puVar2[4] = *(undefined4 *)(param_2 + 0x12f4);
      goto LAB_00157d8c;
    }
  }
  else {
    if (param_1 != 0) {
      return;
    }
    Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa421,&local_154,0x134,0,0);
    os_alloc_mem(0,&local_158,0x418);
    if (local_158 != (undefined4 *)0x0) {
      __memzero(local_158,0x418);
      *(undefined1 *)(local_158 + 3) = 0;
      *(undefined4 *)((int)local_158 + 6) = *(undefined4 *)(param_2 + 0xae0);
      *(undefined2 *)((int)local_158 + 10) = *(undefined2 *)(param_2 + 0xae4);
      *local_158 = *puVar3;
      *(undefined2 *)(local_158 + 1) = *(undefined2 *)(param_2 + 0xf0);
      puVar2 = local_158;
LAB_00157d8c:
      Kernel_ASEND("multiapd.map.slave",0xa2b8,puVar2,0x418,0,0);
      os_free_mem(local_158);
      return;
    }
  }
  if (-1 < DebugLevel) {
    printk("ZTE_Notify_Node_AD alloc memory failed sizeof=%d",0x418);
  }
  return;
}

