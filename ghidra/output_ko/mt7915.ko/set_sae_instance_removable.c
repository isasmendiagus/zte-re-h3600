// module: mt7915.ko
// function: set_sae_instance_removable @ 0x208d10
// size: 180 bytes
//

bool set_sae_instance_removable(undefined4 param_1,undefined1 *param_2,undefined1 *param_3)

{
  int iVar1;
  
  iVar1 = search_sae_instance();
  if (4 < DebugLevel) {
    printk("%s:OM=%02x:%02x:%02x:%02x:%02x:%02x, PM=%02x:%02x:%02x:%02x:%02x:%02x\n",
           "set_sae_instance_removable",*param_2,param_2[1],param_2[2],param_2[3],param_2[4],
           param_2[5],*param_3,param_3[1],param_3[2],param_3[3],param_3[4],param_3[5]);
  }
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x129) = 1;
  }
  return iVar1 != 0;
}

