// module: mt7915.ko
// function: mt_agent_set_ctrl_band @ 0x246a8c
// size: 60 bytes
//

undefined4 mt_agent_set_ctrl_band(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = _kstrtol(param_2,10);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x4cc) = 0;
    uVar2 = 0;
  }
  else {
    uVar2 = 0x104;
  }
  return uVar2;
}

