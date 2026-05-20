// module: mt7915.ko
// function: txcmdsu_dbg_manual_mode_tx @ 0x28ec14
// size: 716 bytes
//

undefined4 txcmdsu_dbg_manual_mode_tx(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_54 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  printk(&_LC69,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
  printk(&_LC5,"TXCMDSU","txcmdsu_dbg_manual_mode_tx",param_3);
  iVar1 = sscanf(param_3,"%d-%d-%d-%d-%d-%d-%d-%d-%d",&local_54,&local_74,&local_70,&local_68,
                 &local_64,&local_6c,&local_60,&local_5c,&local_58);
  local_50 = local_54;
  local_4c = (undefined1)local_74;
  local_4b = (undefined1)local_70;
  local_4a = (undefined1)local_6c;
  local_48 = (undefined1)local_64;
  local_49 = (undefined1)local_68;
  local_46 = (undefined1)local_60;
  local_47 = (undefined1)local_5c;
  local_45 = (undefined1)local_58;
  if (iVar1 == 9) {
    printk(&_LC82,"TXCMDSU","txcmdsu_dbg_manual_mode_tx","txcmdsu_dbg_manual_mode_tx",local_54,
           local_74,local_70,local_6c,local_68,local_64,local_60,local_5c,local_58);
    local_44 = 0x1a;
    local_40 = 100;
    local_34 = &local_50;
    local_2c = 0;
    local_38 = 0;
    local_30 = 0;
    local_3c = 0x10;
    iVar1 = dbg_ut_wmcu_send(param_1,&local_44);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk(&_LC6,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
      uVar2 = 0;
    }
  }
  else {
    printk(&_LC71,"TXCMDSU","txcmdsu_dbg_manual_mode_tx",iVar1);
    printk(&_LC72,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC73,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC74,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC75,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC76,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC77,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC78,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC79,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC80,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    printk(&_LC81,"TXCMDSU","txcmdsu_dbg_manual_mode_tx");
    uVar2 = 1;
  }
  return uVar2;
}

