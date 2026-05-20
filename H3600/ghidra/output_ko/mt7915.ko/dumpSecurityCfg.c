// module: mt7915.ko
// function: dumpSecurityCfg @ 0x34a48
// size: 260 bytes
//

void dumpSecurityCfg(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = WscGetAuthType(*param_1);
  if (param_2 <= DebugLevel) {
    printk("AKMMap=0x%x,WscAuthMode=0x%x\n",*param_1,uVar1);
  }
  uVar1 = WscGetEncryType(param_1[0x52]);
  if (DebugLevel < param_2) {
    return;
  }
  printk("EncrypType=0x%x,WscEncrypType=0x%x\n",param_1[0x52],uVar1);
  if (param_2 <= DebugLevel) {
    printk("RekeyInterval=%lu\n",param_1[0x9d]);
    if (DebugLevel < param_2) {
      return;
    }
    printk("RekeyMethod=%d\n",param_1[0x9c]);
    if (DebugLevel < param_2) {
      return;
    }
    printk("DefaultKeyID=%d\n",*(undefined1 *)(param_1 + 0x53));
    if (DebugLevel < param_2) {
      return;
    }
    printk("IEEE8021X=%d\n",*(undefined1 *)(param_1 + 0x165));
  }
  if (DebugLevel < param_2) {
    return;
  }
  printk("PSK=%s\n",(int)param_1 + 0x14d);
  return;
}

