// module: idmfdb.ko
// function: INC_MTRANS_CNT @ 0x10e38
// size: 316 bytes
//

void INC_MTRANS_CNT(uint param_1,byte *param_2,byte *param_3,int param_4)

{
  int iVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined1 *puVar4;
  uint uVar5;
  
  uVar5 = ((uint)param_2[1] << 8 | (uint)*param_2 << 0x10 | (uint)param_2[2]) ^ param_1 ^
          ~((uint)param_2[4] << 8 | (uint)param_2[3] << 0x10 | (uint)param_2[5]) ^
          ((uint)param_3[1] << 8 | (uint)*param_3 << 0x10 | (uint)param_3[2]) ^
          ~((uint)param_3[4] << 8 | (uint)param_3[3] << 0x10 | (uint)param_3[5]);
  iVar1 = (uVar5 & 0x7f) * 0x30;
  puVar4 = &g_mtrans_dbg_cnt + iVar1;
  if ((&g_mtrans_dbg_cnt)[iVar1] != '\0') {
    if (*(uint *)(&DAT_00014d14 + iVar1) == uVar5) goto LAB_00010f18;
    iVar1 = ((uVar5 & 0x3f) + 0x80) * 0x30;
    puVar4 = &g_mtrans_dbg_cnt + iVar1;
    if ((&g_mtrans_dbg_cnt)[iVar1] != '\0') {
      if (*(uint *)(&DAT_00014d14 + iVar1) != uVar5) {
        return;
      }
      goto LAB_00010f18;
    }
  }
  *(uint *)(puVar4 + 4) = uVar5;
  *puVar4 = 1;
  *(undefined4 *)(puVar4 + 8) = *(undefined4 *)param_2;
  *(undefined2 *)(puVar4 + 0xc) = *(undefined2 *)(param_2 + 4);
  *(undefined4 *)(puVar4 + 0xe) = *(undefined4 *)param_3;
  uVar2 = *(undefined2 *)(param_3 + 4);
  *(uint *)(puVar4 + 0x18) = param_1;
  *(undefined2 *)(puVar4 + 0x12) = uVar2;
LAB_00010f18:
  uVar5 = *(uint *)(puVar4 + 0x20);
  uVar3 = *(uint *)(puVar4 + 0x28);
  *(uint *)(puVar4 + 0x20) = uVar5 + 1;
  *(uint *)(puVar4 + 0x24) = *(int *)(puVar4 + 0x24) + (uint)(0xfffffffe < uVar5);
  uVar5 = *(uint *)(param_4 + 100);
  *(uint *)(puVar4 + 0x28) = uVar3 + uVar5;
  *(uint *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x2c) + (uint)CARRY4(uVar3,uVar5);
  return;
}

