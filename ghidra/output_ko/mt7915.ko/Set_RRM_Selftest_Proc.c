// module: mt7915.ko
// function: Set_RRM_Selftest_Proc @ 0x2200dc
// size: 184 bytes
//

undefined4 Set_RRM_Selftest_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined *local_16;
  undefined2 local_12;
  
  local_16 = &DAT_00430c00;
  local_12 = 0;
  iVar2 = *param_1;
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 == 1) {
    iVar1 = MacTableInsertEntry(param_1,&local_16,
                                param_1 + *(int *)(iVar2 + 0x3c) * 0x160d + 0xadc92,0x20001,1,1);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0xfc) = 2;
      *(ushort *)(iVar1 + 0xaf6) = *(ushort *)(iVar1 + 0xaf6) | 0x1000;
      *(byte *)(iVar1 + 0x11ec) = *(byte *)(iVar1 + 0x11ec) | 0x20;
      return 1;
    }
  }
  return 1;
}

