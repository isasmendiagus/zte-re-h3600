// module: mt7915.ko
// function: MtAsicDelWcidTabByFw @ 0x19800c
// size: 196 bytes
//

void MtAsicDelWcidTabByFw(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((2 < DebugLevel) && (printk("%s, --->\n","MtAsicDelWcidTabByFw"), 2 < DebugLevel)) {
    printk("%s, wcid_idx(%d)\n","MtAsicDelWcidTabByFw",param_2);
  }
  if (param_2 == 0x7fff) {
    param_2 = 0;
    uVar1 = 4;
  }
  else {
    uVar1 = 1;
  }
  CmdExtWtblUpdate(param_1,param_2,uVar1,0,0);
  if (2 < DebugLevel) {
    printk("%s, <---\n","MtAsicDelWcidTabByFw");
    return;
  }
  return;
}

