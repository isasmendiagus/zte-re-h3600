// module: mt7915.ko
// function: RTMPTkipCompareMICValue @ 0x117620
// size: 316 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4
RTMPTkipCompareMICValue
          (int param_1,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4,
          undefined4 param_5,byte param_6,int param_7)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined1 local_34 [4];
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar3 = param_1 + 0xa39f4c;
  local_34._1_3_ = 0;
  local_34[0] = param_6;
  RTMPTkipSetMICKey(iVar3,param_5);
  puVar4 = param_3;
  do {
    puVar6 = puVar4 + 1;
    RTMPTkipAppendByte(iVar3,*puVar4);
    puVar4 = puVar6;
  } while (puVar6 != param_3 + 6);
  puVar4 = param_4;
  do {
    puVar6 = puVar4 + 1;
    RTMPTkipAppendByte(iVar3,*puVar4);
    puVar4 = puVar6;
  } while (puVar6 != param_4 + 6);
  puVar5 = (undefined4 *)local_34;
  RTMPTkipAppendByte(iVar3,param_6);
  while (puVar4 = param_2, iVar1 = param_7, puVar5 != (undefined4 *)((int)local_34 + 3)) {
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    RTMPTkipAppendByte(iVar3,*(undefined1 *)puVar5);
  }
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    RTMPTkipAppendByte(iVar3,*puVar4);
    puVar4 = puVar4 + 1;
  }
  local_30 = *(undefined4 *)(param_2 + param_7);
  uStack_2c = *(undefined4 *)((int)(param_2 + param_7) + 4);
  RTMPTkipGetMIC(iVar3);
  iVar3 = memcmp((void *)(param_1 + 0xa39f7c),&local_30,8);
  if (iVar3 == 0) {
    uVar2 = 1;
  }
  else if (DebugLevel < 0) {
    uVar2 = 0;
  }
  else {
    printk("RTMPTkipCompareMICValue(): TKIP MIC Error !\n");
    uVar2 = 0;
  }
  return uVar2;
}

