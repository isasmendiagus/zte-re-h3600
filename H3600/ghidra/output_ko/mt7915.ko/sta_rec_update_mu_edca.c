// module: mt7915.ko
// function: sta_rec_update_mu_edca @ 0x1c2d60
// size: 136 bytes
//

undefined4 sta_rec_update_mu_edca(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 local_34;
  undefined2 local_32;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  os_zero_mem(&local_34,0x24);
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    local_30 = *(undefined4 *)(iVar2 + 0x1479);
    uStack_2c = *(undefined4 *)(iVar2 + 0x147d);
    uStack_28 = *(undefined4 *)(iVar2 + 0x1481);
    uStack_24 = *(undefined4 *)(iVar2 + 0x1485);
    local_32 = 0x24;
    local_34 = 0x13;
    local_20 = *(undefined4 *)(iVar2 + 0x1489);
    uStack_1c = *(undefined4 *)(iVar2 + 0x148d);
    uStack_18 = *(undefined4 *)(iVar2 + 0x1491);
    uStack_14 = *(undefined4 *)(iVar2 + 0x1495);
    AndesAppendCmdMsg(param_2,&local_34,0x24);
    uVar1 = 0;
  }
  return uVar1;
}

