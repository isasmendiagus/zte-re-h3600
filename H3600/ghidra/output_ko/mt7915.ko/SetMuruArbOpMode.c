// module: mt7915.ko
// function: SetMuruArbOpMode @ 0x23f644
// size: 132 bytes
//

undefined4 SetMuruArbOpMode(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_14 [2];
  
  local_14[0] = param_2;
  pcVar2 = strsep(local_14,"-");
  uVar4 = 0;
  if (pcVar2 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar2,0,10);
    iVar3 = wifi_test_muru_set_arb_op_mode(param_1,uVar1);
    uVar4 = 0;
    if (iVar3 != 0) {
      uVar4 = 1;
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruArbOpMode",uVar4);
  }
  return uVar4;
}

