// module: mt7915.ko
// function: set_vow_near_far_en @ 0x446b4
// size: 124 bytes
//

undefined4 set_vow_near_far_en(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined1 local_14 [8];
  
  if ((param_2 == (char *)0x0) || (iVar1 = sscanf(param_2,"%u",local_14), iVar1 != 1)) {
    uVar2 = 0;
  }
  else {
    bVar3 = -1 < DebugLevel;
    *(undefined1 *)(param_1 + 0xa7a312) = local_14[0];
    uVar2 = 1;
    if (bVar3) {
      printk("%s: set %u.\n","set_vow_near_far_en");
    }
  }
  return uVar2;
}

