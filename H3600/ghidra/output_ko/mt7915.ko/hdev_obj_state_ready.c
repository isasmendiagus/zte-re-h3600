// module: mt7915.ko
// function: hdev_obj_state_ready @ 0xae904
// size: 24 bytes
//

bool hdev_obj_state_ready(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 != 0) {
    bVar1 = *(char *)(param_1 + 0x1c) == '\x01';
  }
  return bVar1;
}

