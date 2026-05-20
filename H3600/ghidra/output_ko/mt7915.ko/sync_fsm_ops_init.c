// module: mt7915.ko
// function: sync_fsm_ops_init @ 0x10bddc
// size: 104 bytes
//

undefined4 sync_fsm_ops_init(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 0x14);
  if (uVar1 != 8) {
    if (uVar1 < 9) {
      if (uVar1 != 1) goto LAB_0010be28;
    }
    else if ((uVar1 != 0x20) && ((uVar1 == 0x100 || (uVar1 != 0x10)))) {
LAB_0010be28:
      *(undefined1 **)(param_1 + 0xbcc) = sta_fsm_ops;
      return 1;
    }
  }
  *(undefined1 **)(param_1 + 0xbcc) = ap_fsm_ops;
  return 1;
}

