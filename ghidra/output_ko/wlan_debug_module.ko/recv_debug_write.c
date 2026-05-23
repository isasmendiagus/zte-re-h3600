// module: wlan_debug_module.ko
// function: recv_debug_write @ 0x10d18
// size: 188 bytes
//

uint recv_debug_write(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uStack_18;
  
  uStack_18 = param_4;
  pbVar1 = (byte *)__kmalloc(param_3 + 1,0x80d0);
  if (pbVar1 == (byte *)0x0) {
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
    iVar2 = __copy_from_user(pbVar1,param_2,param_3);
    if (iVar2 != 0) goto LAB_00010dbc;
  }
  else if (param_3 != 0) {
    __memzero(pbVar1,param_3,uVar4);
LAB_00010dbc:
    kfree(pbVar1);
    return 0xfffffff2;
  }
  pbVar1[param_3] = 0;
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  g_wlan_debug_recv_debug = *pbVar1 - 0x30;
  kfree(pbVar1);
  return param_3;
}

