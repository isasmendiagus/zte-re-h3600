// module: mt7915.ko
// function: mtf_set_air_monitor_rule @ 0x19781c
// size: 368 bytes
//

undefined4 mtf_set_air_monitor_rule(int param_1,byte *param_2,int param_3)

{
  byte bVar1;
  undefined1 *local_24;
  undefined1 auStack_20 [12];
  
  local_24 = (undefined1 *)0x0;
  os_alloc_mem(param_1,&local_24,8);
  if (local_24 != (undefined1 *)0x0) {
    if (0 < DebugLevel) {
      printk("--> %s()\n","mtf_set_air_monitor_rule");
    }
    if (param_2 != (byte *)0x0) {
      bVar1 = *(byte *)(param_1 + 0xa376a4) & 0xf8;
      *(byte *)(param_1 + 0xa376a4) = bVar1;
      *(byte *)(param_1 + 0xa376a4) =
           bVar1 | param_2[2] & 1 | (*param_2 & 1) << 2 | (param_2[1] & 1) << 1;
      if (param_3 == 0) {
        *local_24 = 0;
        local_24[1] = 1;
LAB_001978fc:
        apply_mntr_ruleset_smesh(param_1,local_24);
        MtCmdSmeshConfigSet(param_1,local_24,auStack_20);
        if (0 < DebugLevel) {
          printk("<-- %s()\n","mtf_set_air_monitor_rule");
        }
        os_free_mem(local_24);
        return 1;
      }
      if (param_3 == 1) {
        *local_24 = 1;
        local_24[1] = 1;
        goto LAB_001978fc;
      }
      if (0 < DebugLevel) {
        printk("%s():: wrong band index(%d)\n","mtf_set_air_monitor_rule",param_3);
      }
    }
    os_free_mem(local_24);
  }
  return 0;
}

