// module: mt7915.ko
// function: AndesCtrlInit @ 0x1a4b54
// size: 276 bytes
//

void AndesCtrlInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + 0xa7849c;
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0,param_3,param_4,param_4);
  if (iVar1 == 0) {
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xfeffffff;
    *(undefined1 *)(param_1 + 0xa7849c) = 0;
    tasklet_init(param_1 + 0xa784a4,AndesCmdMsgBh,param_1);
    *(undefined4 *)(param_1 + 0xa784b8) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784bc);
    *(undefined4 *)(param_1 + 0xa784c4) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784c8);
    *(undefined4 *)(param_1 + 0xa784d0) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784d4);
    *(undefined4 *)(param_1 + 0xa784dc) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784e0);
    *(undefined4 *)(param_1 + 0xa784e8) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784ec);
    *(undefined4 *)(param_1 + 0xa784f4) = 0;
    FUN_001a4604(iVar2,param_1 + 0xa784f8);
    *(undefined4 *)(param_1 + 0xa78504) = 0;
    *(undefined4 *)(param_1 + 0xa78508) = 0;
    *(undefined4 *)(param_1 + 0xa7850c) = 0;
    *(undefined4 *)(param_1 + 0xa78510) = 0;
    *(undefined4 *)(param_1 + 0xa78514) = 0;
    *(int *)(param_1 + 0xa78628) = param_1;
    hif_mcu_init(*(undefined4 *)(param_1 + 0xa797a0));
    OS_SET_BIT(0,param_1 + 0xa784a0);
  }
  *(undefined1 *)(param_1 + 0xa78518) = 0;
  *(undefined1 *)(param_1 + 0xa78519) = 0;
  *(undefined1 *)(param_1 + 0xa7851a) = 0;
  *(undefined1 *)(param_1 + 0xa7851b) = 0;
  *(undefined4 *)(param_1 + 0xa78500) = 0;
  return;
}

