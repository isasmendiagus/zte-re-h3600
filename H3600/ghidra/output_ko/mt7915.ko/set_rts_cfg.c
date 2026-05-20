// module: mt7915.ko
// function: set_rts_cfg @ 0xbc3b0
// size: 524 bytes
//

undefined4 set_rts_cfg(int param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  char *local_1c [2];
  
  local_1c[0] = param_2;
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((((local_1c[0] == (char *)0x0) || (*local_1c[0] == '\0')) ||
      (pcVar2 = strsep(local_1c,":"), pcVar2 == (char *)0x0)) || (local_1c[0] == (char *)0x0)) {
    uVar5 = 0;
  }
  else {
    uVar5 = os_str_toul(pcVar2,0,10);
    uVar5 = uVar5 & 0xff;
    if (uVar5 < 2) {
      iVar3 = os_str_toul(local_1c[0],0,10);
      if (iVar3 == 0) {
        asic_rts_on_off_detail(param_1,uVar5,4,0x92b,0);
        iVar1 = DebugLevel;
        *(undefined1 *)(param_1 + uVar5 * 0x70 + 0xa7c454) = 0;
        if (iVar1 < 1) {
          return 1;
        }
        printk("enable rts\n");
        return 1;
      }
      if (iVar3 == 1) {
        asic_rts_on_off_detail(param_1,uVar5,0xff,0xffffff,0);
        iVar1 = DebugLevel;
        *(undefined1 *)(param_1 + uVar5 * 0x70 + 0xa7c454) = 1;
        if (iVar1 < 1) {
          return 1;
        }
        printk("disable rts\n");
        return 1;
      }
    }
  }
  if (0 < DebugLevel) {
    puVar4 = &_LC206;
    if (*(char *)(uVar5 * 0x70 + param_1 + 0xa7c454) == '\0') {
      puVar4 = &_LC207;
    }
    printk("rts is %s, asic_rts_on_off = %p\n",puVar4,*(undefined4 *)(iVar1 + 0x1cc));
    if (((0 < DebugLevel) && (printk("format: [bandidx]:[mode]\n"), 0 < DebugLevel)) &&
       ((printk("[bandidx]: 0/1\n"), 0 < DebugLevel &&
        (printk("[mode]: 0 = enable rts , 1 = disable rts,"), 0 < DebugLevel)))) {
      printk("2 = disable dynamic rts on/off alg, 3 = enable dynamic rts on/off alg\n");
    }
  }
  return 1;
}

