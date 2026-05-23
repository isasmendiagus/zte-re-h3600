// module: mt7915.ko
// function: ComposeWPSIE @ 0xb3584
// size: 252 bytes
//

void ComposeWPSIE(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_24;
  int local_20;
  undefined2 local_1c;
  undefined1 local_1a;
  
  iVar2 = *param_3;
  if ((*(int *)(param_2 + 0x14) != 1) || (iVar3 = *(int *)(param_2 + 4), iVar3 == 0)) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0x12e4);
  if (iVar1 < 1) {
LAB_000b3608:
    if (iVar1 == 0) goto LAB_000b3610;
  }
  else if (*(short *)(param_2 + 0xee0) != 0) {
    local_20 = 0;
    MakeOutgoingFrame(param_4 + iVar2,&local_20,*(short *)(param_2 + 0xee0),param_2 + 0xee2,
                      0xffffffff);
    iVar1 = *(int *)(param_2 + 0x12e4);
    iVar2 = iVar2 + local_20;
    goto LAB_000b3608;
  }
  if ((*(char *)(iVar3 + 0x5c0) == '\x01') && ((*(uint *)(iVar3 + 0x174) & 0xe) != 0)) {
    local_20 = 0x500005dd;
    local_1c = 0x5f2;
    local_1a = 0;
    local_24 = 0;
    MakeOutgoingFrame(param_4 + iVar2,&local_24,7,&local_20,0xffffffff);
    iVar2 = iVar2 + local_24;
  }
LAB_000b3610:
  *param_3 = iVar2;
  return;
}

