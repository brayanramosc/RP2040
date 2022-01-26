#ifndef _LCD_H
#define _LCD_H

// LCD ports
// Control ports
#define RS  28
#define RW  27
#define E   26

// Data/Command ports
#define D4  22
#define D5  21
#define D6  20
#define D7  19

#define LCD_CLEAR                       0x01
#define LCD_CURSOR_HOME                 0x02
#define LCD_ENTRY_MODE                  0x04
#define LCD_ONOFF_CONTROL               0x08
#define LCD_MOVE                        0x10
#define LCD_SET_FUNCTION                0x20
#define LCD_SET_DDRAM_ADDR              0x80
#define LCD_INITIALIZE_CMD              0x30   

// Entry mode
// Cursor inc/dec
#define LCD_ENTRY_MODE_CURSOR_INC       0x02
#define LCD_ENTRY_MODE_CURSOR_DEC       0x00
// display shift
#define LCD_ENTRY_MODE_DISPSHIFT        0x01
#define LCD_ENTRY_MODE_DIPSNOSHIFT      0x00

// Display/cursor on/off
// Display on/off
#define LCD_ONOFF_CONTROL_DISP_ON       0x04
#define LCD_ONOFF_CONTROL_DISP_OFF      0x00
// Cursor on/off
#define LCD_ONOFF_CONTROL_CURSOR_ON     0x02
#define LCD_ONOFF_CONTROL_CURSOR_OFF    0x00
// Blinking on/off
#define LCD_ONOFF_CONTROL_BLINK_ON      0x01
#define LCD_ONOFF_CONTROL_BLINK_OFF     0x00

// Shift
// Display/cursor shift
#define LCD_MOVE_DISP                   0x08
#define LCD_MOVE_CURSOR                 0x00
// Shift direction
#define LCD_MOVE_TO_RIGHT               0x04
#define LCD_MOVE_TO_LEFT                0x00

// Set function
// N-bits interface
#define LCD_SET_FUNCTION_8BITS          0x10
#define LCD_SET_FUNCTION_4BITS          0x00
// Line display
#define LCD_SET_FUNCTION_2LINE          0x08
#define LCD_SET_FUNCTION_1LINE          0x00
// Dots
#define LCD_SET_FUNCTION_5x10           0x04
#define LCD_SET_FUNCTION_5x8            0x00

#define LCD_RS_CMD                      0
#define LCD_RS_DATA                     1
#define LCD_RW_WRITE                    0
#define LCD_RW_READ                     1
#define LCD_DISABLE                     0
#define LCD_ENABLE                      1

#define LCD_BYTE_MSB(b)                 (((uint8_t)(b) >> 4) & 0x0F)
#define LCD_BYTE_LSB(b)                 (((uint8_t)(b) >> 0) & 0x0F)

void ports_init(void);
bool lcd_busy(void);
void lcd_init_cmd(uint8_t);
void lcd_enable_pulse(void);
void lcd_send_4bit(uint8_t, bool);
void lcd_set_function(uint8_t, uint8_t, uint8_t);
void lcd_onoff_control(uint8_t, uint8_t, uint8_t);
void lcd_clear_screen(void);
void lcd_entry_mode(uint8_t, uint8_t);
void lcd_set_address_ddram (uint8_t);
void lcd_init(void);
void lcd_send_char(uint8_t);
void lcd_write_msg(uint8_t *);

#endif
