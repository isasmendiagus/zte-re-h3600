// module: mt7915.ko
// function: MtAsicGetDbdcCtrlByFw @ 0x19962c
// size: 256 bytes
//

void MtAsicGetDbdcCtrlByFw(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  *(undefined1 *)(param_2 + 8) = 7;
  *(undefined1 *)(param_2 + 0xb) = 5;
  *(undefined4 *)(param_2 + 4) = 0;
  *(undefined1 *)(param_2 + 9) = 0;
  *(undefined1 *)(param_2 + 0xc) = 0;
  *(undefined1 *)(param_2 + 0xf) = 0;
  *(undefined1 *)(param_2 + 0x17) = 0;
  *(undefined1 *)(param_2 + 0x18) = 0;
  *(undefined1 *)(param_2 + 0x1a) = 0;
  *(undefined1 *)(param_2 + 0x1d) = 0;
  *(undefined1 *)(param_2 + 0x20) = 0;
  *(undefined1 *)(param_2 + 0x24) = 0;
  *(undefined1 *)(param_2 + 0xe) = 6;
  *(undefined1 *)(param_2 + 0x11) = 6;
  *(undefined1 *)(param_2 + 0x14) = 6;
  *(undefined1 *)(param_2 + 0x12) = 1;
  *(undefined1 *)(param_2 + 0x1b) = 1;
  *(undefined1 *)(param_2 + 0x23) = 1;
  *(undefined1 *)(param_2 + 0x26) = 1;
  *(undefined1 *)(param_2 + 0x27) = 1;
  *(undefined1 *)(param_2 + 0x15) = 2;
  *(undefined1 *)(param_2 + 0x1e) = 2;
  *(undefined1 *)(param_2 + 0x21) = 3;
  iVar2 = param_2;
  do {
    *(char *)(iVar2 + 0x2a) = (char)iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)(iVar2 + 0x29) = 3;
    iVar2 = iVar2 + 3;
  } while (iVar1 != 0xf);
  iVar1 = 0;
  iVar2 = param_2;
  do {
    *(char *)(iVar2 + 0x57) = (char)iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)(iVar2 + 0x56) = 2;
    iVar2 = iVar2 + 3;
  } while (iVar1 != 5);
  iVar1 = 0;
  iVar2 = param_2;
  do {
    *(char *)(iVar2 + 0x66) = (char)iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)(iVar2 + 0x65) = 4;
    iVar2 = iVar2 + 3;
  } while (iVar1 != 0x20);
  *(undefined4 *)(param_2 + 4) = 0x3f;
  MtCmdGetDbdcCtrl(param_1,param_2);
  return;
}

