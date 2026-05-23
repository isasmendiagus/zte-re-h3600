// module: mt7915.ko
// function: Set_PwrConstraint @ 0x14059c
// size: 400 bytes
//

undefined4 Set_PwrConstraint(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [4];
  
  uStack_28 = 0x14063204;
  local_2c = 0x46016400;
  uStack_24 = 0x50d0a0a;
  cVar3 = os_str_tol(param_2,0,10,auStack_20);
  cVar4 = GetRegulatoryMaxTxPwr(param_1,*(undefined1 *)(*(int *)(param_1 + 0xa1d28) + 0x1a));
  uVar5 = RTMP_GetTxPwr(param_1,*(undefined2 *)(param_1 + 0xa1ddc),
                        *(undefined1 *)(*(int *)(param_1 + 0xa1d28) + 0x1a));
  bVar1 = *(byte *)(param_1 + 0x794cd8);
  cVar8 = (char)uVar5 - (cVar4 - cVar3);
  if (bVar1 < 0x5b) {
    if (bVar1 < 0x3d) {
      if (bVar1 < 0x1f) {
        if (bVar1 < 0x10) {
          if (bVar1 < 10) {
            cVar8 = cVar8 + '\f';
          }
          else {
            cVar8 = cVar8 + '\t';
          }
        }
        else {
          cVar8 = cVar8 + '\x06';
        }
      }
      else {
        cVar8 = cVar8 + '\x03';
      }
    }
    else {
      cVar8 = cVar8 + '\x01';
    }
  }
  iVar9 = (int)cVar8;
  if (0 < DebugLevel) {
    printk("MaxTxPwr=%d, CurTxPwr=%d, DaltaPwr=%d\n",(int)(char)(cVar4 - cVar3),uVar5,iVar9);
  }
  if (iVar9 < (char)local_2c) {
    iVar7 = 0;
  }
  else {
    iVar6 = 1;
    while( true ) {
      iVar7 = iVar6 * 2;
      iVar6 = iVar6 + 1;
      if (iVar9 < *(char *)((int)&local_2c + iVar7)) break;
      if (iVar6 == 6) {
        if (-1 < DebugLevel) {
          printk("Power constraint value be in range from 0 to 13dB\n");
        }
        return 1;
      }
    }
  }
  uVar2 = *(undefined1 *)((int)&local_2c + iVar7 + 1);
  *(char *)(param_1 + 0x795043) = cVar3;
  *(undefined1 *)(param_1 + 0x794cd8) = uVar2;
  return 1;
}

