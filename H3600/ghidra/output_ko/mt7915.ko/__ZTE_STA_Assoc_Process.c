// module: mt7915.ko
// function: __ZTE_STA_Assoc_Process @ 0x15a58c
// size: 828 bytes
//

void __ZTE_STA_Assoc_Process
               (int param_1,int param_2,undefined4 *param_3,uint param_4,undefined1 param_5,
               int param_6,int param_7,undefined4 param_8,undefined4 param_9)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar5;
  int iVar6;
  int local_88;
  undefined1 local_7c;
  int local_74;
  undefined1 auStack_70 [3];
  char local_6d;
  undefined1 *puVar4;
  
  local_74 = 0;
  if ((param_1 == 0) || (param_7 == 0 && param_3 == (undefined4 *)0x0)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s:__ZTE_STA_Assoc_Process parameter error null ptr\n","__ZTE_STA_Assoc_Process");
    return;
  }
  if (param_7 == 0) {
    local_7c = 0;
  }
  else {
    uVar2 = (uint)*(byte *)(param_7 + 0xe5);
    if (param_4 != 0) {
      uVar2 = param_4;
    }
    local_7c = (undefined1)uVar2;
  }
  if (*(char *)(param_1 + 0xa7dfb8) == '\0') {
    puVar4 = (undefined1 *)(param_1 + 0xa7dfb8);
    do {
      puVar3 = puVar4 + 0x48;
      *puVar4 = 0;
      puVar4 = puVar3;
    } while (puVar3 != (undefined1 *)(param_1 + 0xa86c58));
LAB_0015a624:
    local_88 = 0;
  }
  else {
    local_88 = *(int *)(param_1 + 0xa86c58) + 1;
    if (499 < local_88) goto LAB_0015a624;
  }
  uVar1 = jiffies;
  iVar5 = local_88 * 0x48;
  iVar6 = param_1 + iVar5;
  *(undefined1 *)(iVar6 + 0xa7dfb8) = 1;
  *(int *)(iVar6 + 0xa7dfc8) = param_2;
  *(undefined4 *)(iVar6 + 0xa7dfd0) = param_9;
  *(undefined1 *)(iVar6 + 0xa7dfbb) = param_5;
  *(undefined1 *)(iVar6 + 0xa7dfba) = (undefined1)param_6;
  uVar1 = jiffies_to_msecs(uVar1);
  *(undefined4 *)(iVar6 + 0xa7dfd4) = uVar1;
  snprintf((char *)(param_1 + iVar5 + 0xa7dfd8),0x28,"%s",param_8);
  if (param_7 == 0) {
    *(char *)(iVar6 + 0xa7dfb9) = (char)param_4;
    if (param_3 == (undefined4 *)0x0) goto LAB_0015a788;
    iVar5 = param_1 + iVar5 + 0xa7dfb8;
    *(undefined4 *)(iVar5 + 4) = *param_3;
    *(undefined2 *)(iVar5 + 8) = *(undefined2 *)(param_3 + 1);
  }
  else {
    uVar1 = RTMPAvgRssi(param_1,param_7 + 0x108);
    *(undefined4 *)(iVar6 + 0xa7dfc4) = uVar1;
    ZTE_GetAssocRate(param_7,&local_74);
    iVar5 = param_1 + iVar5 + 0xa7dfb8;
    *(int *)(iVar6 + 0xa7dfcc) = local_74 * 1000;
    *(undefined1 *)(iVar6 + 0xa7dfb9) = local_7c;
    *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(param_7 + 0xec);
    *(undefined2 *)(iVar5 + 8) = *(undefined2 *)(param_7 + 0xf0);
  }
  if (param_2 == 0x13 && param_3 != (undefined4 *)0x0) {
    iVar5 = param_1 + local_88 * 0x48;
    *(undefined4 *)(iVar5 + 0xa7dfbc) = *param_3;
    *(undefined2 *)(iVar5 + 0xa7dfc0) = *(undefined2 *)(param_3 + 1);
  }
LAB_0015a788:
  *(int *)(param_1 + 0xa86c58) = local_88;
  __memzero(auStack_70,0x48);
  memcpy(auStack_70,(void *)(param_1 + local_88 * 0x48 + 0xa7dfb8),0x48);
  if (param_6 == 0 && (local_6d == -0x38 || local_6d == '\0')) {
    return;
  }
  Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa20a,auStack_70,0x48,0,0);
  return;
}

