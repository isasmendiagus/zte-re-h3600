// module: mt7915.ko
// function: set_fgi_and_ltf_profile @ 0x4032c
// size: 200 bytes
//

undefined4 set_fgi_and_ltf_profile(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  
  if (2 < DebugLevel) {
    printk("%s:: enter\n","set_fgi_and_ltf_profile");
  }
  iVar1 = DebugLevel;
  if (param_2 == 0) {
    uVar2 = 0xfffffff2;
  }
  else {
    if (param_3 == 0) {
      uVar3 = 0;
    }
    else if (param_3 == 800) {
      uVar3 = 1;
    }
    else if (param_3 == 0x640) {
      uVar3 = 2;
    }
    else {
      if (param_3 != 0xc80) {
        return 0xffffffff;
      }
      uVar3 = 3;
    }
    *(undefined1 *)(param_2 + 0x405c) = uVar3;
    if (iVar1 < 3) {
      uVar2 = 1;
    }
    else {
      printk("%s(): set target_gi(%d)\n","set_fgi_and_ltf_profile");
      uVar2 = 1;
    }
  }
  return uVar2;
}

