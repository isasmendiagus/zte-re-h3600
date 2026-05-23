// module: wlan_debug_module.ko
// function: pktcnt_dbgredirect_write @ 0x12728
// size: 252 bytes
//

uint pktcnt_dbgredirect_write(int param_1,uint param_2,uint param_3)

{
  char *__s;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_28 [6];
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar4 = *(uint *)(((uint)auStack_28 & 0xffffe000) + 8);
  uVar2 = param_2 + param_3;
  uVar3 = uVar2;
  if (!CARRY4(param_2,param_3)) {
    uVar3 = uVar2 - (uVar4 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar2 <= uVar4) {
    uVar4 = 0;
  }
  if (uVar4 == 0) {
    iVar1 = __copy_from_user(__s,param_2,param_3);
    if (iVar1 != 0) goto LAB_0001280c;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar3);
LAB_0001280c:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  local_22 = 0;
  local_20 = 0;
  local_1e = 0;
  local_1c = 0;
  local_1a = 0;
  sscanf(__s,"%9s",&local_22);
  _pktcnt_Extract_parameters_constprop_2(&local_22,&g_pktcnt_dbgredirect);
  printk("set dbgredirect = [0x%x]\n",g_pktcnt_dbgredirect);
  kfree(__s);
  return param_3;
}

