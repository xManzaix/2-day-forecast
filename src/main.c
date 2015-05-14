#include <pebble.h>
#include "background.h"
//#include "background2dayforecast.c"
 
  
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
  //app_message_register_inbox_received(inbox_received_callback);
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