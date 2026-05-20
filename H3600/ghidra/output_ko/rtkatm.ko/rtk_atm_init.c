// module: rtkatm.ko
// function: rtk_atm_init @ 0x10ec4
// size: 784 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 rtk_atm_init(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2c3,"rtk_atm_init",0,7
              ,0,"Init remote ATM host module.\n");
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2c7,"rtk_atm_init",0,7
              ,0,&_LC28);
  iVar1 = alloc_netdev_mqs(200,"ptm%d",0,&ether_setup,1,1);
  uVar3 = realtek_proc;
  *(undefined1 **)(iVar1 + 300) = ptm_netdev_ops;
  proc_create_data("atm_carrier",0,uVar3,fops_atm_carrier_cfg,0);
  proc_create_data("ptm_carrier",0,realtek_proc,fops_ptm_carrier_cfg,0);
  proc_create_data("remote_atm_phy",0,realtek_proc,fops_remote_atm,0);
  if (iVar1 != 0) {
    register_netdev(iVar1);
  }
  piVar2 = (int *)kmem_cache_alloc(_DAT_000120b8,0x80d0);
  if (piVar2 == (int *)0x0) {
    ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2d7,"rtk_atm_init",0
                ,4,0,&_LC33);
    uVar3 = 0xfffffff4;
  }
  else {
    iVar1 = atm_dev_register(&_LC34,0,ops,0xffffffff,0);
    rtk_atmdev = iVar1;
    if (iVar1 == 0) {
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2de,"rtk_atm_init"
                  ,0,4,0,&_LC35);
      uVar3 = 0xffffffed;
    }
    else {
      *(int **)(iVar1 + 0x10) = piVar2;
      *piVar2 = iVar1;
      *(undefined1 *)(iVar1 + 0x32) = 8;
      *(undefined1 *)(iVar1 + 0x33) = 0x10;
      cfg = piVar2;
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2ea,"rtk_atm_init"
                  ,0,7,0,"###################################################\n");
      uVar3 = *(undefined4 *)(rtk_atmdev + 8);
      pcVar5 = "v0.0.1";
      pcVar6 = "May 12, 2017";
      pcVar4 = "RTK ATM Module";
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2ec,"rtk_atm_init"
                  ,0,7,0,"%s: %s %s (%s)\n",uVar3,"RTK ATM Module","v0.0.1","May 12, 2017");
      ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2ed,"rtk_atm_init"
                  ,0,7,0,"###################################################\n");
      remote_dev = dev_get_by_name(&init_net,&_LC22);
      if (remote_dev == 0) {
        ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x2f1,
                    "rtk_atm_init",0,4,0,"rtk_atm: cannot find remote device\n",uVar3,pcVar4,pcVar5,
                    pcVar6);
        uVar3 = 0xffffffed;
      }
      else {
        DAT_0001190c = remote_dev;
        *(undefined1 *)(rtk_atmdev + 0x70) = 0;
        dev_add_pack(&atm_packet_type);
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}

