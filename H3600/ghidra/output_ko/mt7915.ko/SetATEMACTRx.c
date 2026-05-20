// module: mt7915.ko
// function: SetATEMACTRx @ 0x260bb8
// size: 204 bytes
//

bool SetATEMACTRx(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uStack_28;
  uint local_24 [4];
  
  puVar7 = &uStack_28;
  iVar2 = net_ad_wrap_service();
  uVar1 = *(undefined1 *)(iVar2 + 0x4cc);
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATEMACTRx",param_2);
  }
  iVar6 = 0;
  local_24[0] = 0;
  local_24[1] = 0;
  iVar2 = rstrtok(param_2,&_LC2);
  if (iVar2 == 0) {
    uVar4 = 0;
    uVar5 = 0;
  }
  else {
    do {
      puVar7 = puVar7 + 1;
      uVar3 = simple_strtol(iVar2,0,0x10);
      iVar6 = iVar6 + 1;
      *puVar7 = uVar3;
      iVar2 = rstrtok(0,&_LC2);
    } while (iVar6 != 3 && iVar2 != 0);
    uVar5 = local_24[1] & 0xff;
    uVar4 = local_24[0];
  }
  iVar2 = MtATESetMacTxRx(param_1,uVar4,uVar5,uVar1);
  return iVar2 == 0;
}

