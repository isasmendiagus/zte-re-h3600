// module: mt7915.ko
// function: show_wtbltlv_proc @ 0xe0bf4
// size: 380 bytes
//

undefined4 show_wtbltlv_proc(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined1 auStack_44 [44];
  
  __memzero(auStack_44,0x2c);
  if (DebugLevel < 1) {
    if (param_2 == 0) {
      return 0;
    }
  }
  else {
    printk("%s::param=%s\n","show_wtbltlv_proc",param_2);
    if (param_2 == 0) goto LAB_000e0cfc;
  }
  iVar4 = rstrtok(param_2,&_LC232);
  if (iVar4 != 0) {
    uVar3 = os_str_tol(iVar4,0,10);
    iVar4 = rstrtok(0,&_LC232);
    if (iVar4 != 0) {
      uVar1 = os_str_tol(iVar4,0,10);
      iVar4 = rstrtok(0,&_LC232);
      if (iVar4 != 0) {
        uVar2 = os_str_tol(iVar4,0,10);
        if (0 < DebugLevel) {
          printk("%s():Wcid(%d), CmdId(%d), Action(%d)\n","show_wtbltlv_proc",uVar3,uVar1,uVar2);
        }
        mt_wtbltlv_debug(param_1,uVar3,uVar1,uVar2,auStack_44);
        return 1;
      }
    }
  }
LAB_000e0cfc:
  if ((0 < DebugLevel) &&
     (printk("%s: param = %s not correct\n","show_wtbltlv_proc",param_2), 0 < DebugLevel)) {
    printk("%s: iwpriv ra0 show wtbltlv=Wcid,CmdId,Action\n","show_wtbltlv_proc");
  }
  return 0;
}

