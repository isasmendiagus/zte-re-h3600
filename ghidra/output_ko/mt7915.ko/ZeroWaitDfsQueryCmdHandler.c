// module: mt7915.ko
// function: ZeroWaitDfsQueryCmdHandler @ 0x2376e0
// size: 336 bytes
//

undefined4 ZeroWaitDfsQueryCmdHandler(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  uint local_120 [3];
  byte local_114;
  byte local_113 [5];
  ushort auStack_10e [121];
  
  os_zero_mem(&local_114,0xf4);
  if (local_114 == 0x14) {
    FUN_002338fc(param_1,&local_114);
  }
  else if (local_114 == 0x15) {
    DfsProvideNopOfChList(param_1,&local_114);
    iVar5 = 0;
    pbVar6 = &local_114;
    while( true ) {
      if (0 < DebugLevel) {
        printk("[%s]: band index - %d\n","ZeroWaitDfsQueryNopOfChList",iVar5);
      }
      pbVar6 = pbVar6 + 1;
      uVar2 = (uint)*pbVar6;
      if (uVar2 != 0) {
        uVar4 = 0;
        do {
          if (0 < DebugLevel) {
            iVar1 = (iVar5 * 0x1e + uVar4) * 4;
            local_120[0] = (uint)*(ushort *)(local_113 + iVar1 + 5);
            printk("NopReportChList[%d].Channel = %d, Bw = %d, NOP = %d\n",uVar4,
                   local_113[iVar1 + 3],local_113[iVar1 + 4]);
            uVar2 = (uint)*pbVar6;
          }
          uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < uVar2);
      }
      if (iVar5 == 1) break;
      iVar5 = 1;
    }
  }
  uVar2 = *(uint *)(param_2 + 0x10);
  *(undefined2 *)(param_2 + 0x14) = 0xf4;
  uVar4 = *(uint *)(((uint)local_120 & 0xffffe000) + 8);
  if (uVar2 < 0xffffff0c && uVar2 + 0xf4 <= uVar4) {
    uVar4 = 0;
  }
  if (uVar4 == 0) {
    iVar5 = __copy_to_user(uVar2,&local_114);
    if (iVar5 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0xfffffff2;
    }
    return uVar3;
  }
  return 0xfffffff2;
}

