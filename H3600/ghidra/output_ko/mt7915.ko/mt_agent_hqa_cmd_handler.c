// module: mt7915.ko
// function: mt_agent_hqa_cmd_handler @ 0x24f7fc
// size: 372 bytes
//

int mt_agent_hqa_cmd_handler(int param_1,char *param_2)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  undefined4 uVar6;
  byte *pbVar7;
  uint local_2c [2];
  
  local_2c[0] = 0;
  if ((*param_2 != '\x01') ||
     (iVar1 = mt_agent_hqa_cmd_string_parser
                        (*(undefined4 *)(param_2 + 1),*(undefined4 *)(param_2 + 1)), iVar1 == 0)) {
    piVar5 = *(int **)(param_2 + 1);
    uVar6 = *(undefined4 *)(param_1 + 4);
    if (*piVar5 == -0x7fd7ebe8) {
      uVar3 = (*(ushort *)((int)piVar5 + 6) & 0xff) << 8 | (uint)(*(ushort *)((int)piVar5 + 6) >> 8)
      ;
      uVar4 = 0;
      *(ushort *)(piVar5 + 2) = *(ushort *)(piVar5 + 2) << 8 | *(ushort *)(piVar5 + 2) >> 8;
      do {
        if ((uVar3 & 0xff00) == (&DAT_002a46f0)[uVar4 * 3]) {
          pbVar7 = (byte *)(&DAT_002a46e8)[uVar4 * 3];
          if ((uVar3 & 0xff00) == 0x1600) {
            sys_ad_move_mem(local_2c,piVar5 + 3,4);
            uVar3 = local_2c[0] >> 0x18;
          }
          uVar3 = uVar3 & 0xff;
          if (*(int *)(&UNK_002a46ec + uVar4 * 0xc) != 0) {
            pbVar2 = pbVar7;
            if (*pbVar7 == uVar3) {
LAB_0024f8f4:
              iVar1 = (**(code **)(pbVar2 + 4))(uVar6,piVar5);
              goto LAB_0024f904;
            }
            iVar1 = 0;
            while( true ) {
              pbVar2 = pbVar2 + 8;
              iVar1 = iVar1 + 1;
              if (iVar1 == *(int *)(&UNK_002a46ec + uVar4 * 0xc)) break;
              if (pbVar7[iVar1 * 8] == uVar3) goto LAB_0024f8f4;
            }
          }
        }
        else {
          uVar4 = uVar4 + 1;
        }
      } while (uVar4 < 7);
      iVar1 = 0;
LAB_0024f904:
      if (uVar3 == 5) {
        *(undefined1 *)(piVar5 + 1) = 5;
      }
      else {
        *(undefined1 *)(piVar5 + 1) = 8;
      }
      *(undefined1 *)((int)piVar5 + 5) = 0x80;
      return iVar1;
    }
    iVar1 = 0x104;
  }
  return iVar1;
}

