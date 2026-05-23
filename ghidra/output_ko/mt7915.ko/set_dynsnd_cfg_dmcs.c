// module: mt7915.ko
// function: set_dynsnd_cfg_dmcs @ 0xe6720
// size: 184 bytes
//

bool set_dynsnd_cfg_dmcs(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char *pcVar3;
  int iVar4;
  bool bVar5;
  char *local_14;
  
  local_14 = param_2;
  pcVar3 = strsep(&local_14,":");
  if (pcVar3 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar3,0,10);
    pcVar3 = strsep(&local_14,"");
    if (pcVar3 != (char *)0x0) {
      uVar2 = os_str_tol(pcVar3,0,10);
      iVar4 = cmd_txbf_cfg_dynsnd_dmcsth(param_1,uVar1,uVar2);
      bVar5 = iVar4 == 0;
      goto LAB_000e67a0;
    }
  }
  bVar5 = false;
LAB_000e67a0:
  if (-1 < DebugLevel) {
    printk("%s:(status = %d\n","set_dynsnd_cfg_dmcs",bVar5);
  }
  return bVar5;
}

