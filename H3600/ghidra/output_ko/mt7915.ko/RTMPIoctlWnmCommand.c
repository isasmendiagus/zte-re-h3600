// module: mt7915.ko
// function: RTMPIoctlWnmCommand @ 0x36434
// size: 200 bytes
//

uint RTMPIoctlWnmCommand(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_18 [4];
  int local_14 [2];
  
  local_14[0] = 0;
  os_alloc_mem(0,local_14,*(undefined2 *)(param_2 + 0x14));
  if (local_14[0] != 0) {
    uVar2 = *(uint *)(param_2 + 0x10);
    uVar4 = (uint)*(ushort *)(param_2 + 0x14);
    uVar3 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
    if (!CARRY4(uVar2,uVar4) && uVar2 + uVar4 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      uVar4 = __copy_from_user(local_14[0],uVar2,uVar4);
    }
    else if (uVar4 != 0) {
      __memzero(local_14[0],uVar4);
    }
    iVar1 = wnm_handle_command(param_1,local_14[0]);
    if (iVar1 != 0) {
      uVar4 = 0xffffffea;
    }
    os_free_mem(local_14[0]);
    return uVar4;
  }
  return 0;
}

