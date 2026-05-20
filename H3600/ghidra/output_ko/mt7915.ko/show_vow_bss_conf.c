// module: mt7915.ko
// function: show_vow_bss_conf @ 0x472e8
// size: 740 bytes
//

undefined4 show_vow_bss_conf(int param_1,char *param_2)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  uint local_1c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar3 = sscanf(param_2,"%u",&local_1c);
  if ((iVar3 == 0) || (0xf < local_1c)) {
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s: ************** Group%d **********\n","show_vow_bss_conf");
  if (DebugLevel < 0) {
LAB_00047470:
    if (DebugLevel < 0) goto LAB_00047588;
    iVar3 = local_1c * 0x1c + param_1;
    printk("Airtime ratio --> %u/%u %%\n",*(undefined1 *)(iVar3 + 0xa7982d),
           *(undefined1 *)(iVar3 + 0xa7982c));
    if (DebugLevel < 0) {
      return 1;
    }
    iVar3 = local_1c * 0x1c + param_1;
    uVar1 = *(ushort *)(iVar3 + 0xa79838);
    uVar2 = *(ushort *)(iVar3 + 0xa7983a);
    printk("Rate token --> %u Byte(%u)/%u Byte(%u)\n",uVar2 >> 3,uVar2,uVar1 >> 3,uVar1);
  }
  else {
    pcVar6 = "Disable";
    pcVar5 = "Enable";
    pcVar4 = pcVar6;
    if (((uint)*(ushort *)(param_1 + 0xa7a2f0) & 1 << (local_1c & 0xff)) != 0) {
      pcVar4 = pcVar5;
    }
    printk("BW control --> %s(%d)\n",pcVar4);
    if (DebugLevel < 0) {
      return 1;
    }
    pcVar4 = pcVar6;
    if (*(char *)(local_1c * 0x1c + param_1 + 0xa79842) != '\0') {
      pcVar4 = pcVar5;
    }
    printk("Airtime control --> %s(%d)\n",pcVar4);
    if (-1 < DebugLevel) {
      if (*(char *)(local_1c * 0x1c + param_1 + 0xa79841) != '\0') {
        pcVar6 = pcVar5;
      }
      printk("Rate control --> %s(%d)\n",pcVar6);
      if (DebugLevel < 0) {
        return 1;
      }
      iVar3 = local_1c * 0x1c + param_1;
      printk("Rate --> %u/%uMbps\n",*(undefined2 *)(iVar3 + 0xa7982a),
             *(undefined2 *)(iVar3 + 0xa79828));
      goto LAB_00047470;
    }
  }
  if (DebugLevel < 0) {
    return 1;
  }
  iVar3 = local_1c * 0x1c + param_1;
  printk("Rate bucket --> %u Byte/%u Byte\n",(uint)*(ushort *)(iVar3 + 0xa79830) << 10,
         (uint)*(ushort *)(iVar3 + 0xa7982e) << 10);
  if (DebugLevel < 0) {
    return 1;
  }
  iVar3 = local_1c * 0x1c + param_1;
  uVar1 = *(ushort *)(iVar3 + 0xa7983e);
  uVar2 = *(ushort *)(iVar3 + 0xa7983c);
  printk("Airtime token --> %u us(%u)/%u us(%u)\n",uVar1 >> 3,uVar1,uVar2 >> 3,uVar2);
LAB_00047588:
  if (-1 < DebugLevel) {
    param_1 = local_1c * 0x1c + param_1;
    printk("Airtime bucket --> %u us/%u us\n",(uint)*(byte *)(param_1 + 0xa79835) << 10,
           (uint)*(byte *)(param_1 + 0xa79834) << 10);
  }
  return 1;
}

