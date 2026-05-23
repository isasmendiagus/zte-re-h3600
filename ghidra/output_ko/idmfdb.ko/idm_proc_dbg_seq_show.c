// module: idmfdb.ko
// function: idm_proc_dbg_seq_show @ 0x11ae4
// size: 56 bytes
//

undefined4 idm_proc_dbg_seq_show(undefined4 param_1)

{
  seq_printf(param_1,&_LC0,ifd_debug);
  seq_printf(param_1,
             "#define IFD_DBG_PKT (1 << 0)\n#define IFD_DBG_MUL (1 << 1)\n#define IFD_DBG_LED (1 << 2)\n#define IFD_DBG_TX  (1 << 3)\n#define IFD_DBG_RX  (1 << 4)\n"
            );
  return 0;
}

