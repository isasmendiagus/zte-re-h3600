// module: mt7915.ko
// function: MtAsicSetWcidAAD_OMByFw @ 0x1980d0
// size: 192 bytes
//

void MtAsicSetWcidAAD_OMByFw(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (2 < DebugLevel) {
    printk("%s, wcid_idx(%d), value(%d)\n","MtAsicSetWcidAAD_OMByFw",param_2,param_3);
  }
  if (param_3 == 0) {
    WtblDwSet(param_1,param_2,1,2,0xfffffff7,0);
  }
  else {
    WtblDwSet(param_1,param_2,1,2,0xfffffff7,8);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, <---\n","MtAsicSetWcidAAD_OMByFw");
  return;
}

