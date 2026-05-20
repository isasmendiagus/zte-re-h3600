// module: mt7915.ko
// function: hqa_ext_cmds @ 0x26cc0c
// size: 228 bytes
//

undefined4 hqa_ext_cmds(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  if (2 < DebugLevel) {
    printk("%s: 0x%x\n","hqa_ext_cmds",uVar1);
  }
  if (uVar1 < 0x28) {
    if (*(code **)(&DAT_002a5ae8 + uVar1 * 4) != (code *)0x0) {
                    /* WARNING: Jumptable at 0x0026cc94 did not pass sanity check. */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(&DAT_002a5ae8 + uVar1 * 4))(param_1,param_2,param_3);
      return uVar2;
    }
    if (1 < DebugLevel) {
      printk("%s: cmd idx 0x%x is not supported\n","hqa_ext_cmds",uVar1);
    }
  }
  else if (1 < DebugLevel) {
    printk("%s: cmd idx 0x%x is over bounded\n","hqa_ext_cmds",uVar1);
  }
  return 0;
}

