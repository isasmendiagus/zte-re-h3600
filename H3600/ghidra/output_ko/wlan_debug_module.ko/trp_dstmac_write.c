// module: wlan_debug_module.ko
// function: trp_dstmac_write @ 0x10400
// size: 336 bytes
//

uint trp_dstmac_write(int param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  char *__s;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint local_30;
  uint uStack_2c;
  undefined2 *local_28;
  int local_24;
  undefined4 local_1e;
  undefined2 local_1a;
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar7 = *(uint *)(((uint)&local_30 & 0xffffe000) + 8);
  uVar5 = param_2 + param_3;
  uVar6 = uVar5;
  if (!CARRY4(param_2,param_3)) {
    uVar6 = uVar5 - (uVar7 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar5 <= uVar7) {
    uVar7 = 0;
  }
  if (uVar7 == 0) {
    iVar4 = __copy_from_user(__s,param_2,param_3);
    if (iVar4 != 0) goto LAB_00010538;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar6);
LAB_00010538:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  local_30 = (int)&local_1e + 2;
  uStack_2c = (int)&local_1e + 3;
  local_28 = &local_1a;
  local_24 = (int)&local_1a + 1;
  local_1e = 0;
  local_1a = 0;
  iVar4 = sscanf(__s,"%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",&local_1e,(int)&local_1e + 1);
  if (iVar4 == 6) {
    g_wlan_debug_trp_dstmac._0_4_ = local_1e;
    uVar6 = (uint)g_wlan_debug_trp_dstmac;
    g_wlan_debug_trp_dstmac._4_2_ = local_1a;
    uVar3 = g_wlan_debug_trp_dstmac._4_2_;
    g_wlan_debug_trp_dstmac._1_1_ = (undefined1)(local_1e >> 8);
    uVar1 = g_wlan_debug_trp_dstmac._1_1_;
    g_wlan_debug_trp_dstmac._2_1_ = (undefined1)(local_1e >> 0x10);
    uVar2 = g_wlan_debug_trp_dstmac._2_1_;
    local_30 = local_1e >> 0x18;
    g_wlan_debug_trp_dstmac._4_1_ = (byte)local_1a;
    uStack_2c = (uint)g_wlan_debug_trp_dstmac._4_1_;
    g_wlan_debug_trp_dstmac._5_1_ = (byte)((ushort)local_1a >> 8);
    local_28 = (undefined2 *)(uint)g_wlan_debug_trp_dstmac._5_1_;
    g_wlan_debug_trp_dstmac._0_4_ = uVar6;
    g_wlan_debug_trp_dstmac._4_2_ = uVar3;
    printk("set dstmac = [%02X:%02X:%02X:%02X:%02X:%02X]\n",local_1e & 0xff,uVar1,uVar2);
  }
  else {
    printk("Invalid MAC Address [%s]\n",__s);
  }
  kfree(__s);
  return param_3;
}

