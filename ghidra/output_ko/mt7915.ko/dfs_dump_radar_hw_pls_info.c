// module: mt7915.ko
// function: dfs_dump_radar_hw_pls_info @ 0x231490
// size: 504 bytes
//

void dfs_dump_radar_hw_pls_info(undefined4 param_1,undefined1 *param_2)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  
  if (param_2 == (undefined1 *)0x0) {
    return;
  }
  if ((((DebugLevel < 1) ||
       (printk("\n--------------------------------------------------------------\n"), DebugLevel < 1
       )) || (printk("===> RDD-%d: Interrupt\n",*param_2), DebugLevel < 1)) ||
     (printk("\n------------------------HW pulse buffer-----------------------\n"), DebugLevel < 1))
  {
    uVar2 = (uint)(byte)param_2[7];
    if (uVar2 == 0) {
      return;
    }
  }
  else {
    printk(
          "Index\t | ST(us)\t | PW(us)\t | Power(dBm)\t | \tSC\t | \tReset\t | \tMDRDY | \tTX_active\n"
          );
    uVar2 = (uint)(byte)param_2[7];
    iVar3 = DebugLevel;
    if (uVar2 == 0) goto LAB_002314f0;
  }
  uVar5 = 0;
  iVar3 = DebugLevel;
  do {
    if (0 < iVar3) {
      printk("%d\t%u\t\t",uVar5,(uint)(*(int *)(param_2 + uVar5 * 0xc + 0x324) << 2) / 10);
      if (0 < DebugLevel) {
        iVar3 = (int)(short)(*(short *)(param_2 + uVar5 * 0xc + 0x32a) + -0x400);
        if (iVar3 < 0) {
          iVar3 = iVar3 + 3;
        }
        printk("%u\t\t%d\t\t",((uint)*(ushort *)(param_2 + uVar5 * 0xc + 0x328) << 2) / 10,
               iVar3 >> 2);
        if (0 < DebugLevel) {
          pcVar1 = "false";
          if (param_2[uVar5 * 0xc + 0x32c] != '\0') {
            pcVar1 = "true";
          }
          pcVar4 = "true";
          if (param_2[uVar5 * 0xc + 0x32d] == '\0') {
            pcVar4 = "false";
          }
          printk("%s\t\t%s\t\t",pcVar1,pcVar4);
          if ((0 < DebugLevel) && (printk(&_LC66,param_2[uVar5 * 0xc + 0x32e]), 0 < DebugLevel)) {
            printk("%d\t\t\n",param_2[uVar5 * 0xc + 0x32f]);
          }
        }
      }
      uVar2 = (uint)(byte)param_2[7];
      iVar3 = DebugLevel;
    }
    uVar5 = uVar5 + 1 & 0xff;
  } while (uVar5 < uVar2);
LAB_002314f0:
  if (iVar3 < 1) {
    return;
  }
  printk("--------------------------------------------------------------\n");
  return;
}

