// module: mt7915.ko
// function: HcIsRadioAcq @ 0xaa014
// size: 8 bytes
//

void HcIsRadioAcq(int param_1)

{
  hdev_obj_state_ready(*(undefined4 *)(param_1 + 0xabc));
  return;
}

