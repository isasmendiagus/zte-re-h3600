// module: mt7915.ko
// function: build_wsc_ie @ 0x146a54
// size: 916 bytes
//

uint build_wsc_ie(int param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  void *__dest;
  byte local_21;
  undefined1 *local_20;
  undefined2 local_1c;
  undefined1 local_1a;
  
  local_21 = *(byte *)(param_2 + 1);
  puVar2 = (undefined1 *)(uint)local_21;
  if (puVar2 == &DAT_00000004) {
    iVar4 = param_2[4];
    __dest = (void *)*param_2;
    if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
      if (*(int *)(iVar4 + 0x14) != 2) {
        return 0;
      }
      if (*(int *)(iVar4 + 0x12e4) == 0) {
        return 0;
      }
      if (*(char *)(iVar4 + 0x3cc8) == '\0') {
        return 0;
      }
      iVar3 = *(int *)(iVar4 + 0x3bc8);
      if ((iVar3 != 0) && (*(int *)(&DAT_0036da4c + param_1) == 0)) {
        if (1 < DebugLevel) {
          printk("[scan_active: %d] ConWpsApCliMode=%d conWscStatus=%d bHasWscIe=%d\n",0x95,0,iVar3,
                 0);
          return 0;
        }
        return 0;
      }
      if (1 < DebugLevel) {
        printk("[scan_active: %d] ConWpsApCliMode=%d conWscStatus=%d bHasWscIe=%d\n",0x95,
               *(undefined4 *)(&DAT_0036da4c + param_1),iVar3,1);
      }
    }
    else {
      if (*(int *)(iVar4 + 0x14) != 2) {
        return 0;
      }
      iVar3 = GetStaCfgByWdev(param_1,iVar4);
      if (iVar3 == 0) {
        printk(&_LC3,0x9d);
        dump_stack();
      }
      if (*(char *)(iVar4 + 0x1349) == '\0') {
        return 0;
      }
      if (*(int *)(iVar4 + 0x12e4) == 0) {
        return 0;
      }
      if (*(char *)(iVar4 + 0x3cc8) != '\x01') {
        return 0;
      }
    }
    local_20 = (undefined1 *)0x0;
    local_21 = 0;
    os_alloc_mem(0,&local_20,0x200);
    if (local_20 == (undefined1 *)0x0) {
      if (1 < DebugLevel) {
        printk("%s:: WscBuf Allocate failed!\n","build_wsc_probe_req_ie");
        return 0;
      }
      return 0;
    }
    __memzero(local_20,0x200);
    WscBuildProbeReqIE(param_1,iVar4,local_20,&local_21);
LAB_00146b08:
    puVar2 = local_20;
    uVar1 = (uint)local_21;
    memmove(__dest,local_20,uVar1);
    os_free_mem(puVar2);
    return uVar1;
  }
  if (puVar2 == &DAT_00000005) {
    iVar4 = param_2[4];
    param_2 = (undefined4 *)*param_2;
    if (*(int *)(iVar4 + 0x14) == 1) {
      iVar3 = *(int *)(iVar4 + 0x12e4);
      if (iVar3 == 0) {
        return 0;
      }
      if (*(char *)(iVar4 + 0x5c0) == '\x01') {
        uVar1 = 0;
      }
      else {
        uVar1 = 0;
        if ((*(uint *)(iVar4 + 0x174) & 0xe) != 0) {
          uVar1 = 7;
          local_20 = (undefined1 *)0x500005dd;
          local_1c = 0x5f2;
          local_1a = 0;
          *param_2 = 0x500005dd;
          *(undefined1 *)((int)param_2 + 6) = 0;
          *(undefined2 *)(param_2 + 1) = 0x5f2;
          iVar3 = *(int *)(iVar4 + 0x12e4);
        }
      }
      if (0 < iVar3) {
        if (*(ushort *)(iVar4 + 0x10e2) != 0) {
          memmove((void *)((int)param_2 + uVar1),(void *)(iVar4 + 0x10e4),
                  (uint)*(ushort *)(iVar4 + 0x10e2));
          return uVar1 + *(ushort *)(iVar4 + 0x10e2);
        }
        return uVar1;
      }
      return uVar1;
    }
    if (*(int *)(iVar4 + 0x14) == 4) {
      if (*(ushort *)(iVar4 + 0x10e2) == 0) {
        return 0;
      }
      memmove(param_2,(void *)(iVar4 + 0x10e4),(uint)*(ushort *)(iVar4 + 0x10e2));
      return (uint)*(ushort *)(iVar4 + 0x10e2);
    }
  }
  else if (puVar2 == (undefined1 *)0x0) {
    iVar4 = param_2[4];
    __dest = (void *)*param_2;
    if (*(char *)(iVar4 + 0x1348) == '\0') {
      return 0;
    }
    if (*(int *)(iVar4 + 0x12e4) == 0) {
      return 0;
    }
    if (*(char *)(iVar4 + 0x3cc8) == '\0') {
      return 0;
    }
    local_20 = puVar2;
    os_alloc_mem(param_1,&local_20,0x200);
    if (local_20 == (undefined1 *)0x0) {
      if (1 < DebugLevel) {
        printk("%s:: WscBuf Allocate failed!\n","build_wsc_assoc_req_ie");
        return 0;
      }
      return 0;
    }
    __memzero(local_20,0x200);
    WscBuildAssocReqIE(iVar4 + 0x12e4,local_20,&local_21);
    goto LAB_00146b08;
  }
  return 0;
}

