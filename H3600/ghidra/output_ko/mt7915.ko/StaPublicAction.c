// module: mt7915.ko
// function: StaPublicAction @ 0xa1fc0
// size: 232 bytes
//

void StaPublicAction(int param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 auStack_39 [41];
  
  iVar1 = GetStaCfgByWdev(param_1,param_3);
  if (iVar1 == 0) {
    printk(&_LC15,0x23c);
    dump_stack();
    return;
  }
  if (2 < DebugLevel) {
    printk("ACTION - StaPeerPublicAction  Bss2040Coexist = %x\n",*param_2);
  }
  if (((*param_2 & 1) != 0) && ((*(uint *)(param_1 + 0x795124) & 0x40000) != 0)) {
    *(byte *)(param_1 + 0x7956b5) = *(byte *)(param_1 + 0x7956b5) & 0xf9 | 1;
    TriEventInit(param_1);
    ScanParmFill(param_1,auStack_39,ZeroSsid,0,2,4);
    cntl_scan_request(param_3,auStack_39);
    return;
  }
  return;
}

