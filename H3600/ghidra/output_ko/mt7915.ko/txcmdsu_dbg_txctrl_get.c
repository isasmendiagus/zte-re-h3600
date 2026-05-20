// module: mt7915.ko
// function: txcmdsu_dbg_txctrl_get @ 0x28ef18
// size: 1112 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 txcmdsu_dbg_txctrl_get(undefined4 param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *local_3c;
  uint local_38;
  uint local_34;
  int local_30 [5];
  uint *local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  
  local_3c = (undefined4 *)0x0;
  local_34 = 0;
  local_30[0] = 0;
  printk(&_LC84,"TXCMDSU","txcmdsu_dbg_txctrl_get");
  printk(&_LC5,"TXCMDSU","txcmdsu_dbg_txctrl_get",param_3);
  iVar1 = sscanf(param_3,"%d-%x",&local_34,local_30);
  if (iVar1 < 1) {
    printk(&_LC47,"TXCMDSU","txcmdsu_dbg_txctrl_get");
    printk(&_LC86,"TXCMDSU","txcmdsu_dbg_txctrl_get");
    printk(&_LC49,"TXCMDSU","txcmdsu_dbg_txctrl_get");
  }
  local_38 = local_34;
  os_alloc_mem(0,&local_3c,0x640);
  if (local_3c == (undefined4 *)0x0) {
    printk(&_LC87,"TXCMDSU","txcmdsu_dbg_txctrl_get");
    return 1;
  }
  os_zero_mem(local_3c,0x640);
  if (local_34 < 4) {
    uVar2 = (&DAT_002a79b8)[local_34];
  }
  else {
    uVar2 = 0;
  }
  printk(&_LC88,"TXCMDSU","txcmdsu_dbg_txctrl_get",uVar2);
  local_30[1] = 0x1a;
  local_18 = local_3c;
  local_30[3] = 4;
  local_30[2] = 0xc9;
  local_1c = &local_38;
  local_14 = 0;
  local_30[4] = uVar2;
  iVar1 = dbg_ut_wmcu_send(param_1,local_30 + 1);
  if (iVar1 != 0) {
    printk(&_LC6,"TXCMDSU","txcmdsu_dbg_txctrl_get");
  }
  iVar1 = local_30[0];
  puVar3 = local_3c;
  switch(local_34) {
  case 0:
    printk(&_LC89,"TXCMDSU","txcmdsu_dbg_txdata_dump",*(undefined1 *)((int)local_3c + 1));
    printk(&_LC90,"TXCMDSU","txcmdsu_dbg_txdata_dump",*(undefined2 *)((int)puVar3 + 2));
    printk(&_LC91,"TXCMDSU","txcmdsu_dbg_txdata_dump",puVar3[4]);
    printk(&_LC92,"TXCMDSU","txcmdsu_dbg_txdata_dump",puVar3[1]);
    printk(&_LC93,"TXCMDSU","txcmdsu_dbg_txdata_dump",*(undefined1 *)puVar3);
    printk(&_LC94,"TXCMDSU","txcmdsu_dbg_txdata_dump",puVar3[3]);
    FUN_0028e218(puVar3 + 5);
    break;
  case 1:
    puVar3 = local_3c + 1;
    printk(&_LC95,"TXCMDSU","txcmdsu_dbg_protect_dump",*local_3c);
    FUN_0028e218(puVar3);
    break;
  case 2:
    printk(&_LC95,"TXCMDSU","txcmdsu_dbg_trig_dump",local_3c[7]);
    printk(&_LC96,"TXCMDSU","txcmdsu_dbg_trig_dump",puVar3[8]);
    printk(&_LC97,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined1 *)((int)puVar3 + 1));
    printk(&_LC98,"TXCMDSU","txcmdsu_dbg_trig_dump",puVar3[6]);
    printk(&_LC99,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined1 *)puVar3);
    printk(&_LC100,"TXCMDSU","txcmdsu_dbg_trig_dump",puVar3[3]);
    printk(&_LC101,"TXCMDSU","txcmdsu_dbg_trig_dump",puVar3[2]);
    printk(&_LC102,"TXCMDSU","txcmdsu_dbg_trig_dump",puVar3[4]);
    printk(&_LC103,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined1 *)((int)puVar3 + 2));
    printk(&_LC104,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined1 *)(puVar3 + 1));
    printk(&_LC105,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined2 *)(puVar3 + 5));
    printk(&_LC106,"TXCMDSU","txcmdsu_dbg_trig_dump",*(undefined1 *)((int)puVar3 + 0x16));
    FUN_0028e218(puVar3 + 9);
    break;
  case 3:
    puVar4 = local_3c + 0x180;
    do {
      if (((iVar1 == 0) || (iVar1 == puVar3[4])) && (*(char *)(puVar3 + 5) == '\x01')) {
        FUN_0028eee4(puVar3);
      }
      puVar3 = puVar3 + 6;
    } while (puVar3 != puVar4);
  }
  os_free_mem(local_3c);
  return 0;
}

