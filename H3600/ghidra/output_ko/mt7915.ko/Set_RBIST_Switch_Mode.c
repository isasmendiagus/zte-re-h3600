// module: mt7915.ko
// function: Set_RBIST_Switch_Mode @ 0xeab6c
// size: 184 bytes
//

undefined4 Set_RBIST_Switch_Mode(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = net_ad_wrap_service();
  uVar3 = *(uint *)(iVar2 + 0x4e0);
  cVar1 = simple_strtol(param_2,0,10);
  if (cVar1 == '\0') {
    iVar2 = net_ad_wrap_service(param_1);
LAB_000eabc4:
    *(uint *)(iVar2 + 0x4e0) = uVar3 & 0xfffffdff;
    MtCmdRfTestSwitchMode(param_1,0,0,8);
    return 1;
  }
  if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
    iVar2 = net_ad_wrap_service(param_1);
    uVar3 = uVar3 | 0x200;
  }
  else {
    if (cVar1 != '\x04') {
      iVar2 = net_ad_wrap_service(param_1);
      goto LAB_000eabc4;
    }
    iVar2 = net_ad_wrap_service(param_1);
    uVar3 = uVar3 & 0xfffffdff;
  }
  *(uint *)(iVar2 + 0x4e0) = uVar3;
  MtCmdRfTestSwitchMode(param_1,cVar1,0,8);
  return 1;
}

