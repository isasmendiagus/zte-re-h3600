// module: mt7915.ko
// function: MtAsicSetDbdcCtrlByFw @ 0x19972c
// size: 4 bytes
//

undefined4 MtAsicSetDbdcCtrlByFw(undefined4 param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  int iVar8;
  undefined1 uStack_11c;
  undefined1 uStack_11b;
  undefined1 auStack_118 [256];
  
  os_zero_mem(&uStack_11c,0x104);
  iVar3 = AndesAllocCmdMsg(param_1,0x104);
  if (iVar3 == 0) {
    uVar7 = 3;
  }
  else {
    AndesInitCmdMsg(iVar3,0x45ed0000,0x8000f,0,0,EventExtCmdResult);
    iVar8 = *(int *)(param_2 + 4);
    uStack_11c = *param_2;
    uStack_11b = (undefined1)iVar8;
    if (iVar8 != 0) {
      puVar4 = &uStack_11c;
      puVar5 = param_2;
      do {
        puVar6 = puVar5 + 3;
        uVar1 = puVar5[8];
        uVar2 = puVar5[9];
        puVar4[6] = puVar5[10];
        puVar4[4] = uVar1;
        puVar4[5] = uVar2;
        puVar4 = puVar4 + 4;
        puVar5 = puVar6;
      } while (puVar6 != param_2 + iVar8 * 3);
    }
    AndesAppendCmdMsg(iVar3,&uStack_11c,0x104);
    uVar7 = chip_cmd_tx(param_1,iVar3);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetDbdcCtrl",uVar7);
  }
  return uVar7;
}

