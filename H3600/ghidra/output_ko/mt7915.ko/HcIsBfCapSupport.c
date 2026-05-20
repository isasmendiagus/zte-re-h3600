// module: mt7915.ko
// function: HcIsBfCapSupport @ 0xa9070
// size: 68 bytes
//

undefined4 HcIsBfCapSupport(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0xabc) != 0)) {
    iVar1 = hdev_obj_state_ready();
    if (iVar1 == 0) {
      return 0;
    }
    uVar2 = RcIsBfCapSupport(*(undefined4 *)(param_1 + 0xabc));
    return uVar2;
  }
  return 0;
}

