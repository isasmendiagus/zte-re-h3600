// module: mt7915.ko
// function: MtCmdGetEdca @ 0x1b892c
// size: 324 bytes
//

undefined4 MtCmdGetEdca(undefined4 param_1,byte *param_2)

{
  byte *pbVar1;
  int iVar2;
  byte *extraout_r2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  int local_ac;
  undefined2 local_88 [2];
  byte local_84;
  uint auStack_80 [25];
  
  uVar5 = 0;
  os_zero_mem(local_88,0x68);
  iVar2 = AndesAllocCmdMsg(param_1,0x68);
  if (iVar2 == 0) {
    uVar6 = 3;
  }
  else {
    local_ac = (uint)(ushort)((ushort)*param_2 * 8 + 8) << 0x10;
    local_ac = CONCAT31(local_ac._1_3_,7);
    AndesInitCmdMsg(iVar2,0x3ced0000,local_ac,0,param_2,MtCmdGetEdcaRsp);
    local_84 = *param_2;
    uVar7 = (uint)local_84;
    pbVar3 = extraout_r2;
    if (uVar7 != 0) {
      pbVar3 = param_2;
    }
    local_88[0] = 4;
    if (uVar7 != 0) {
      do {
        pbVar1 = pbVar3 + 4;
        uVar4 = uVar5 + 1;
        pbVar3 = pbVar3 + 8;
        auStack_80[uVar5] = (uint)*pbVar1;
        uVar5 = uVar4;
      } while (uVar4 != uVar7);
    }
    AndesAppendCmdMsg(iVar2,local_88,0x68);
    uVar6 = chip_cmd_tx(param_1,iVar2);
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetEdca",uVar6);
  }
  return uVar6;
}

