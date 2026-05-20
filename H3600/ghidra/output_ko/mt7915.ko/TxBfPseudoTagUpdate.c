// module: mt7915.ko
// function: TxBfPseudoTagUpdate @ 0x89144
// size: 224 bytes
//

bool TxBfPseudoTagUpdate(int *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                        undefined1 param_5,undefined1 param_6,undefined1 param_7)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 local_31;
  undefined4 local_2d;
  undefined1 local_29;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (2 < DebugLevel) {
    printk("=>[%s]\n","TxBfPseudoTagUpdate");
  }
  if (iVar2 == 0) {
    uVar1 = 0;
    if (-1 < DebugLevel) {
      printk("wdev is NULL\n");
    }
  }
  else {
    uVar1 = HcGetBandByWdev(iVar2);
  }
  local_31 = CONCAT31(CONCAT12(param_4,CONCAT11(param_3,param_2)),0x18);
  local_2d = CONCAT13(uVar1,CONCAT12(param_7,CONCAT11(param_6,param_5)));
  iVar2 = CmdETxBfPseudoTagWrite(param_1,local_31,local_2d,local_29);
  return iVar2 == 0;
}

