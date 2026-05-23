// module: mt7915.ko
// function: parse_mbssid_subelement @ 0x110ae8
// size: 372 bytes
//

void parse_mbssid_subelement(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  undefined4 local_2e;
  undefined1 local_2a;
  byte bStack_29;
  
  iVar4 = get_scan_tab_by_wdev();
  if (*(byte *)(param_3 + 2) - 1 < 8) {
    uVar5 = (uint)*(byte *)(param_3 + 4);
    pcVar10 = (char *)(param_3 + 3);
    uVar12 = *(byte *)(param_3 + 1) - 1 & 0xffff;
    if (uVar5 + 2 <= uVar12) {
      uVar11 = 0;
      do {
        if (((*pcVar10 == '\0') && (pcVar9 = pcVar10 + 2, pcVar9 != (char *)0x0)) &&
           (uVar8 = (byte)pcVar10[3] + 2, uVar8 <= uVar5)) {
          uVar7 = 0;
          if (pcVar10[2] != 'U') {
            do {
              pcVar9 = pcVar9 + uVar8;
              uVar7 = uVar7 + uVar8 & 0xffff;
              uVar8 = (byte)pcVar9[1] + 2;
              if (uVar5 < uVar7 + 2 + (uint)(byte)pcVar9[1]) goto LAB_00110b9c;
            } while (*pcVar9 != 'U');
            if (pcVar9 == (char *)0x0) goto LAB_00110b9c;
          }
          if (pcVar9[2] != '\0') {
            local_2e = *(undefined4 *)(param_4 + 6);
            cVar3 = (char)(1 << *(sbyte *)(param_3 + 2));
            bVar2 = cVar3 - 1;
            bStack_29 = (byte)((ushort)*(undefined2 *)(param_4 + 10) >> 8);
            _local_2a = CONCAT11(bVar2 & pcVar9[2] + (bStack_29 & bVar2) | -cVar3 & bStack_29,
                                 (char)*(undefined2 *)(param_4 + 10));
            iVar6 = BssTableSearch(iVar4,&local_2e,*(undefined1 *)(param_4 + 0x30));
            if (iVar6 != -1) {
              iVar6 = iVar6 * 0xaf4 + iVar4;
              *(undefined1 *)(iVar6 + 0xad4) = *(undefined1 *)(param_3 + 2);
              *(char *)(iVar6 + 0xad5) = pcVar9[2];
            }
          }
        }
LAB_00110b9c:
        pbVar1 = (byte *)(pcVar10 + 1);
        pcVar10 = pcVar10 + *pbVar1 + 2;
        uVar11 = uVar11 + *pbVar1 + 2 & 0xffff;
        uVar5 = (uint)(byte)pcVar10[1];
      } while (uVar11 + 2 + uVar5 <= uVar12);
    }
  }
  return;
}

