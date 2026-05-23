// module: mt7915.ko
// function: rtmp_IpAssembleHandle @ 0xc776c
// size: 884 bytes
//

uint rtmp_IpAssembleHandle(int param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  int in_stack_0000000c;
  short local_38;
  int *local_2c [2];
  
  iVar14 = jiffies;
  puVar17 = (undefined4 *)(param_1 + 0x286328);
  puVar12 = (undefined4 *)(param_1 + 0x286308);
  puVar16 = puVar17;
  do {
    puVar8 = *(undefined4 **)*puVar12;
    puVar7 = (undefined4 *)*puVar12;
    while (puVar6 = puVar8, puVar12 != puVar7) {
      if ((puVar7[4] == 0) || (-1 < (puVar7[8] + 100000) - iVar14)) {
        puVar8 = (undefined4 *)*puVar6;
        puVar7 = puVar6;
      }
      else {
        if (puVar7 == (undefined4 *)*puVar16) {
          *puVar16 = 0;
        }
        FUN_000c4ee8(param_1,puVar7);
        puVar8 = (undefined4 *)*puVar6;
        puVar7 = puVar6;
      }
    }
    puVar12 = puVar12 + 2;
    puVar16 = puVar16 + 1;
  } while (puVar12 != puVar17);
  if ((*(byte *)(param_3 + 0xc) & 4) != 0) {
    uVar2 = *(ushort *)(in_stack_0000000c + 0x14);
    uVar4 = (uint)(uVar2 >> 8);
    uVar5 = (uVar2 & 0xff) << 8;
    uVar10 = uVar5 & 0x3fff | uVar4;
    if (uVar10 != 0) {
      uVar3 = *(ushort *)(in_stack_0000000c + 0x10);
      uVar11 = (*(ushort *)(in_stack_0000000c + 0x12) & 0xff) << 8 |
               (uint)(*(ushort *)(in_stack_0000000c + 0x12) >> 8);
      bVar1 = *(byte *)(in_stack_0000000c + 0xe);
      local_38 = (short)param_4;
      if (uVar10 == 0x2000) {
        iVar15 = param_1 + (param_4 + 0x50c61) * 8;
        iVar14 = param_1 + local_38 * 8;
        for (local_2c[0] = *(int **)(iVar14 + 0x286308); (int *)iVar15 != local_2c[0];
            local_2c[0] = (int *)*local_2c[0]) {
          if (uVar11 == local_2c[0][6]) {
            if (local_2c[0] != (int *)0x0) goto LAB_000c79ec;
            break;
          }
        }
        local_2c[0] = (int *)0x0;
        os_alloc_mem(0,local_2c,0x24);
        iVar9 = jiffies;
        if (local_2c[0] != (int *)0x0) {
          local_2c[0][7] = ((uVar3 & 0xff) << 8 | (uint)(uVar3 >> 8)) + (bVar1 & 0xf) * -4;
          local_2c[0][8] = iVar9;
          local_2c[0][3] = 0;
          local_2c[0][2] = 0;
          local_2c[0][4] = 0;
          local_2c[0][6] = uVar11;
          *local_2c[0] = *(int *)(iVar14 + 0x286308);
          local_2c[0][1] = iVar15;
          *(int **)(*(int *)(iVar14 + 0x286308) + 4) = local_2c[0];
          *(int **)(iVar14 + 0x286308) = local_2c[0];
LAB_000c79ec:
          puVar17[local_38] = local_2c[0];
          *param_3 = 0;
          if ((undefined4 *)local_2c[0][3] == (undefined4 *)0x0) {
            local_2c[0][2] = (int)param_3;
          }
          else {
            *(undefined4 *)local_2c[0][3] = param_3;
          }
          local_2c[0][3] = (int)param_3;
          local_2c[0][4] = local_2c[0][4] + 1;
          return 0;
        }
      }
      else {
        iVar14 = (int)local_38;
        piVar13 = (int *)puVar17[iVar14];
        if ((piVar13 != (int *)0x0) && (*(uint *)((int)piVar13 + 0x18) == uVar11)) {
LAB_000c7914:
          *param_3 = 0;
          if (*(undefined4 **)((int)piVar13 + 0xc) == (undefined4 *)0x0) {
            *(undefined4 **)((int)piVar13 + 8) = param_3;
          }
          else {
            **(undefined4 **)((int)piVar13 + 0xc) = param_3;
          }
          *(undefined4 **)((int)piVar13 + 0xc) = param_3;
          iVar15 = *(int *)((int)piVar13 + 0x10) + 1;
          *(int *)((int)piVar13 + 0x10) = iVar15;
          if (((uVar2 & 0x20) != 0) || ((uVar5 & 0x1fff) == 0 && uVar4 == 0)) {
            return 0;
          }
          iVar9 = __aeabi_idiv((uVar5 & 0x1fff | uVar4) << 3,*(undefined4 *)((int)piVar13 + 0x1c));
          if (iVar15 != iVar9 + 1) {
            FUN_000c4ee8(param_1,piVar13);
            puVar17[iVar14] = 0;
            return 1;
          }
          iVar15 = ge_enq_req(param_1,0,param_4,param_2,(int)piVar13 + 8);
          if (iVar15 != 0) {
            FUN_000c4ee8(param_1,piVar13);
            puVar17[iVar14] = 0;
            return uVar2 & 0x20;
          }
          FUN_000c4ee8(param_1,piVar13);
          puVar17[iVar14] = 0;
          return 1;
        }
        for (piVar13 = *(int **)(param_1 + (param_4 + 0x50c61) * 8);
            (int *)(param_1 + (param_4 + 0x50c61) * 8) != piVar13; piVar13 = (int *)*piVar13) {
          if (uVar11 == piVar13[6]) {
            if (piVar13 != (int *)0x0) {
              puVar17[iVar14] = piVar13;
              goto LAB_000c7914;
            }
            break;
          }
        }
      }
      RTMPFreeNdisPacket(param_1,param_3);
      return 1;
    }
  }
  return 2;
}

