// module: mt7915.ko
// function: StaRecUpdateVhtInfo @ 0x1c323c
// size: 188 bytes
//

undefined4 StaRecUpdateVhtInfo(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 local_20;
  undefined2 local_1e;
  undefined1 auStack_1c [4];
  undefined1 auStack_18 [2];
  undefined1 auStack_16 [2];
  undefined1 local_14;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_20,0x10);
    local_1e = 0x10;
    local_20 = 10;
    os_move_mem(auStack_1c,(void *)(iVar2 + 0xd14),4);
    os_move_mem(auStack_18,(void *)(iVar2 + 0xd18),2);
    os_move_mem(auStack_16,(void *)(iVar2 + 0xd1c),2);
    if ((0x7f < *(byte *)(iVar2 + 0xbf)) && ((*(uint *)(iVar2 + 100) & 8) == 0)) {
      local_14 = wlan_config_get_vht_bw_sig(*(undefined4 *)(iVar2 + 8));
    }
    AndesAppendCmdMsg(param_2,&local_20,0x10);
    uVar1 = 0;
  }
  return uVar1;
}

