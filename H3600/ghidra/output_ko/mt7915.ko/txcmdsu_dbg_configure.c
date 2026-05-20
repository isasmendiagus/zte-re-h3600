// module: mt7915.ko
// function: txcmdsu_dbg_configure @ 0x28e8a8
// size: 872 bytes
//

undefined4 txcmdsu_dbg_configure(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  printk(&_LC45,"TXCMDSU","txcmdsu_dbg_configure");
  printk(&_LC5,"TXCMDSU","txcmdsu_dbg_configure",param_3);
  iVar1 = sscanf(param_3,"%d-%d-%d",&local_44,&local_40,&local_3c);
  local_38 = local_44;
  local_34 = local_40;
  local_30 = local_3c;
  if (iVar1 == 3) {
    printk(&_LC68,"TXCMDSU","txcmdsu_dbg_configure","txcmdsu_dbg_configure",local_44,local_40,
           local_3c);
    local_2c = 0x1a;
    local_28 = 0x65;
    local_1c = &local_38;
    local_14 = 0;
    local_20 = 0;
    local_18 = 0;
    local_24 = 0xc;
    iVar1 = dbg_ut_wmcu_send(param_1,&local_2c);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk(&_LC6,"TXCMDSU","txcmdsu_dbg_configure");
      uVar2 = 0;
    }
  }
  else {
    printk(&_LC47,"TXCMDSU","txcmdsu_dbg_configure",iVar1);
    printk(&_LC48,"TXCMDSU","txcmdsu_dbg_configure");
    printk(&_LC49,"TXCMDSU","txcmdsu_dbg_configure");
    printk(&_LC50,"TXCMDSU","txcmdsu_dbg_configure");
    printk(&_LC51,"TXCMDSU","txcmdsu_dbg_configure",0);
    printk(&_LC52,"TXCMDSU","txcmdsu_dbg_configure",1);
    printk(&_LC53,"TXCMDSU","txcmdsu_dbg_configure",2);
    printk(&_LC54,"TXCMDSU","txcmdsu_dbg_configure",3);
    printk(&_LC55,"TXCMDSU","txcmdsu_dbg_configure",4);
    printk(&_LC56,"TXCMDSU","txcmdsu_dbg_configure",5);
    printk(&_LC57,"TXCMDSU","txcmdsu_dbg_configure",6);
    printk(&_LC58,"TXCMDSU","txcmdsu_dbg_configure",7);
    printk(&_LC59,"TXCMDSU","txcmdsu_dbg_configure",8);
    printk(&_LC60,"TXCMDSU","txcmdsu_dbg_configure",9);
    printk(&_LC61,"TXCMDSU","txcmdsu_dbg_configure",10);
    printk(&_LC62,"TXCMDSU","txcmdsu_dbg_configure",0xb);
    printk(&_LC63,"TXCMDSU","txcmdsu_dbg_configure",0xc);
    printk(&_LC64,"TXCMDSU","txcmdsu_dbg_configure",0xd);
    printk(&_LC65,"TXCMDSU","txcmdsu_dbg_configure",0xe);
    printk(&_LC66,"TXCMDSU","txcmdsu_dbg_configure",0xf);
    printk(&_LC67,"TXCMDSU","txcmdsu_dbg_configure",0x10);
    uVar2 = 1;
  }
  return uVar2;
}

