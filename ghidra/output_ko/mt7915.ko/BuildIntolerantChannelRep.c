// module: mt7915.ko
// function: BuildIntolerantChannelRep @ 0xa20a8
// size: 536 bytes
//

int BuildIntolerantChannelRep(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char cVar10;
  int local_7c;
  char cStack_70;
  undefined4 local_6f;
  undefined2 local_6b;
  char local_69;
  char local_68 [68];
  
  local_6f = 0x200c0b00;
  local_6b = 0x3621;
  local_69 = '7';
  local_7c = 0;
  RTMPZeroMemory(local_68,0x40);
  iVar4 = 0;
  pcVar9 = &cStack_70;
  do {
    pcVar9 = pcVar9 + 1;
    cVar1 = *pcVar9;
    if (*(char *)(param_1 + 0x7956b8) != '\0') {
      uVar8 = 0;
      uVar7 = 0;
      do {
        iVar2 = param_1 + uVar7 * 10;
        if (*(char *)(iVar2 + 0x7956ba) == '\x01') {
          if (*(char *)(iVar2 + 0x7956c1) == cVar1) {
            if (uVar8 == 0) {
              uVar8 = 0;
              cVar10 = *(char *)(iVar2 + 0x7956c2);
              uVar6 = 1;
LAB_000a2264:
              local_68[uVar8] = cVar10;
              uVar8 = uVar6;
            }
            else {
              cVar10 = *(char *)(iVar2 + 0x7956c2);
              if (local_68[0] != cVar10) {
                pcVar3 = local_68;
                uVar6 = 0;
                do {
                  uVar6 = uVar6 + 1 & 0xff;
                  if (uVar6 == uVar8) {
                    uVar6 = uVar8 + 1 & 0xff;
                    goto LAB_000a2264;
                  }
                  pcVar3 = pcVar3 + 1;
                } while (*pcVar3 != cVar10);
              }
            }
            *(undefined1 *)(param_1 + uVar7 * 10 + 0x7956ba) = 0;
          }
          if (0 < DebugLevel) {
            printk("ACT - BuildIntolerantChannelRep , Total Channel number = %d\n",uVar8);
          }
        }
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < *(byte *)(param_1 + 0x7956b8));
      if (uVar8 != 0) {
        puVar5 = (undefined1 *)(param_2 + iVar4);
        *puVar5 = 0x49;
        puVar5[2] = cVar1;
        puVar5[1] = (char)uVar8 + '\x01';
        RTMPMoveMemory(param_2 + iVar4 + 3,local_68,uVar8);
        iVar4 = uVar8 + iVar4 + 3;
        local_7c = local_7c + 3 + uVar8;
      }
    }
    if (pcVar9 == &local_69) {
      if (0 < DebugLevel) {
        printk("ACT-BuildIntolerantChannelRep(Size=%ld)\n",local_7c);
      }
      hex_dump("ACT-pDestMsg",param_2,local_7c);
      return local_7c;
    }
  } while( true );
}

