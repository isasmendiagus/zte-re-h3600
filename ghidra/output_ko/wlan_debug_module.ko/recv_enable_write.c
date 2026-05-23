// module: wlan_debug_module.ko
// function: recv_enable_write @ 0x10e94
// size: 240 bytes
//

uint recv_enable_write(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  undefined4 uStack_18;
  
  uStack_18 = param_4;
  pcVar2 = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (pcVar2 == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar6 = *(uint *)(((uint)&uStack_18 & 0xffffe000) + 8);
  uVar4 = param_2 + param_3;
  uVar5 = uVar4;
  if (!CARRY4(param_2,param_3)) {
    uVar5 = uVar4 - (uVar6 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar4 <= uVar6) {
    uVar6 = 0;
  }
  if (uVar6 == 0) {
    iVar3 = __copy_from_user(pcVar2,param_2,param_3);
    if (iVar3 != 0) goto LAB_00010f5c;
  }
  else if (param_3 != 0) {
    __memzero(pcVar2,param_3,uVar5);
LAB_00010f5c:
    kfree(pcVar2);
    return 0xfffffff2;
  }
  pcVar2[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  cVar1 = *pcVar2;
  pcVar7 = pcVar2;
  while (cVar1 == ' ') {
    pcVar7 = pcVar7 + 1;
    cVar1 = *pcVar7;
  }
  uVar5 = (uint)(byte)(cVar1 - 0x30);
  if (1 < (byte)(cVar1 - 0x30)) {
    printk("the input parameter out of range(0:disable, 1:enable)\n");
    uVar5 = g_wlan_debug_recv_enable;
  }
  g_wlan_debug_recv_enable = uVar5;
  kfree(pcVar2);
  return param_3;
}

