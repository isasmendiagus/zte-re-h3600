// module: mt7915.ko
// function: show_wtbl_proc @ 0xe0af0
// size: 256 bytes
//

undefined4 show_wtbl_proc(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  asic_dump_wtbl_base_info();
  if (param_2 == (char *)0x0) {
    return 1;
  }
  if (DebugLevel < 1) {
    if (*param_2 != '\0') {
LAB_000e0b64:
      uVar2 = os_str_toul(param_2,0,10);
      uVar1 = uVar2;
      uVar3 = uVar2;
      if (DebugLevel < 1) goto LAB_000e0b44;
      goto LAB_000e0b90;
    }
    uVar3 = *(ushort *)("Get_System_CapNode_Info" + param_1 + 8) - 1;
    uVar1 = 0;
  }
  else {
    printk("%s(): arg=%s\n","show_wtbl_proc",param_2,DebugLevel,param_4);
    if (*param_2 != '\0') goto LAB_000e0b64;
    uVar3 = *(ushort *)("Get_System_CapNode_Info" + param_1 + 8) - 1;
    uVar1 = 0;
    if (DebugLevel < 1) goto LAB_000e0b3c;
    uVar2 = 0xffffffff;
    uVar3 = *(ushort *)("Get_System_CapNode_Info" + param_1 + 8) - 1;
LAB_000e0b90:
    printk("Dump WTBL entries info, start=%d, end=%d, idx=%d\n",uVar1,uVar3,uVar2,param_4);
  }
LAB_000e0b3c:
  uVar2 = uVar1;
  if ((int)uVar3 < (int)uVar1) {
    return 1;
  }
LAB_000e0b44:
  do {
    uVar1 = uVar2 & 0xffff;
    uVar2 = uVar2 + 1;
    asic_dump_wtbl_info(param_1,uVar1);
  } while ((int)uVar2 <= (int)uVar3);
  return 1;
}

