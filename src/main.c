#include <pebble.h>
#include "background.h"

#define KEY_DATE 0
#define KEY_TEMPERATURE_DAY1 1
#define KEY_TEMPERATURE_DAY2 2
#define KEY_TEMPERATURE_DAY3 3
#define KEY_CONDITION_DAY1 4
#define KEY_CONDITION_DAY2 5
#define KEY_CONDITION_DAY3 6
#define KEY_WINDSPEED_DAY1 7
#define KEY_WINDSPEED_DAY2 8
#define KEY_WINDSPEED_DAY3 9
#define KEY_WINDDIR_DAY1 10
#define KEY_WINDDIR_DAY2 11
#define KEY_WINDDIR_DAY3 12


  
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  APP_LOG(APP_LOG_LEVEL_DEBUG, buffer);
  update_time_layer(buffer);
}  
   
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
 
  //Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    //Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    //Add a key-value pair
    dict_write_uint8(iter, 0, 0);
    
    //Send message!
    app_message_outbox_send();
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
    //Store incomming information
  static char temperature_day1_buffer[8];
  static char temperature_day2_buffer[8];
  static char temperature_day3_buffer[8];    
  static char conditions_day1_buffer[32];
  static char conditions_day2_buffer[32];
  static char conditions_day3_buffer[32];
  static char windspeed_day1_buffer[8];
  static char windspeed_day2_buffer[8];
  static char windspeed_day3_buffer[8];
  static char winddir_day1_buffer[8];
  static char winddir_day2_buffer[8];
  static char winddir_day3_buffer[8];
  static char weather_day1_layer_buffer[32];
  static char weather_day2_layer_buffer[32];
  static char weather_day3_layer_buffer[32];
  static char date_buffer[32];

  
  //Read first item
  Tuple *t = dict_read_first(iterator);
  
  //for all item
  while(t != NULL) {
    //Which key was received?
    switch(t->key) {
    case KEY_TEMPERATURE_DAY1:
      snprintf(temperature_day1_buffer, sizeof(temperature_day1_buffer), "%dC", (int)t->value->int32);
      break;
    case KEY_TEMPERATURE_DAY2:
      snprintf(temperature_day2_buffer, sizeof(temperature_day2_buffer), "%dC", (int)t->value->int32);
      break;
     case KEY_TEMPERATURE_DAY3:
      snprintf(temperature_day3_buffer, sizeof(temperature_day3_buffer), "%dC", (int)t->value->int32);
      break;   
    case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
    case KEY_WINDSPEED:
      snprintf(windspeed_buffer, sizeof(windspeed_buffer), "%dkn", (int)t->value->int32);
      break;
    case KEY_WINDDIRECTION:
      snprintf(winddir_buffer, sizeof(winddir_buffer), "%s", t->value->cstring);
      break;  
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }
    
    //look for next item
    t = dict_read_next(iterator);
  }
  //Assemble full string and display
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s, %s", temperature_buffer, conditions_buffer, windspeed_buffer);
  text_layer_set_text(s_weather_layer, weather_layer_buffer);
  text_layer_set_text(s_winddir_layer, winddir_buffer);
} 

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}  

static void init() {
  show_background();
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  //Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  hide_background();
}

int main(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "code starts here");
  init();
  app_event_loop();
  deinit();
}  