// module: mt7915.ko
// function: StaRecUpdateHwAmsdu @ 0x1c306c
// size: 144 bytes
//

undefined4 StaRecUpdateHwAmsdu(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar3 = *(int *)(param_3 + 0x9c);
  local_20 = 0;
  local_1c = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar3 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_20,8);
    uVar2 = local_1c;
    local_20 = 0x8000f;
    local_1c._3_1_ = SUB41(uVar2,3);
    local_1c._0_3_ =
         CONCAT12(1,CONCAT11(*(undefined1 *)(iVar3 + 0xd06),*(undefined1 *)(iVar1 + 0x1c5)));
    AndesAppendCmdMsg(param_2,&local_20,8);
    uVar2 = 0;
  }
  return uVar2;
}

