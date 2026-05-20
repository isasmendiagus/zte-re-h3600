// module: mt7915.ko
// function: set_vow_near_far_th @ 0x44734
// size: 152 bytes
//

undefined4 set_vow_near_far_th(int param_1,char *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined2 local_10 [2];
  undefined2 local_c [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",local_10,local_c);
  if (uVar1 < 2) {
    uVar2 = 0;
  }
  else {
    bVar3 = DebugLevel < 0;
    *(undefined2 *)(param_1 + 0xa7a314) = local_10[0];
    *(undefined2 *)(param_1 + 0xa7a316) = local_c[0];
    if (bVar3) {
      uVar2 = 1;
    }
    else {
      printk("%s: set slow_th %u, fast_th %d.\n","set_vow_near_far_th");
      uVar2 = 1;
    }
  }
  return uVar2;
}

