// module: mt7915.ko
// function: set_txbf_prof_tag_ru_range @ 0xe7564
// size: 236 bytes
//

undefined4 set_txbf_prof_tag_ru_range(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 local_1a;
  
  iVar4 = 0;
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_1a = 0;
  iVar3 = rstrtok(param_2,&_LC232);
  if (iVar3 != 0) {
    do {
      uVar1 = os_str_toul(iVar3,0,10);
      *(undefined1 *)((int)&local_1a + iVar4) = uVar1;
      iVar3 = rstrtok(0,&_LC232);
      iVar4 = iVar4 + 1;
    } while (iVar3 != 0);
    if (iVar4 == 2) {
      uVar1 = local_1a._1_1_;
      if (*(code **)(iVar2 + 0x158) != (code *)0x0) {
        (**(code **)(iVar2 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x14,(undefined1)local_1a);
        (**(code **)(iVar2 + 0x158))(*(undefined4 *)(param_1 + 0xa797a0),0x15,uVar1);
        return 1;
      }
      return 0;
    }
  }
  if (-1 < DebugLevel) {
    printk("Error: Un-expected format!\n");
  }
  return 0;
}

