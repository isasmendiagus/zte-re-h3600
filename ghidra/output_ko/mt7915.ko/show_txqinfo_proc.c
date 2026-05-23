// module: mt7915.ko
// function: show_txqinfo_proc @ 0xe2f80
// size: 316 bytes
//

undefined4 show_txqinfo_proc(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  code *pcVar6;
  
  iVar5 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  if (0 < DebugLevel) {
    printk("%s::param = %s\n","show_txqinfo_proc",param_2);
  }
  if ((param_2 != 0) && (iVar3 = rstrtok(param_2,&_LC232), iVar3 != 0)) {
    uVar2 = os_str_tol(iVar3,0,10);
    iVar3 = rstrtok(0,&_LC232);
    if (iVar3 != 0) {
      uVar4 = os_str_tol(iVar3,0,10);
      iVar3 = rstrtok(0,&_LC232);
      if (iVar3 != 0) {
        uVar1 = os_str_tol(iVar3,0,10);
        pcVar6 = *(code **)(iVar5 + 0xc);
        if (pcVar6 == (code *)0x0) {
          return 1;
        }
        if (0 < DebugLevel) {
          printk("%s::wcid = %d, pkt_type = %d, q_idx = %d\n","show_txqinfo_proc",uVar2,uVar4,uVar1)
          ;
          pcVar6 = *(code **)(iVar5 + 0xc);
        }
        (*pcVar6)(param_1,uVar2,uVar4,uVar1);
        return 1;
      }
    }
  }
  return 0;
}

