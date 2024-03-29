export const HEADER_SIGN        = '$';
export const HEADER_BYTE        = 0x24;
export const MONITOR_BYTE       = 0x40;
export const CONTROL_BYTE       = 0x80;
export const OPEN_LOOP_BYTE     = 0x20;
export const CLOSED_LOOP_BYTE   = 0x21;
export const P_VALUE_BYTE       = 0x22;
export const I_VALUE_BYTE       = 0x23;
export const CURRENT_VALUE_BYTE = 0x01;
export const ERROR_BYTE         = 0x02;

export const ST_START           = 0;
export const ST_GET_MODE        = 1;
export const ST_GET_VALUE       = 2;
export const ST_GET_CS          = 3;
