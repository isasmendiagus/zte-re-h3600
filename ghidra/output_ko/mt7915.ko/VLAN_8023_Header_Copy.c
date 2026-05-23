// module: mt7915.ko
// function: VLAN_8023_Header_Copy @ 0x2446e8
// size: 144 bytes
//

undefined4
VLAN_8023_Header_Copy
          (uint param_1,uint param_2,undefined4 *param_3,uint param_4,undefined4 *param_5,
          undefined2 *param_6)

{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    memcpy(param_5,param_3,param_4);
    return 0;
  }
  uVar4 = *param_3;
  uVar2 = param_3[2];
  param_5[1] = param_3[1];
  uVar3 = param_1 & 0xfff | (param_2 & 7) << 0xd;
  param_5[2] = uVar2;
  *param_5 = uVar4;
  uVar1 = *param_6;
  *(ushort *)((int)param_5 + 0xe) = (ushort)(uVar3 >> 8) | (ushort)(uVar3 << 8);
  *(undefined2 *)(param_5 + 3) = uVar1;
  *(undefined2 *)(param_5 + 4) = *(undefined2 *)(param_3 + 3);
  if (param_4 < 0xf) {
    return 4;
  }
  memcpy((void *)((int)param_5 + 0x12),(void *)((int)param_3 + 0xe),param_4 - 0xe);
  return 4;
}

