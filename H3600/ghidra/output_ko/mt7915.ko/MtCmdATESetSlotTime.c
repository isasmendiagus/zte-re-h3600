// module: mt7915.ko
// function: MtCmdATESetSlotTime @ 0x1b6cc8
// size: 148 bytes
//

void MtCmdATESetSlotTime(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                        undefined2 param_5,undefined1 param_6)

{
  byte bVar1;
  byte local_6c [4];
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined2 local_64;
  undefined1 local_62;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
    bVar1 = 0;
    if (*(int *)(param_1 + 0xa77bb4) == 1) {
      bVar1 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
    }
  }
  else {
    bVar1 = 1;
  }
  os_zero_mem(local_6c,0x4c);
  local_64 = param_5;
  local_62 = param_6;
  local_6c[1] = 0x13;
  local_6c[0] = bVar1;
  local_68 = param_2;
  local_67 = param_3;
  local_66 = param_4;
  MtCmdATETest(param_1,local_6c);
  return;
}

