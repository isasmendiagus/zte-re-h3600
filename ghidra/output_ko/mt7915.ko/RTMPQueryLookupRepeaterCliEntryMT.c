// module: mt7915.ko
// function: RTMPQueryLookupRepeaterCliEntryMT @ 0x81368
// size: 208 bytes
//

undefined4
RTMPQueryLookupRepeaterCliEntryMT(undefined4 param_1,undefined1 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (3 < DebugLevel) {
    printk("%s:: %02x:%02x:%02x:%02x:%02x:%02x\n","RTMPQueryLookupRepeaterCliEntryMT",*param_2,
           param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
  }
  iVar1 = RTMPLookupRepeaterCliEntry(param_1,0,param_2,param_3);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (3 < DebugLevel) {
      printk("%s:: not the repeater client\n","RTMPQueryLookupRepeaterCliEntryMT");
    }
  }
  else if (DebugLevel < 4) {
    uVar2 = 1;
  }
  else {
    printk("%s:: is the repeater client\n","RTMPQueryLookupRepeaterCliEntryMT");
    uVar2 = 1;
  }
  return uVar2;
}

