// module: mt7915.ko
// function: load_fw_v1 @ 0x1bfc6c
// size: 456 bytes
//

int load_fw_v1(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  uint local_34;
  uint local_30;
  
  if ((char)param_3[1] == '\0') {
    local_34 = 0;
    local_30 = 0;
  }
  else {
    iVar4 = 0;
    local_30 = 0;
    uVar5 = 0;
    local_34 = 0;
    do {
      uVar5 = uVar5 + 1;
      puVar6 = (undefined4 *)(*param_3 + iVar4);
      iVar4 = iVar4 + 0x1c;
      uVar3 = (uint)*(byte *)(puVar6 + 3);
      bVar9 = (*(byte *)(puVar6 + 3) & 0x20) != 0;
      if (bVar9) {
        uVar3 = puVar6[1];
      }
      *(undefined4 *)(param_1 + 0xa7861c) = 1;
      bVar1 = *(byte *)(puVar6 + 3);
      if (bVar9) {
        local_34 = 1;
        local_30 = uVar3;
      }
      if ((bVar1 & 1) == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 8;
      }
      if ((bVar1 & 0x10) == 0) {
        uVar7 = 0;
      }
      else {
        uVar7 = 0x40;
      }
      if (param_2 == 1) {
        uVar8 = 0x10;
      }
      else {
        uVar8 = 0;
      }
      iVar2 = MtCmdAddressLenReq(param_1,puVar6[1],puVar6[2],
                                 bVar1 & 7 | 0x80000000 | uVar3 | uVar7 | uVar8);
      if (iVar2 != 0) {
LAB_001bfd60:
        os_free_mem(*param_3);
        *param_3 = 0;
        *(undefined1 *)(param_3 + 1) = 0;
        goto LAB_001bfd7c;
      }
      *(undefined4 *)(param_1 + 0xa7861c) = 2;
      iVar2 = FUN_001bfba4(param_1,*puVar6,puVar6[2]);
      if (iVar2 != 0) goto LAB_001bfd60;
    } while (uVar5 < *(byte *)(param_3 + 1));
  }
  *(undefined4 *)(param_1 + 0xa7861c) = 1;
  if (param_2 == 1) {
    uVar5 = 4;
  }
  else {
    uVar5 = 0;
  }
  iVar2 = MtCmdFwStartReq(param_1,uVar5 | local_34,local_30);
  os_free_mem(*param_3);
  *param_3 = 0;
  *(undefined1 *)(param_3 + 1) = 0;
  if (iVar2 == 0) {
    return 0;
  }
LAB_001bfd7c:
  iVar4 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa7861c) = 0;
  if (0 < iVar4) {
    printk("%s: load fw fail\n","load_fw_v1");
  }
  return iVar2;
}

