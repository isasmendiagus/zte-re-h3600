// module: mt7915.ko
// function: DfsGetSysParameters @ 0x22ffb0
// size: 200 bytes
//

void DfsGetSysParameters(int param_1,int param_2,char param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  bool bVar5;
  
  if (param_2 == 0) {
    return;
  }
  iVar3 = *(int *)(param_2 + 0x3fe4);
  if (iVar3 != 0) {
    bVar1 = *(byte *)(param_2 + 0x1a);
    iVar2 = HcGetBandByWdev(param_2);
    hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar2);
    if (param_4 == 6) {
      bVar4 = param_3 - 2;
      bVar5 = bVar4 <= bVar1;
      *(byte *)(param_1 + 0x795132) = bVar1;
      if (bVar5) {
        *(byte *)(param_1 + 0x795130) = bVar4;
        bVar4 = bVar1;
      }
      else {
        *(byte *)(param_1 + 0x795130) = bVar1;
      }
      *(bool *)(param_1 + 0x795133) = bVar5;
      *(byte *)(param_1 + 0x795131) = bVar4;
    }
    else {
      *(byte *)(param_1 + 0x795132) = bVar1;
      *(char *)(param_1 + 0x795133) = (char)iVar2;
      *(byte *)(param_1 + iVar2 + 0x795130) = bVar1;
    }
    *(char *)(param_1 + 0x795000 + iVar2 + 0x134) = (char)param_4;
    *(undefined1 *)(param_1 + 0x795000 + iVar2 * 0x20 + 0x2f0) = *(undefined1 *)(iVar3 + 4);
    *(undefined1 *)(param_1 + 0x7953e0) = *(undefined1 *)(param_1 + 0x795074);
    return;
  }
  return;
}

