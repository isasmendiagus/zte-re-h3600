// module: mt7915.ko
// function: DynamicTxBfDisable @ 0x88df8
// size: 512 bytes
//

undefined4 DynamicTxBfDisable(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 uVar5;
  uint local_1d8 [51];
  uint local_10c;
  uint local_108;
  int local_104;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0 [36];
  int *local_60;
  
  if (2 < DebugLevel) {
    printk("[%s]\n","DynamicTxBfDisable");
  }
  if (param_2 == 0) {
    local_104 = param_1 + 0x795000;
    *(undefined1 *)(param_1 + 0x7959a6) = 0;
    local_108 = ((uint)*(byte *)(param_1 + 0x794ccd) << 0x1d) >> 0x1f;
    local_10c = (uint)*(byte *)(param_1 + 0x79599c);
    AsicTxBfeeHwCtrl(param_1,1);
  }
  else {
    local_104 = param_1 + 0x795000;
    local_108 = 0;
    local_10c = 0;
    *(byte *)(param_1 + 0x7959a6) = *(byte *)(param_1 + 0x7959a6) | 0x40;
    AsicTxBfeeHwCtrl(param_1);
  }
  if (2 < DebugLevel) {
    local_1d8[0] = (uint)*(byte *)(local_104 + 0x9a6);
    printk("[%s] fgETxBf=%d, fgITxBf=%d, ucAutoSoundingCtrl=%d\n","DynamicTxBfDisable",local_10c,
           local_108);
  }
  piVar3 = (int *)(param_1 + 0xa1d20);
  uVar5 = 0;
  for (uVar4 = 0; iVar2 = HcGetMaxStaNum(param_1), (int)uVar4 < iVar2; uVar4 = uVar4 + 1) {
    if ((*piVar3 == 2 || (*piVar3 - 0x20001U & 0xfffdffff) == 0) && (piVar3[0x3f] == 2)) {
      if (2 < DebugLevel) {
        printk("[%s] Enable/Disable BF for wlanid %d\n","DynamicTxBfDisable",uVar4);
      }
      os_zero_mem(&local_fc,0xd4);
      uVar1 = (uint)local_f8 >> 8;
      local_f4 = 0;
      local_fc = CONCAT22((short)uVar4,(undefined2)local_fc);
      *(undefined1 *)((int)piVar3 + 0xc53) = *(undefined1 *)(local_104 + 0x9a6);
      local_f8 = CONCAT31((uint3)uVar1 & 0xffff00,1);
      local_fc = CONCAT31(local_fc._1_3_,*(undefined1 *)(piVar3[2] + 0x999));
      local_f0[0] = 0x10;
      local_60 = piVar3;
      memcpy(local_1d8,local_f0,200);
      iVar2 = CmdExtStaRecUpdate(param_1,local_fc,local_f8,local_f4);
      local_1d8[0] = 0;
      if (iVar2 == 0) {
        uVar5 = 1;
      }
      local_1d8[1] = 0;
      CmdTxBfTxApplyCtrl(param_1,uVar4 & 0xffff,local_10c,local_108);
    }
    piVar3 = piVar3 + 0x530;
  }
  return uVar5;
}

