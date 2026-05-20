// module: mt7915.ko
// function: UpdateBssScanParm @ 0xa22c4
// size: 276 bytes
//

void UpdateBssScanParm(int param_1,uint param_2,uint param_3,uint param_4,ushort param_5)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  short sStack_a;
  short local_6;
  
  uVar2 = param_4 >> 0x10;
  if (0x5f < uVar2 - 5) {
    uVar2 = 5;
  }
  *(short *)(param_1 + 0x7956a8) = (short)uVar2;
  uVar1 = param_3 & 0xffff;
  if (0x37a < (uVar1 - 10 & 0xffff)) {
    uVar1 = 900;
  }
  *(short *)(param_1 + 0x7956a2) = (short)uVar1;
  if ((param_2 & 0xffff) - 5 < 0x3e4) {
    *(short *)(param_1 + 0x79569e) = (short)param_2;
  }
  else {
    *(undefined2 *)(param_1 + 0x79569e) = 0x14;
  }
  sStack_a = (short)(param_2 >> 0x10);
  if (0x3de < (ushort)(sStack_a - 10U)) {
    sStack_a = 10;
  }
  *(short *)(param_1 + 0x7956a0) = sStack_a;
  local_6 = (short)(param_3 >> 0x10);
  if (0x2648 < (ushort)(local_6 - 200U)) {
    local_6 = 200;
  }
  *(short *)(param_1 + 0x7956a4) = local_6;
  uVar3 = (undefined2)param_4;
  if (0x26fc < ((param_4 & 0xffff) - 0x14 & 0xffff)) {
    uVar3 = 0x14;
  }
  *(undefined2 *)(param_1 + 0x7956a6) = uVar3;
  if (param_5 < 0x65) {
    *(ushort *)(param_1 + 0x7956aa) = param_5;
  }
  else {
    *(undefined2 *)(param_1 + 0x7956aa) = 0x19;
  }
  *(uint *)(param_1 + 0x7956ac) = uVar1 * uVar2;
  return;
}

