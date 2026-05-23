// module: mt7915.ko
// function: WtblResetAndDWsSet @ 0x1c6324
// size: 300 bytes
//

undefined4
WtblResetAndDWsSet(undefined4 param_1,undefined4 param_2,undefined1 param_3,int param_4,
                  undefined1 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 local_38;
  undefined2 local_36;
  undefined1 local_34;
  undefined1 local_33;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (3 < DebugLevel) {
    printk(&_LC14,"WtblResetAndDWsSet");
  }
  if (param_4 < 1) {
    uVar1 = 0;
  }
  else {
    iVar2 = 0;
    do {
      __memzero(&local_38,0x10);
      local_30 = *(undefined4 *)(param_5 + 4);
      local_33 = *param_5;
      local_2c = *(undefined4 *)(param_5 + 8);
      if (iVar2 == 0) {
        uVar1 = 1;
      }
      else {
        uVar1 = 2;
      }
      param_5 = param_5 + 0xc;
      local_36 = 0x10;
      local_38 = 0xe;
      local_34 = param_3;
      uVar1 = CmdExtWtblUpdate(param_1,param_2,uVar1,&local_38,0x10);
      if (3 < DebugLevel) {
        printk("%s: cmd_cnt/WlanIdx/Tag/Length/WtblIdx/WhichDW/DwMask/DwValue/ret=%d/%d/%d/%d/%d/%d/0x%x/0x%x/%d\n"
               ,"WtblResetAndDWsSet",iVar2,param_2,local_38,local_36,local_34,local_33,local_30,
               local_2c,uVar1);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != param_4);
  }
  return uVar1;
}

