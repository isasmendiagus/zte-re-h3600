// module: mt7915.ko
// function: MtCmdSetVoWDRRCtrlRsp @ 0x1ac7d4
// size: 136 bytes
//

void MtCmdSetVoWDRRCtrlRsp(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  puVar2 = *(undefined4 **)(param_1 + 0xc);
  uVar3 = param_2[1];
  uVar5 = param_2[2];
  uVar4 = param_2[3];
  *puVar2 = *param_2;
  iVar1 = DebugLevel;
  puVar2[1] = uVar3;
  puVar2[2] = uVar5;
  puVar2[3] = uVar4;
  puVar2[4] = param_2[4];
  if (iVar1 < 4) {
    return;
  }
  printk("%s: u4CtrlFieldID = 0x%x, ExtCmd (0x%02x)\n","MtCmdSetVoWDRRCtrlRsp",*param_2,
         *(undefined1 *)(param_1 + 3));
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: ucCtrlStatus = 0x%x\n","MtCmdSetVoWDRRCtrlRsp",*(undefined1 *)((int)param_2 + 5),
         param_4);
  return;
}

