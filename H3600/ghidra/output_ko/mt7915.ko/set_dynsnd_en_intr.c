// module: mt7915.ko
// function: set_dynsnd_en_intr @ 0xe64e4
// size: 48 bytes
//

bool set_dynsnd_en_intr(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = os_str_tol(param_2,0,10);
  iVar2 = cmd_txbf_en_dynsnd_intr(param_1,uVar1);
  return iVar2 == 0;
}

