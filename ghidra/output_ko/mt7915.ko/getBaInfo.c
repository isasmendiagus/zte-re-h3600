// module: mt7915.ko
// function: getBaInfo @ 0x61488
// size: 704 bytes
//

void getBaInfo(int param_1,char *param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  
  iVar1 = HcGetMaxStaNum(param_1);
  iVar8 = 0;
  iVar6 = param_1;
  if (0 < iVar1) {
    do {
      if (((*(int *)(iVar6 + 0xa1d20) == 2 ||
            (*(int *)(iVar6 + 0xa1d20) - 0x10001U & 0xfffeffff) == 0) &&
          (*(int *)(iVar6 + 0xa1e1c) == 2)) ||
         ((*(uint *)(iVar8 * 0x14c0 + param_1 + 0xa1d20) & 0xc) != 0)) {
        uVar3 = (uint)*(byte *)(iVar6 + 0xa1e10);
        puVar7 = (ushort *)(iVar6 + 0xa29f2);
        uVar10 = (uint)*(byte *)(iVar6 + 0xa1e11);
        uVar9 = (uint)*(ushort *)(iVar6 + 0xa1e18);
        sprintf(param_2,"%s\n%02x:%02x:%02x:%02x:%02x:%02x (Aid = %d) (AP) -\n",param_2,
                (uint)*(byte *)(iVar6 + 0xa1e0c),(uint)*(byte *)(iVar6 + 0xa1e0d),
                (uint)*(byte *)(iVar6 + 0xa1e0e),(uint)*(byte *)(iVar6 + 0xa1e0f),uVar3,uVar10,uVar9
               );
        sprintf(param_2,"%s[Recipient]\n",param_2);
        iVar1 = 0;
        do {
          while( true ) {
            puVar7 = puVar7 + 1;
            if (*puVar7 == 0) break;
            iVar5 = (uint)*puVar7 * 0x60;
            iVar11 = param_1 + 0x1c0 + iVar5;
            iVar4 = iVar1 + 1;
            sprintf(param_2,"%sTID=%d, BAWinSize=%d, LastIndSeq=%d, ReorderingPkts=%d\n",param_2,
                    iVar1,(uint)*(ushort *)(iVar11 + 0x14),(uint)*(ushort *)(iVar11 + 0xc),
                    *(undefined4 *)(param_1 + iVar5 + 500),uVar3,uVar10,uVar9);
            iVar1 = iVar4;
            if (iVar4 == 8) goto LAB_00061618;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 != 8);
LAB_00061618:
        sprintf(param_2,"%s\n",param_2);
        sprintf(param_2,"%s[Originator]\n",param_2);
        puVar7 = (ushort *)((int)&DAT_000a2a00 + iVar6 + 2);
        iVar1 = 0;
        do {
          while( true ) {
            puVar7 = puVar7 + 1;
            if (*puVar7 == 0) break;
            iVar4 = param_1 + 0x1c0 + (uint)*puVar7 * 0x48;
            iVar5 = iVar1 + 1;
            sprintf(param_2,"%sTID=%d, BAWinSize=%d, StartSeq=%d, CurTxSeq=%d\n",param_2,iVar1,
                    (uint)*(ushort *)(iVar4 + 0x1b004),(uint)*(ushort *)(iVar4 + 0x1b008),
                    (uint)*(ushort *)
                           (param_1 + 0x1c0 +
                            (iVar1 + (uint)*(ushort *)(iVar6 + 0xa1e00) * 0x310 + 0x17a78) * 2 + 4))
            ;
            iVar1 = iVar5;
            if (iVar5 == 8) goto LAB_000616dc;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 != 8);
LAB_000616dc:
        sprintf(param_2,"%s\n\n",param_2);
      }
      iVar6 = iVar6 + 0x14c0;
      sVar2 = strlen(param_2);
      if (param_3 - 0x1eU < sVar2) {
        return;
      }
      iVar8 = iVar8 + 1;
      iVar1 = HcGetMaxStaNum(param_1);
    } while (iVar8 < iVar1);
  }
  return;
}

