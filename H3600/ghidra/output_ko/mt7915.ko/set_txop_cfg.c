// module: mt7915.ko
// function: set_txop_cfg @ 0xbc174
// size: 568 bytes
//

undefined4 set_txop_cfg(undefined4 param_1,char *param_2)

{
  undefined2 uVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_1c [2];
  
  local_1c[0] = param_2;
  if (0 < DebugLevel) {
    printk(":%s: current setting txop 0=%x, txop 60=%x, txop 80=%x, txop fe=%x\n","set_txop_cfg",
           txop0,txop60,txop80,txopfe);
  }
  pcVar2 = strsep(local_1c,":");
  if ((pcVar2 == (char *)0x0) || (local_1c[0] == (char *)0x0)) {
    if (DebugLevel < 1) {
      uVar5 = 0;
    }
    else {
      printk(":%s: Invalid parameters\n","set_txop_cfg");
      uVar5 = 0;
    }
  }
  else {
    do {
      pcVar3 = strsep(local_1c,":");
      if (pcVar3 == (char *)0x0) {
        pcVar3 = local_1c[0];
      }
      iVar4 = os_str_toul(pcVar2,0,0x10);
      if (iVar4 == 0x60) {
        txop60 = os_str_toul(pcVar3,0,0x10);
        uVar1 = txop60;
joined_r0x000bc2b0:
        if (0 < DebugLevel) {
          printk(":%s: txop60 change to %x\n","set_txop_cfg",uVar1);
        }
      }
      else if (iVar4 < 0x61) {
        if (iVar4 == 0) {
          txop0 = os_str_toul(pcVar3,0,0x10);
          if (0 < DebugLevel) {
            printk(":%s: txop0 change to %x\n","set_txop_cfg",txop0);
          }
        }
        else {
LAB_000bc2cc:
          if (0 < DebugLevel) {
            uVar5 = os_str_toul(pcVar2,0,0x10);
            printk(":%s: not support txop%lx\n","set_txop_cfg",uVar5);
          }
        }
      }
      else {
        if (iVar4 != 0x80) {
          if (iVar4 == 0xfe) {
            txopfe = os_str_toul(pcVar3,0,0x10);
            uVar1 = txopfe;
            goto joined_r0x000bc2b0;
          }
          goto LAB_000bc2cc;
        }
        txop80 = os_str_toul(pcVar3,0,0x10);
        if (0 < DebugLevel) {
          printk(":%s: txop80 change to %x\n","set_txop_cfg",txop80);
        }
      }
      pcVar2 = strsep(local_1c,":");
    } while (pcVar2 != (char *)0x0);
    uVar5 = 1;
  }
  return uVar5;
}

