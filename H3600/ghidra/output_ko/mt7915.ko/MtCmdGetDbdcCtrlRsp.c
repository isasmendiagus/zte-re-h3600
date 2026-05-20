// module: mt7915.ko
// function: MtCmdGetDbdcCtrlRsp @ 0x1aba08
// size: 148 bytes
//

void MtCmdGetDbdcCtrlRsp(int param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  puVar3 = *(undefined1 **)(param_1 + 0xc);
  if (3 < DebugLevel) {
    printk("Enable=%d,TotalNum=%d\n",*param_2,param_2[1],param_4,param_4);
  }
  *(uint *)(puVar3 + 4) = (uint)(byte)param_2[1];
  *puVar3 = *param_2;
  if (param_2[1] == '\0') {
    return;
  }
  iVar1 = 0;
  puVar2 = param_2;
  do {
    iVar1 = iVar1 + 1;
    puVar3[9] = puVar2[5];
    puVar3[8] = puVar2[4];
    puVar3[10] = puVar2[6];
    puVar2 = puVar2 + 4;
    puVar3 = puVar3 + 3;
  } while (iVar1 < (int)(uint)(byte)param_2[1]);
  return;
}

