// module: mt7915.ko
// function: dumpWlanCfg @ 0x34bac
// size: 464 bytes
//

void dumpWlanCfg(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar1;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  int iVar2;
  
  if (param_1 == 0) {
    return;
  }
  iVar2 = *(int *)(param_1 + 0xb10);
  if (iVar2 == 0) {
    return;
  }
  if (DebugLevel < param_2) {
    return;
  }
  printk("\nht_bw=%d\n",*(undefined1 *)(iVar2 + 0x15));
  uVar1 = extraout_r2;
  if (DebugLevel < param_2) {
LAB_00034c5c:
    if (param_2 <= DebugLevel) {
      printk("MpduDensity=%d\n",*(undefined1 *)(iVar2 + 0x2c));
      if (DebugLevel < param_2) {
        return;
      }
      printk("mmps=%d\n",*(undefined1 *)(iVar2 + 0x2e));
      goto LAB_00034c9c;
    }
LAB_00034cdc:
    if (DebugLevel < param_2) goto LAB_00034d5c;
    printk("vht_bw=%d\n",*(undefined1 *)(iVar2 + 0x5c));
    if (DebugLevel < param_2) {
      return;
    }
    printk("vht_sgi=%d\n",*(undefined1 *)(iVar2 + 0x5f));
  }
  else {
    printk("ht_gi=%d\n",*(undefined1 *)(iVar2 + 0x18));
    if (DebugLevel < param_2) {
      return;
    }
    printk("ht_stbc=%d\n",*(undefined1 *)(iVar2 + 0x16));
    if (param_2 <= DebugLevel) {
      printk("ext_cha=%d\n",*(undefined1 *)(iVar2 + 0x14));
      if (DebugLevel < param_2) {
        return;
      }
      printk("ht_protect_en=%d\n",*(undefined1 *)(iVar2 + 0x19));
      uVar1 = extraout_r2_00;
      goto LAB_00034c5c;
    }
LAB_00034c9c:
    if (param_2 <= DebugLevel) {
      printk("ba_decline=%d\n",*(undefined1 *)(iVar2 + 0x30));
      if (DebugLevel < param_2) {
        return;
      }
      printk("ba_enable=%d\n",*(undefined1 *)(iVar2 + 0x31));
      uVar1 = extraout_r2_01;
      goto LAB_00034cdc;
    }
  }
  if (DebugLevel < param_2) {
    return;
  }
  printk("vht_stbc=%d\n",*(undefined1 *)(iVar2 + 0x5d));
  if (DebugLevel < param_2) {
    return;
  }
  printk("vht_bw_sig=%d\n",*(undefined1 *)(iVar2 + 0x60));
  uVar1 = extraout_r2_02;
LAB_00034d5c:
  if (DebugLevel < param_2) {
    return;
  }
  printk("twtsupport=%d\n",*(undefined1 *)(iVar2 + 0x70),uVar1,param_4);
  return;
}

