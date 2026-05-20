// module: mt7915.ko
// function: RtmpPhyNetDevMainCreate @ 0x13de54
// size: 152 bytes
//

void RtmpPhyNetDevMainCreate(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 0;
  iVar1 = load_dev_l1profile();
  if (iVar1 == 0) {
    if (3 < DebugLevel) {
      printk("load l1profile succeed!\n");
    }
  }
  else if (1 < DebugLevel) {
    printk("load l1profile failed!\n");
  }
  uVar2 = get_dev_name_prefix(param_1,0x100);
  RtmpOSNetDevCreate(0,&local_c,0x100,0,0x10,uVar2,0);
  return;
}

