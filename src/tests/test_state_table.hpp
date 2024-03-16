#ifndef TestStateTable_HPP
#define TestStateTable_HPP

#include "../utils/context.hpp" 

void testStateTable() {
  ContextSingleton* context = ContextSingleton::GetInstance("SOO");

  // TODO: verify which state you should be in
                                      // idl
  context->event_queue->push(b4_evt); // cal
  context->event_queue->push(b1_evt); // cal
  context->event_queue->push(no_evt); // cal
  context->event_queue->push(b2_evt); // cal
  context->event_queue->push(b3_evt); // cal
  context->event_queue->push(b4_evt); // man
  context->event_queue->push(b4_evt); // mts
  context->event_queue->push(b1_evt); // idle
  context->event_queue->push(b1_evt); // idle
  context->event_queue->push(b2_evt); // man
  context->event_queue->push(b2_evt); // man
  context->event_queue->push(b4_evt); // mts
                                      // mts
                                      // mts
                                      // mts
}

#endif