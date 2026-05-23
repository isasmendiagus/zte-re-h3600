// module: mt7915.ko
// function: wmm_ctrl_init @ 0xad6e4
// size: 192 bytes
//

undefined4 wmm_ctrl_init(int param_1,byte *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 extraout_r2;
  uint uVar6;
  undefined8 uVar7;
  int local_1c [2];
  
  bVar1 = *(byte *)(param_1 + 0xba8);
  uVar6 = (uint)bVar1;
  local_1c[0] = 0;
  os_alloc_mem(0,local_1c,uVar6 * 0x28);
  if (local_1c[0] == 0) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar7 = os_zero_mem(local_1c[0],uVar6 * 0x28);
    *param_2 = bVar1;
    uVar2 = extraout_r2;
    if (uVar6 != 0) {
      uVar2 = 0;
      uVar7 = 0;
    }
    *(int *)(param_2 + 4) = local_1c[0];
    if (uVar6 != 0) {
      do {
        iVar3 = (int)uVar7;
        *(char *)(local_1c[0] + iVar3 + 3) = (char)((ulonglong)uVar7 >> 0x20);
        uVar5 = (int)((ulonglong)uVar7 >> 0x20) + 1;
        *(undefined1 *)(local_1c[0] + iVar3 + 4) = uVar2;
        *(undefined1 *)(local_1c[0] + iVar3 + 1) = uVar2;
        *(undefined1 *)(local_1c[0] + iVar3) = uVar2;
        uVar7 = CONCAT44(uVar5,iVar3 + 0x28);
        *(undefined1 *)(local_1c[0] + iVar3 + 2) = uVar2;
      } while (uVar6 != uVar5);
    }
    uVar4 = 0;
  }
  return uVar4;
}

