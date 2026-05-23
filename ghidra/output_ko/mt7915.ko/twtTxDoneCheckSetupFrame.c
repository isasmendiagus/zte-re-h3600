// module: mt7915.ko
// function: twtTxDoneCheckSetupFrame @ 0x169c38
// size: 360 bytes
//

void twtTxDoneCheckSetupFrame(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 local_44 [6];
  undefined1 auStack_29 [21];
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar7 = *(int *)(param_1 + (uint)*(byte *)(param_2 + 0x2d) * 4 + 0xc);
  if ((iVar7 != 0) && (*(int *)(iVar7 + 0x14) == 2)) {
    puVar3 = (undefined4 *)(*(int *)(param_2 + 0xcc) + (uint)*(byte *)(iVar2 + 2));
    if (((*(byte *)(*(int *)(param_2 + 0xcc) + (uint)*(byte *)(iVar2 + 2)) & 0xfc) == 0xd0) &&
       (*(char *)(puVar3 + 6) == '\x16')) {
      if (*(char *)((int)puVar3 + 0x19) == '\x06') {
        if (*(int *)(&DAT_00580f3c + param_1 + (uint)*(byte *)(iVar7 + 0xe) * 0x2137b0) == 1) {
          puVar9 = puVar3;
          puVar1 = local_44;
          do {
            puVar10 = puVar1;
            puVar8 = puVar9;
            puVar9 = puVar8 + 4;
            uVar4 = puVar8[1];
            uVar5 = puVar8[2];
            uVar6 = puVar8[3];
            *puVar10 = *puVar8;
            puVar10[1] = uVar4;
            puVar10[2] = uVar5;
            puVar10[3] = uVar6;
            puVar1 = puVar10 + 4;
          } while (puVar9 != puVar3 + 8);
          uVar4 = puVar8[5];
          uVar5 = puVar8[6];
          puVar10[4] = *puVar9;
          puVar10[5] = uVar4;
          puVar10[6] = uVar5;
          uVar4 = twtGetRxSetupFlowId(auStack_29,uVar4,uVar5,puVar10 + 7);
          twtReqFsmSteps(param_1,iVar7,2,uVar4,0);
        }
      }
      else if ((*(char *)((int)puVar3 + 0x19) == '\a') &&
              (*(int *)(&DAT_00580f3c + param_1 + (uint)*(byte *)(iVar7 + 0xe) * 0x2137b0) == 6)) {
        twtReqFsmSteps(param_1,iVar7,0,*(byte *)((int)puVar3 + 0x1a) & 7,0);
      }
    }
  }
  return;
}

