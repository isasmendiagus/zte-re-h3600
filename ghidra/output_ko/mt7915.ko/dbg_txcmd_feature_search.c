// module: mt7915.ko
// function: dbg_txcmd_feature_search @ 0x28de48
// size: 396 bytes
//

undefined4 dbg_txcmd_feature_search(int *param_1,char *param_2)

{
  undefined4 uVar1;
  char *__s;
  char *pcVar2;
  uint uVar3;
  size_t __n;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  char *local_24 [2];
  
  local_24[0] = param_2;
  uVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  puVar6 = (undefined4 *)param_1[0x29f424];
  if (puVar6 == (undefined4 *)0x0) {
    os_alloc_mem(param_1,param_1 + 0x29f424,0x1f0);
    iVar4 = param_1[0x29f424];
    if (iVar4 == 0) {
      printk("%s(): allocate fail!\n","dbg_txcmd_framework_init");
    }
    else {
      os_zero_mem(iVar4,0x1f0);
      *(int **)(iVar4 + 0xc) = param_1;
      *(int *)iVar4 = iVar4;
      *(int *)(iVar4 + 4) = iVar4;
      txcmdsu_dbg_init(iVar4);
    }
    puVar6 = (undefined4 *)param_1[0x29f424];
    if (puVar6 == (undefined4 *)0x0) {
      return 0;
    }
  }
  __s = strsep(local_24,"-");
  pcVar2 = strsep(local_24,"-");
  uVar3 = simple_strtol(pcVar2,0,10);
  uVar7 = uVar3;
  printk(&_LC4,"FRAMEWORK","dbg_txcmd_feature_search",__s,uVar3);
  puVar5 = (undefined4 *)*puVar6;
  while( true ) {
    if (puVar5 == puVar6) {
      return 0;
    }
    __n = strlen(__s);
    iVar4 = strncmp(__s,(char *)(puVar5 + 2),__n);
    if (iVar4 == 0) break;
    printk(&_LC6,"FRAMEWORK","dbg_txcmd_feature_search");
    puVar5 = (undefined4 *)*puVar5;
  }
  if ((uint)puVar5[10] < uVar3) {
    return 0;
  }
  printk(&_LC5,"FRAMEWORK","dbg_txcmd_feature_search",puVar5[10],uVar7);
  uVar1 = (**(code **)(puVar5[0xb] + (uVar3 + 0x3fffffff) * 4))(param_1,uVar1,local_24[0]);
  return uVar1;
}

