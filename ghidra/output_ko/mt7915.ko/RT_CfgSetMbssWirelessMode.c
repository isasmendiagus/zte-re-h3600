// module: mt7915.ko
// function: RT_CfgSetMbssWirelessMode @ 0xb86c8
// size: 340 bytes
//

undefined4 RT_CfgSetMbssWirelessMode(int param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = os_str_tol(param_2,0,10);
  bVar1 = cfgmode_2_wmode(uVar3 & 0xff);
  if (bVar1 != 0) {
    iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (((((bVar1 & 0xb1) == 0) || ((*(uint *)(iVar4 + 0x2c) & 2) != 0)) &&
        (((bVar1 & 0x4e) == 0 || ((*(uint *)(iVar4 + 0x2c) & 1) != 0)))) &&
       (((bVar1 & 0x18) == 0 || ((*(uint *)(param_1 + 0xa39f8c) & 1) == 0)))) {
      if (((bVar1 & 0xb1) != 0) &&
         (((bVar1 & 0x4e) != 0 && (*(char *)(param_1 + 0x79504d) == '\x01')))) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("AP cannot support 2.4G/5G band mxied mode!\n");
        return 0;
      }
      *(byte *)(param_1 + 0x794c48) = bVar1;
      return 1;
    }
  }
  if (-1 < DebugLevel) {
    printk("%s(): Invalid wireless mode(%d, wmode=0x%x), ChipCap(%s)\n","RT_CfgSetMbssWirelessMode",
           uVar3,bVar1,(&PTR_s_Invalid_00294354)[*(uint *)(iVar2 + 0x2c) & 3]);
  }
  return 0;
}

