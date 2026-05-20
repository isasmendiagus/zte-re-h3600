// module: mt7915.ko
// function: HcDelRepeaterEntry @ 0xa912c
// size: 104 bytes
//

undefined4 HcDelRepeaterEntry(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 != 0) {
    OcDelRepeaterEntry(uVar2,*(undefined1 *)(param_1 + 0xe));
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcDelRepeaterEntry",*(undefined1 *)(param_1 + 0xc),
         DebugLevel,param_4);
  return 1;
}

