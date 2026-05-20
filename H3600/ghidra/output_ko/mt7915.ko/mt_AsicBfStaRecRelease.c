// module: mt7915.ko
// function: mt_AsicBfStaRecRelease @ 0x86710
// size: 288 bytes
//

undefined4 mt_AsicBfStaRecRelease(int param_1,undefined1 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_1c0 [204];
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8 [36];
  int local_58;
  
  iVar1 = param_1 + param_3 * 0x14c0;
  os_zero_mem(iVar1 + 0xa295a,0x2a);
  *(undefined2 *)(iVar1 + 0xa295a) = 0xffff;
  os_zero_mem(&local_f4,0xd4);
  if (*(int *)(iVar1 + 0xa1d28) == 0) {
    printk(&_LC24,0x463);
    dump_stack();
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
    local_f4 = CONCAT31(local_f4._1_3_,param_2);
    local_e8[0] = 0x10;
    local_f4 = CONCAT22((short)param_3,(undefined2)local_f4);
    local_f0 = CONCAT31(CONCAT21(local_f0._2_2_,*(undefined1 *)(*(int *)(iVar1 + 0xa1d28) + 0x29)),1
                       );
    local_ec = 0;
    local_58 = param_1 + param_3 * 0x14c0 + 0xa1d20;
    memcpy(auStack_1c0,local_e8,200);
    iVar1 = CmdExtStaRecUpdate(param_1,local_f4,local_f0,local_ec);
    if (iVar1 == 0) {
      uVar2 = 1;
    }
    else if (DebugLevel < 0) {
      uVar2 = 0;
    }
    else {
      printk("Something wrong in the BF STA Rec update!!\n");
    }
  }
  return uVar2;
}

