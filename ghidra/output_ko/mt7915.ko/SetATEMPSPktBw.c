// module: mt7915.ko
// function: SetATEMPSPktBw @ 0x260d68
// size: 8 bytes
//

undefined4 SetATEMPSPktBw(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int aiStack_2c [2];
  
  iVar7 = *(int *)(param_1 + 0xa39fd4);
  aiStack_2c[0] = 0;
  if (0 < DebugLevel) {
    printk("%s: Parm = %s\n","SetATEMPSParam",param_2);
  }
  iVar2 = rstrtok(param_2,&_LC2);
  if (iVar2 != 0) {
    if (0 < DebugLevel) {
      printk("value:%s, arg:%s, tmp:%s\n",iVar2,param_2,param_2);
    }
    iVar2 = simple_strtol(iVar2,0,10);
    if (iVar2 != 0) {
      iVar3 = os_alloc_mem(param_1,aiStack_2c,iVar2 * 4);
      if (iVar3 == 0) {
        iVar3 = rstrtok(0,&_LC2);
        if (iVar3 != 0) {
          iVar5 = 0;
          iVar6 = 0;
          do {
            iVar1 = aiStack_2c[0];
            uVar4 = simple_strtol(iVar3,0,10);
            iVar6 = iVar6 + 1;
            *(undefined4 *)(iVar1 + iVar5) = uVar4;
            iVar3 = rstrtok(0,&_LC2);
            iVar5 = iVar5 + 4;
            if (iVar3 == 0) {
              if (iVar2 != iVar6) goto LAB_00260550;
              break;
            }
          } while (iVar2 != iVar6);
          (**(code **)(iVar7 + 0xcc))(param_1,9,iVar2,aiStack_2c[0]);
          if (aiStack_2c[0] == 0) {
            return 1;
          }
          os_free_mem(aiStack_2c[0]);
          return 1;
        }
LAB_00260550:
        if (-1 < DebugLevel) {
          printk("%s: Number of items %d is not matched with number of params %d\n","SetATEMPSParam"
                 ,iVar2);
        }
        if (aiStack_2c[0] != 0) {
          os_free_mem();
        }
      }
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Mem allocate fail\n","SetATEMPSParam");
    }
  }
  if (-1 < DebugLevel) {
    printk("%s: [%u]Format: num_itmes:param1:param2:...\n","SetATEMPSParam",9);
  }
  return 0;
}

