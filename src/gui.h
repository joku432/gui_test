#ifndef GUI_H_
#define GUI_H_

#include <stdint.h>

// IMXRT1050-EVKB W: 472 H: 270

enum {
	GUI_SUCCESS = 0,
	GUI_ERROR = -1
};

typedef struct _lv_obj_t lv_obj_t;

typedef struct gui {
	uint16_t W;
	uint16_t H;
	lv_obj_t* screens[3];
	lv_obj_t* line_meter;
	lv_obj_t* value_label;
	uint32_t adc_value_treshold;
} gui_t;

int8_t gui_init(gui_t *gui, uint16_t W, uint16_t H);
void gui_set_callbacks(void);
int8_t gui_update_adc_value(gui_t *gui, uint32_t value);
int8_t gui_set_adc_value_treshold(gui_t *gui, uint32_t value);
int32_t gui_get_adc_value_treshold(gui_t* gui);


#endif