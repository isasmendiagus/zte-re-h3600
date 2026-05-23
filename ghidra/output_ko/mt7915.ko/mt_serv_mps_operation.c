// module: mt7915.ko
// function: mt_serv_mps_operation @ 0x252568
// size: 188 bytes
//

int mt_serv_mps_operation(undefined4 *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_1 + 0x133);
  if (param_2 == 0) {
    iVar1 = net_ad_mps_tx_operation(*param_1,param_1 + uVar2 * 0x346 + 0x138,1);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (*(char *)(param_1 + 0x7d1) != '\0') {
      return 0;
    }
    iVar1 = mt_engine_start_tx(*param_1,param_1 + uVar2 * 0x346 + 0x138,param_1[0x7c4],uVar2);
  }
  else {
    if (param_2 != 1) {
      return 0x204;
    }
    iVar1 = net_ad_mps_tx_operation(*param_1,param_1 + uVar2 * 0x346 + 0x138,0);
  }
  if (iVar1 == 0) {
    return 0;
  }
  printk("%s: err=0x%08x\n","mt_serv_mps_operation",iVar1);
  return iVar1;
}

