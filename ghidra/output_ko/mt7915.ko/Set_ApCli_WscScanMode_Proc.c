// module: mt7915.ko
// function: Set_ApCli_WscScanMode_Proc @ 0x29758
// size: 248 bytes
//

undefined4
Set_ApCli_WscScanMode_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined1 uVar3;
  uint uVar4;
  
  if (*(int *)(*param_1 + 0x38) != 0x400) {
    return 0;
  }
  uVar4 = *(uint *)(*param_1 + 0x3c) & 0xff;
  iVar2 = get_scan_ctrl_by_wdev
                    (param_1,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + uVar4 * 0x2137b0)),
                     0x400,uVar4 * 0x2137b,param_4);
  cVar1 = simple_strtol(param_2,0,10);
  uVar3 = 1;
  if (cVar1 != '\x01') {
    if (*(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x371a89) == '\x01') {
      uVar3 = 0;
      *(undefined4 *)(iVar2 + 0x1bc) = 0;
      *(undefined1 *)(iVar2 + 0x17e) = 0;
      *(undefined1 *)(iVar2 + 0x17c) = 0;
    }
    else {
      uVar3 = 0;
    }
  }
  iVar2 = DebugLevel;
  *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x371a89) = uVar3;
  if (2 < iVar2) {
    printk("%s:: (WscApCliScanMode=%d)\n","Set_ApCli_WscScanMode_Proc");
    return 1;
  }
  return 1;
}

