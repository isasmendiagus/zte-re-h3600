// module: mt7915.ko
// function: asic_wrap_protinfo_in_bssinfo @ 0x195234
// size: 224 bytes
//

void asic_wrap_protinfo_in_bssinfo(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_134 [13];
  undefined1 local_127;
  undefined4 local_126;
  undefined2 local_122;
  undefined4 local_f8;
  int local_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int local_34;
  
  iVar2 = *param_2;
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s: prepare to deliver setting to firmware\n","asic_wrap_protinfo_in_bssinfo");
  }
  os_zero_mem(auStack_134,0x114);
  local_44 = *param_2;
  iStack_40 = param_2[1];
  iStack_3c = param_2[2];
  iStack_38 = param_2[3];
  local_126 = *(undefined4 *)(iVar2 + 0x99a);
  local_f8 = 0x4000;
  local_34 = param_2[4];
  local_127 = *(undefined1 *)(iVar2 + 0x999);
  local_122 = *(undefined2 *)(iVar2 + 0x99e);
  if (*(code **)(iVar1 + 0x28) == (code *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: there is no lower layer implementation.\n","asic_wrap_protinfo_in_bssinfo");
    }
  }
  else {
    (**(code **)(iVar1 + 0x28))(param_1,auStack_134);
  }
  return;
}

