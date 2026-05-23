// module: mt7915.ko
// function: MATEngineTxHandle @ 0x79c58
// size: 456 bytes
//

undefined4 MATEngineTxHandle(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  ushort uVar7;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  bVar1 = false;
  local_16 = 0;
  local_14 = 0;
  local_12 = 0;
  if (*(int *)(param_1 + 0x794b28) != 1) {
    return 0;
  }
  iVar4 = *(int *)(param_2 + 0xcc);
  if (iVar4 == 0) {
    return 0;
  }
  uVar7 = *(ushort *)(iVar4 + 0xc) << 8 | *(ushort *)(iVar4 + 0xc) >> 8;
  if (uVar7 == 0x8100) {
    uVar7 = *(ushort *)(iVar4 + 0x10) << 8 | *(ushort *)(iVar4 + 0x10) >> 8;
    if (uVar7 == 0x800) {
      puVar5 = MATProtoIPHandle;
    }
    else {
      bVar1 = true;
      if (uVar7 != 0x806) goto LAB_00079cb8;
      puVar5 = MATProtoARPHandle;
    }
LAB_00079d14:
    iVar4 = iVar4 + 0x12;
  }
  else {
    if (uVar7 == 0x800) {
      puVar5 = MATProtoIPHandle;
    }
    else if (uVar7 == 0x806) {
      puVar5 = MATProtoARPHandle;
    }
    else {
LAB_00079cb8:
      if (uVar7 == 0x8863) {
        iVar6 = 2;
      }
      else if (uVar7 == 0x8864) {
        iVar6 = 3;
      }
      else {
        if (uVar7 != 0x86dd) {
          return 0;
        }
        iVar6 = 4;
      }
      puVar5 = (undefined1 *)(&DAT_00291860)[iVar6 * 2];
      if (bVar1) goto LAB_00079d14;
    }
    iVar4 = iVar4 + 0xe;
  }
  if (param_4 == 2) {
    puVar3 = (undefined2 *)(&DAT_0036db73 + param_1 + param_3 * 0x2137b0);
  }
  else if (param_4 == 0x40001) {
    puVar3 = (undefined2 *)(param_3 * 0x42f4 + *(int *)(&DAT_003687a8 + param_1) + 0x83);
  }
  else if (DebugLevel < 0) {
    puVar3 = &local_16;
  }
  else {
    printk(&_LC4,param_2,0x40001,DebugLevel);
    puVar3 = &local_16;
  }
  if (*(code **)(puVar5 + 4) == (code *)0x0) {
    return 0;
  }
  uVar2 = (**(code **)(puVar5 + 4))(param_1 + 0x794b28,param_2,iVar4,puVar3);
  return uVar2;
}

