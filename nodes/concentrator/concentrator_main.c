// #include <stdio.h>

// #include "msg.h"
// #include "thread.h"

// #include "concentrator_coap.h"

// extern const uint8_t resource_count;
// static msg_t _main_msg_queue[resource_count * 2];

// kernel_pid_t main_pid;

// static bool resources_alive[resource_count] = { false };

// int main(void) {
//     main_pid = thread_getpid();
//     msg_init_queue(_main_msg_queue, resource_count);
//     server_init();
//     puts("concentrator ready");

//     while(1) {
//         msg_t msg;
//         msg_receive(&msg);

//         if(msg.type != MESSAGE_TYPE_HEARTBEAT) {
//             continue;
//         }

//         if(resources_alive[msg.content.value]) {
//             resources_alive[msg.content.value] = false;
//         } else {
//             /* insert sensor failure handling here */
//             /* IDEA:
//                 generate some sort of "event", similar to the sensor events,
//                 which is of some "status"-type, indicating the unresponsiveness of the sensor,
//                 add to the event:
//                     - timestamp
//                     - type of the sensor that failed 
//             */
//         }
//     }

//     return 0;
// }