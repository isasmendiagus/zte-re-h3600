// module: mt7915.ko
// function: show_fwcmd_timeout_info @ 0xc4164
// size: 384 bytes
//

undefined4 show_fwcmd_timeout_info(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  if (DebugLevel < 1) {
    uVar5 = (uint)*(ushort *)(param_1 + 0xa7d0b6);
    iVar6 = jiffies;
    if (0x13 < uVar5) {
      uVar5 = 0x14;
    }
  }
  else {
    printk("\n%s:\n","show_fwcmd_timeout_info");
    iVar6 = jiffies;
    uVar4 = (uint)*(ushort *)(param_1 + 0xa7d0b6);
    uVar5 = uVar4;
    if (0x13 < uVar4) {
      uVar5 = 0x14;
    }
    if (0 < DebugLevel) {
      printk("\t- TimeoutCnt(%d), PrintCnt(%d), RecordCnt(%d)\n",uVar4,
             *(undefined2 *)(param_1 + 0xa7d0b8),0x14);
    }
  }
  if (uVar5 != 0) {
    uVar1 = *(ushort *)(param_1 + 0xa7d0b6);
    uVar4 = 0;
    do {
      if (-1 < DebugLevel) {
        iVar2 = (int)((((int)(uVar1 - 1) % 0x14 & 0xffffU) + 0x14) - uVar4) % 0x14;
        iVar3 = param_1 + iVar2 * 8;
        printk("[%02d/%02d] (%ld ms ago) FWCmdTimeout: cmd(%x), ext_cmd(%x), seq(%d), state(%d)\n",
               uVar4,iVar2,(uint)((iVar6 - *(int *)(iVar3 + 0xa7d0bc)) * 1000) / 100,
               *(undefined1 *)(iVar3 + 0xa7d0c0),*(undefined1 *)(iVar3 + 0xa7d0c1),
               *(undefined1 *)(iVar3 + 0xa7d0c2),*(undefined1 *)(iVar3 + 0xa7d0c3));
      }
      uVar4 = uVar4 + 1;
    } while ((uVar4 & 0xffff) < uVar5);
  }
  return 1;
}

