// module: wlan_debug_module.ko
// function: pktcnt_pktlist_write @ 0x11518
// size: 188 bytes
//

uint pktcnt_pktlist_write(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uStack_18;
  
  uStack_18 = param_4;
  iVar1 = __kmalloc(param_3 + 1,0x80d0);
  if (iVar1 == 0) {
    return 0xfffffff4;
  }
  uVar5 = *(uint *)(((uint)&uStack_18 & 0xffffe000) + 8);
  uVar3 = param_2 + param_3;
  uVar4 = uVar3;
  if (!CARRY4(param_2,param_3)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar2 = __copy_from_user(iVar1,param_2,param_3);
    if (iVar2 != 0) goto LAB_000115bc;
  }
  else if (param_3 != 0) {
    __memzero(iVar1,param_3,uVar4);
LAB_000115bc:
    kfree(iVar1);
    return 0xfffffff2;
  }
  *(undefined1 *)(iVar1 + param_3) = 0;
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  __memzero(&g_pktlist,&DAT_0004e3e0);
  kfree(iVar1);
  return param_3;
}

