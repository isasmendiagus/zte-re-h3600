// module: mt7915.ko
// function: MtCmdGetDbdcCtrl @ 0x1b836c
// size: 328 bytes
//

undefined4 MtCmdGetDbdcCtrl(undefined4 param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  int iVar7;
  int local_140;
  undefined1 local_11c [260];
  
  os_zero_mem(local_11c,0x104);
  iVar3 = AndesAllocCmdMsg(param_1,0x104);
  if (iVar3 == 0) {
    uVar6 = 3;
  }
  else {
    local_140 = (uint)(ushort)(((short)*(undefined4 *)(param_2 + 4) + 1) * 4) << 0x10;
    local_140 = CONCAT31(local_140._1_3_,7);
    AndesInitCmdMsg(iVar3,0x45ed0000,local_140,0,param_2,MtCmdGetDbdcCtrlRsp);
    iVar7 = *(int *)(param_2 + 4);
    local_11c[0] = *param_2;
    local_11c[1] = (undefined1)iVar7;
    if (iVar7 != 0) {
      puVar4 = local_11c;
      do {
        puVar1 = param_2 + 8;
        puVar5 = puVar4 + 4;
        uVar2 = param_2[9];
        param_2 = param_2 + 3;
        *puVar5 = *puVar1;
        puVar4[5] = uVar2;
        puVar4 = puVar5;
      } while (puVar5 != local_11c + iVar7 * 4);
    }
    AndesAppendCmdMsg(iVar3,local_11c,0x104);
    uVar6 = chip_cmd_tx(param_1,iVar3);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetDbdcCtrl",uVar6);
  }
  return uVar6;
}

