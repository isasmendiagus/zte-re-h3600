// module: mt7915.ko
// function: set_isr_cmd @ 0xbc070
// size: 256 bytes
//

undefined4 set_isr_cmd(int param_1,char *param_2)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  char *local_1c [2];
  uint local_14;
  
  local_1c[0] = param_2;
  if (0 < DebugLevel) {
    printk(":%s: arg = %s\n","set_isr_cmd",param_2);
  }
  pcVar1 = strsep(local_1c,":");
  if ((pcVar1 == (char *)0x0) || (local_1c[0] == (char *)0x0)) {
    if (DebugLevel < 1) {
      uVar4 = 0;
    }
    else {
      printk(":%s: Invalid parameters\n","set_isr_cmd");
      uVar4 = 0;
    }
  }
  else {
    uVar2 = os_str_toul(pcVar1,0,10);
    uVar3 = os_str_toul(local_1c[0],0,10);
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820600f0,&local_14);
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820600f0,
                  uVar3 & 0xffffff | ~local_14 & 0x80000000 | (uVar2 & 0x7f) << 0x18);
    uVar4 = 1;
  }
  return uVar4;
}

