// module: mt7915.ko
// function: hqa_muru_set_agg_policy @ 0x23fd2c
// size: 296 bytes
//

int hqa_muru_set_agg_policy(undefined4 param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  undefined1 local_12;
  undefined1 local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_muru_set_agg_policy");
  }
  else {
    iVar1 = sscanf(param_2,"%hhu-%hhu",&local_12,&local_11);
    if (0 < iVar1) {
      if (0 < DebugLevel) {
        printk("%s: MURU aggpolicy:%u, duration comp:%u\n","hqa_muru_set_agg_policy",local_12,
               local_11);
      }
      iVar1 = wifi_test_agg_policy(param_1,local_12,local_11);
      if (DebugLevel < 1) {
        return iVar1;
      }
      pcVar2 = "Fail";
      if (iVar1 != 0) {
        pcVar2 = "Success";
      }
      goto LAB_0023fe14;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  iVar1 = 0;
  pcVar2 = "Fail";
LAB_0023fe14:
  printk("%s: CMD %s\n","hqa_muru_set_agg_policy",pcVar2);
  return iVar1;
}

