// module: mt7915.ko
// function: Show_BaTable_Proc @ 0xe09fc
// size: 244 bytes
//

undefined4
Show_BaTable_Proc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = rstrtok(param_2,&_LC232,param_3,param_4,param_4);
  if (iVar2 != 0) {
    iVar2 = os_str_toul(iVar2,0,10);
    if (iVar2 == 1) {
      ba_reordering_resource_dump_all(param_1);
      goto LAB_000e0a40;
    }
    if (iVar2 != 0) {
      if (iVar2 == 2) {
        while (iVar2 = rstrtok(0,&_LC232), iVar2 != 0) {
          uVar1 = os_str_toul(iVar2,0,10);
          ba_reodering_resource_dump(param_1,uVar1);
        }
      }
      goto LAB_000e0a40;
    }
    while (iVar2 = rstrtok(0,&_LC232), iVar2 != 0) {
      uVar3 = os_str_toul(iVar2,0,10);
      ba_resource_dump_all(param_1,uVar3);
    }
  }
  ba_resource_dump_all(param_1,0);
LAB_000e0a40:
  if (0 < DebugLevel) {
    printk("Dump BaTable info arg = %s\n",param_2);
  }
  return 1;
}

