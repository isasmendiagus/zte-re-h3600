// module: mt7915.ko
// function: mt_serv_main @ 0x253a90
// size: 160 bytes
//

int mt_serv_main(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = mt_serv_init_test();
    break;
  case 1:
    iVar1 = mt_serv_exit_test();
    break;
  case 2:
    iVar1 = mt_serv_start();
    break;
  case 3:
    iVar1 = mt_serv_stop();
    break;
  case 4:
    iVar1 = mt_serv_start_tx();
    break;
  case 5:
    iVar1 = mt_serv_stop_tx();
    break;
  case 6:
    iVar1 = mt_serv_start_rx();
    break;
  case 7:
    iVar1 = mt_serv_stop_rx();
    break;
  default:
    return 0x205;
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_main",iVar1);
    return iVar1;
  }
  return 0;
}

