// module: mt7915.ko
// function: MT_ATERxDoneHandle @ 0x2821a8
// size: 216 bytes
//

/* WARNING: Type propagation algorithm not settling */

void MT_ATERxDoneHandle(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint local_28 [3];
  
  uVar1 = *(uint *)(param_1 + 0xa39c48);
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  *(uint *)(param_1 + 0xa39c48) = uVar1 + 1;
  *(uint *)(param_1 + 0xa39c4c) = *(int *)(param_1 + 0xa39c4c) + (uint)(0xfffffffe < uVar1);
  local_28[0] = 0;
  local_28[1] = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5030,local_28);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f5130,local_28 + 1);
  (**(code **)(iVar2 + 100))(param_1,param_2);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    uVar1 = (uint)*(byte *)(param_2 + 0x4c);
  }
  else {
    uVar1 = 0;
    if (*(ushort *)(param_2 + 0x80) != local_28[0]) {
      uVar1 = 1;
    }
  }
  param_1 = param_1 + uVar1 * 4;
  *(int *)(param_1 + 0xa3b74c) = *(int *)(param_1 + 0xa3b74c) + 1;
  return;
}

