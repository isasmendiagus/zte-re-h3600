// module: rtkatm.ko
// function: remote_atm_read @ 0x104e4
// size: 112 bytes
//

undefined4
remote_atm_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  char *pcVar2;
  int iVar3;
  
  seq_printf(param_1,"PHY MAC Address:",param_3,param_4,param_4);
  iVar3 = 0;
  do {
    pcVar2 = "%02x:";
    if (iVar3 == 5) {
      pcVar2 = "%02x";
      uVar1 = dmac._5_1_;
    }
    else {
      uVar1 = *(undefined1 *)((int)&dmac + iVar3);
    }
    iVar3 = iVar3 + 1;
    seq_printf(param_1,pcVar2,uVar1);
  } while (iVar3 != 6);
  seq_printf(param_1,&_LC12);
  return 0;
}

