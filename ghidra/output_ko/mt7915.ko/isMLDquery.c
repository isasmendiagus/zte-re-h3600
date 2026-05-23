// module: mt7915.ko
// function: isMLDquery @ 0x242ab8
// size: 116 bytes
//

undefined4 isMLDquery(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  char local_15;
  undefined1 auStack_14 [8];
  
  local_15 = '\0';
  iVar1 = isMldPkt(param_2,param_3,&local_15,auStack_14);
  if ((iVar1 == 1) && (local_15 == -0x7e)) {
    uVar2 = 1;
    if (3 < DebugLevel) {
      printk("isMLDquery-> MLD type=0x%x MLD_LISTENER_QUERY\n");
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

