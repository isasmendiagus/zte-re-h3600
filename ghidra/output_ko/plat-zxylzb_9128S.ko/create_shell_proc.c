// module: plat-zxylzb_9128S.ko
// function: create_shell_proc @ 0x117d8
// size: 60 bytes
//

int create_shell_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data("shell",0x1a4,param_1,proc_file_fops,0);
  return -(uint)(iVar1 == 0);
}

