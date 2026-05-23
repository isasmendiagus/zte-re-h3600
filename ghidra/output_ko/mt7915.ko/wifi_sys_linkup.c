// module: mt7915.ko
// function: wifi_sys_linkup @ 0x105454
// size: 464 bytes
//

undefined4 wifi_sys_linkup(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  void *__src;
  int iVar3;
  uint unaff_r8;
  ushort *unaff_r9;
  bool bVar4;
  undefined4 local_240;
  int local_23c [8];
  undefined1 local_21c [2];
  ushort local_21a;
  undefined4 local_218;
  undefined1 local_214;
  undefined4 local_210;
  undefined1 local_20c;
  int local_150;
  undefined1 auStack_144 [4];
  undefined4 local_140;
  undefined1 local_137;
  ushort local_130;
  ushort uStack_12e;
  undefined4 local_128;
  undefined4 local_108;
  
  iVar3 = *(int *)(param_1 + 8);
  local_240 = 0;
  if (0 < DebugLevel) {
    printk("%s(), wdev idx = %d\n","wifi_sys_linkup",*(undefined1 *)(param_1 + 0xc));
  }
  iVar2 = HcIsRadioAcq(param_1);
  if ((iVar2 != 0) && (os_zero_mem(local_23c,0x214), *(int *)(param_1 + 0x990) == 0)) {
    BssInfoArgumentLink(*(undefined4 *)(param_1 + 8),param_1,auStack_144);
    bVar4 = param_2 == 0;
    *(undefined4 *)(param_1 + 0x990) = 2;
    if (bVar4) {
      unaff_r9 = &local_130;
    }
    local_140 = 2;
    if (bVar4) {
      unaff_r8 = (uint)*unaff_r9;
    }
    else {
      unaff_r9 = &local_130;
    }
    *(undefined1 *)(param_1 + 0x999) = local_137;
    if (!bVar4) {
      unaff_r8 = (uint)*(ushort *)(param_2 + 0xe0);
    }
    FUN_00104254(param_1,local_128,unaff_r8,&local_240);
    iVar2 = *(int *)(param_1 + 0x14);
    if (iVar2 == 8) {
      *unaff_r9 = (ushort)unaff_r8;
    }
    uStack_12e = (ushort)unaff_r8;
    local_108 = local_240;
    if (iVar2 != 8) {
      uVar1 = *(ushort *)(param_1 + 0x10);
      local_21a = *unaff_r9;
      local_218 = 0x10020;
      local_240 = 0x2101;
      local_210 = 0x2101;
      local_21c[0] = local_137;
      local_150 = iVar3 + 0x1c0 + (uint)uVar1 * 0x620 + 0x2f4e0;
      local_214 = 2;
      local_20c = 1;
      if (iVar2 == 1) {
        APKeyTableInit(iVar3,param_1,local_21c);
      }
      if (param_2 == 0) {
        __src = (void *)(param_1 + 0x21);
      }
      else {
        __src = (void *)(param_2 + 0xec);
      }
      os_move_mem((void *)(iVar3 + 0x1c0 + (uint)uVar1 * 0x620 + 0x2f4eb),__src,6);
      if (2 < DebugLevel) {
        printk("===> AsicStaRecUpdate called by (%s), wcid=%d, PortSecured=%d\n","wifi_sys_linkup",
               *unaff_r9,local_214);
      }
    }
    local_23c[0] = param_1;
    HW_WIFISYS_LINKUP(iVar3,local_23c);
    return 1;
  }
  return 1;
}

