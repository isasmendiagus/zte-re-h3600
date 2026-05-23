// module: mt7915.ko
// function: twtPlannerDrvAgrtInsert @ 0x169ac8
// size: 164 bytes
//

undefined4
twtPlannerDrvAgrtInsert
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,byte param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = (uint)param_5 * 0x20 + 8;
  iVar1 = param_1 + (short)(ushort)param_5 * 0x20;
  *(undefined1 *)(param_1 + (short)(ushort)param_5 * 0x20) = 1;
  iVar5 = param_1 + iVar6;
  *(char *)(iVar1 + 2) = (char)param_2;
  *(char *)(iVar1 + 3) = (char)param_3;
  *(byte *)(iVar1 + 1) = param_5;
  uVar2 = param_4[1];
  uVar4 = param_4[2];
  uVar3 = param_4[3];
  *(undefined4 *)(param_1 + iVar6) = *param_4;
  iVar1 = DebugLevel;
  *(undefined4 *)(iVar5 + 4) = uVar2;
  *(undefined4 *)(iVar5 + 8) = uVar4;
  *(undefined4 *)(iVar5 + 0xc) = uVar3;
  uVar2 = param_4[5];
  *(undefined4 *)(iVar5 + 0x10) = param_4[4];
  *(undefined4 *)(iVar5 + 0x14) = uVar2;
  if (2 < iVar1) {
    printk("%s: ucIdx=%d, ucBssIdx=%d, ucFlowId=%d\n","twtPlannerDrvAgrtInsert",(uint)param_5,
           param_2,param_3);
  }
  return 0;
}

