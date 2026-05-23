// module: mt7915.ko
// function: MtCmdATESetPowerDropLevel @ 0x1b6d5c
// size: 216 bytes
//

void MtCmdATESetPowerDropLevel(int param_1,int param_2,undefined1 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte local_64 [4];
  undefined1 local_60;
  undefined1 local_5f;
  
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
    bVar1 = 0;
    if (*(int *)(param_1 + 0xa77bb4) == 1) {
      bVar1 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
    }
  }
  else {
    bVar1 = 1;
  }
  if (param_2 - 0x5bU < 9) {
    uVar2 = 0;
  }
  else if (param_2 - 0x3dU < 0x1e) {
    uVar2 = 1;
  }
  else if (param_2 - 0x1fU < 0x1e) {
    uVar2 = 3;
  }
  else if (param_2 - 0x10U < 0xf) {
    uVar2 = 6;
  }
  else if (param_2 - 10U < 6) {
    uVar2 = 9;
  }
  else if (param_2 - 1U < 9) {
    uVar2 = 0xc;
  }
  else {
    uVar2 = 0;
  }
  os_zero_mem(local_64,0x4c);
  local_64[1] = 0x1b;
  local_64[0] = bVar1;
  local_60 = uVar2;
  local_5f = param_3;
  MtCmdATETest(param_1,local_64);
  return;
}

