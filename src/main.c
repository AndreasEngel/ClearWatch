#include <pebble.h>
   
static Window *s_main_window;
static TextLayer *s_hour_layer;
static TextLayer *s_tag_layer;
static TextLayer *s_minute_layer;
static TextLayer *s_sekunde_layer;
static TextLayer *s_blutooth_layer;
static TextLayer *s_batt_layer;
static GFont FONT_ROBOTO_40;
static GFont FONT_ROBOTO_80;
static GFont FONT_ROBOTO_30;
 
static void sek_akt() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffers[] = "00";
  strftime(buffers, sizeof("00"), "%S", tick_time);
  text_layer_set_text(s_sekunde_layer, buffers);
}
 
static void min_akt() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffers[] = "00";
  strftime(buffers, sizeof("00"), "%M", tick_time);
  text_layer_set_text(s_minute_layer, buffers);
}
  
static void hour_akt() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffers[] = "00";
  strftime(buffers, sizeof("00"), "%H", tick_time);
  text_layer_set_text(s_hour_layer, buffers);
}
 
static void day_akt() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffert[] = "Mo, 01.";
  static char wt[]="1";
  strftime(wt, sizeof("1"), "%u", tick_time);
  if (strcmp("1",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Mo. %d.", tick_time);
  if (strcmp("2",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Di. %d.", tick_time);
  if (strcmp("3",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Mi. %d.", tick_time);
  if (strcmp("4",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Do. %d.", tick_time);
  if (strcmp("5",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Fr. %d.", tick_time);
  if (strcmp("6",wt)==0) strftime(buffert, sizeof("Mo. 03."), "Sa. %d.", tick_time);
  if (strcmp("7",wt)==0) strftime(buffert, sizeof("Mo. 03."), "So. %d.", tick_time);   
  text_layer_set_text(s_tag_layer, buffert);
}


static void bt_handler(bool connected) {
  // Show current connection state
  if (connected) {
    text_layer_set_text(s_blutooth_layer, "BT");
  } else {
    text_layer_set_text(s_blutooth_layer, "  ");
  }
}
 
static void batt_handler(BatteryChargeState charge_state) {
    static char battery_text[] = "100%";
    if (charge_state.is_charging) {
        snprintf(battery_text, sizeof(battery_text), "***");
    } else {
        snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);
    }
    text_layer_set_text(s_batt_layer, battery_text);
}
 
 
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  window_set_background_color (window,GColorBlack); 
  //Beginn Bluetooth
	// Create output TextLayer
  s_blutooth_layer = text_layer_create(GRect(0,-5,20,18));
  text_layer_set_text_alignment(s_blutooth_layer, GTextAlignmentLeft);
  text_layer_set_font(s_blutooth_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(s_blutooth_layer, GColorBlack);
  text_layer_set_text_color(s_blutooth_layer, GColorClear);
  layer_add_child(window_layer, text_layer_get_layer(s_blutooth_layer));
 
  // Show current connection state
  bt_handler(bluetooth_connection_service_peek()); 
	//Ende Bluetooth
	//Beginn Batterie

	s_batt_layer=text_layer_create(GRect(105,-5,39,18));
	text_layer_set_font(s_batt_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	layer_add_child(window_layer, text_layer_get_layer(s_batt_layer));
	text_layer_set_text_alignment(s_batt_layer, GTextAlignmentRight);
	text_layer_set_background_color(s_batt_layer, GColorBlack);
	text_layer_set_text_color(s_batt_layer, GColorClear);
	batt_handler(battery_state_service_peek());
      
  // Create time TextLayer
  FONT_ROBOTO_40=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_40));
	FONT_ROBOTO_80=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_80));
	FONT_ROBOTO_30=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_30));
   
  s_tag_layer = text_layer_create(GRect(44,-5, 60, 18)); //Start,hoehe,breite 144x168
  text_layer_set_background_color(s_tag_layer, GColorBlack);
  text_layer_set_text_color(s_tag_layer, GColorClear);
  text_layer_set_text(s_tag_layer, "Thu, 3.");
  text_layer_set_font(s_tag_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_tag_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_tag_layer));
     
  s_hour_layer = text_layer_create(GRect(-1, 14, 40, 49)); //Start,hoehe,breite 144x168
  text_layer_set_background_color(s_hour_layer, GColorBlack);
  text_layer_set_text_color(s_hour_layer, GColorClear);
  text_layer_set_text(s_hour_layer, "00");
  text_layer_set_font(s_hour_layer, FONT_ROBOTO_40);
  text_layer_set_text_alignment(s_hour_layer, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_hour_layer));
   
  s_minute_layer = text_layer_create(GRect(35, 52, 80, 80)); //Start,hoehe,breite 144x168
  text_layer_set_background_color(s_minute_layer, GColorBlack);
  text_layer_set_text_color(s_minute_layer, GColorClear);
  text_layer_set_text(s_minute_layer, "00");
  text_layer_set_font(s_minute_layer, FONT_ROBOTO_80);
  text_layer_set_text_alignment(s_minute_layer, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_minute_layer));
   
  s_sekunde_layer = text_layer_create(GRect(113, 138, 30, 30)); //Start,hoehe,breite 144x168
  text_layer_set_background_color(s_sekunde_layer, GColorBlack);
  text_layer_set_text_color(s_sekunde_layer, GColorClear);
  text_layer_set_text(s_sekunde_layer, "00");
  text_layer_set_font(s_sekunde_layer, FONT_ROBOTO_30);
  text_layer_set_text_alignment(s_sekunde_layer, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_sekunde_layer));
  // Make sure the time is displayed from the start
  sek_akt();
  min_akt();
  hour_akt();
}
 
static void main_window_unload(Window *window) {
  // Destroy TextLayer
	text_layer_destroy(s_tag_layer);
	text_layer_destroy(s_hour_layer);
	text_layer_destroy(s_minute_layer);
	text_layer_destroy(s_sekunde_layer);
	text_layer_destroy(s_blutooth_layer);
	text_layer_destroy(s_batt_layer);     
}
 
 
 
 
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    if (units_changed & SECOND_UNIT) {
        sek_akt();
    }
    if (units_changed & MINUTE_UNIT) {
        min_akt();
    }
    if (units_changed & HOUR_UNIT) {
        hour_akt();
    }
	if (units_changed & DAY_UNIT) {
        day_akt();
    }
}
   
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  window_set_fullscreen(s_main_window,true);
 
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
 
 
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
   
  // Register with TickTimerService
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  // Subscribe to Bluetooth updates
  bluetooth_connection_service_subscribe(bt_handler);
  battery_state_service_subscribe(batt_handler);
}
 
static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}
 
int main(void) {
  init();
  app_event_loop();
  deinit();
}