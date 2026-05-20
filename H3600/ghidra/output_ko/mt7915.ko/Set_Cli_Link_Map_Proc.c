// module: mt7915.ko
// function: Set_Cli_Link_Map_Proc @ 0x30eb4
// size: 308 bytes
//

undefined4 Set_Cli_Link_Map_Proc(int *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  if (*(char *)((int)param_1 + 0x36790d) == '\x01') {
    if ((*(int *)(*param_1 + 0x38) - 0x400U & 0xfffffbff) == 0) {
      uVar3 = (uint)*(byte *)(*param_1 + 0x3c);
      if (uVar3 < 2) {
        uVar1 = os_str_tol(param_2,0,10);
        uVar1 = uVar1 & 0xff;
        uVar2 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        bVar4 = 0x1e < uVar1;
        if (uVar1 < 0x20) {
          bVar4 = uVar2 <= uVar1;
        }
        if (!bVar4) {
          UpdateMbssCliLinkMap
                    (param_1,uVar1,param_1 + uVar3 * 0x84dec + 0xdb6d6,
                     param_1 + uVar1 * 0x160d + 0xadc92);
          return 1;
        }
        if (-1 < DebugLevel) {
          printk("wrong mbss idx:%d to set link map.\n",uVar1);
          return 0;
        }
      }
      else if (-1 < DebugLevel) {
        printk("wrong cli link idx:%d to set link map.\n",uVar3);
        return 0;
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("Rept has not been enabled yet.\n");
    return 0;
  }
  return 0;
}

