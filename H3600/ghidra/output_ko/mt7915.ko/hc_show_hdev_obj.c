// module: mt7915.ko
// function: hc_show_hdev_obj @ 0xa970c
// size: 36 bytes
//

void hc_show_hdev_obj(int param_1)

{
  int iVar1;
  
  iVar1 = hdev_obj_state_ready(*(undefined4 *)(param_1 + 0xabc));
  if (iVar1 == 0) {
    return;
  }
  HdevObjShow(*(undefined4 *)(param_1 + 0xabc));
  return;
}

