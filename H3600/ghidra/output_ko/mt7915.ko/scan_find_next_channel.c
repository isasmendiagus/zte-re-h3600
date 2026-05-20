// module: mt7915.ko
// function: scan_find_next_channel @ 0x143f90
// size: 516 bytes
//

uint scan_find_next_channel(undefined4 param_1,char *param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  bool bVar7;
  bool bVar8;
  
  iVar5 = *(int *)(param_2 + 0xaf5d0);
  if (iVar5 == 0) {
    printk(&_LC24,0x53a);
    dump_stack();
    iVar5 = *(int *)(param_2 + 0xaf5d0);
    if (iVar5 == 0) {
      return 0;
    }
  }
  cVar1 = *param_2;
  if ((*(char *)(iVar5 + 0xbb4) != '\0') && (*(int *)(param_2 + 0x90) == 3)) {
    param_3 = (uint)*(byte *)(iVar5 + 0xbb6);
  }
  if ((*(char *)(iVar5 + 0xbc8) == '\0') || (*(char *)(iVar5 + 0xbc9) != '\0')) {
    bVar7 = cVar1 != '\0';
    if (cVar1 != '\x01') {
      bVar7 = 1 < (byte)(cVar1 + 0x7fU);
    }
    if (bVar7 && (cVar1 != '\x01' && (byte)(cVar1 + 0x7fU) != 2)) {
      if ((param_2[0x17c] == '\x01') && (*(int *)(param_2 + 0x90) == 3)) {
        param_3 = (uint)*(byte *)(iVar5 + 0xbb6);
      }
LAB_00144014:
      do {
        while( true ) {
          if (param_3 == 0) {
            param_3 = FirstChannel(param_1,iVar5);
          }
          else {
            param_3 = NextChannel(param_1,param_2,param_3,iVar5);
          }
          if (param_3 == 0) {
            return 0;
          }
          if ((byte)param_2[0x79] == 0) break;
          pbVar6 = *(byte **)(param_2 + 0x7c);
          if (*pbVar6 != param_3) {
            pbVar3 = pbVar6 + (byte)param_2[0x79];
            do {
              pbVar6 = pbVar6 + 1;
              if (pbVar6 == pbVar3) goto LAB_00144070;
            } while (*pbVar6 != param_3);
          }
          if (0 < DebugLevel) {
            printk("Skip channel %d\n",param_3);
          }
        }
LAB_00144070:
        if (param_2[0x80] == '\0') {
          uVar2 = param_3 + 0x78 & 0xff;
          uVar4 = param_3 - 0x34 & 0xff;
          bVar8 = 0x3b < uVar4;
          bVar7 = uVar4 == 0x3c;
          if (0x3c < uVar4) {
            bVar8 = 7 < uVar2;
            bVar7 = uVar2 == 8;
          }
          if (!bVar8 || bVar7) {
            if (0 < DebugLevel) {
              printk("Skip DFS channel %d\n",param_3);
            }
            goto LAB_00144014;
          }
        }
        if ((0xe < param_3 && (*(ushort *)(*(int *)(param_2 + 0xaf5d0) + 0x18) & 0xb1) != 0) ||
           (param_3 < 0xf && (*(ushort *)(*(int *)(param_2 + 0xaf5d0) + 0x18) & 0x4e) != 0)) {
          return param_3;
        }
      } while( true );
    }
  }
  else {
    *(undefined1 *)(iVar5 + 0xbc9) = 1;
  }
  return 0;
}

