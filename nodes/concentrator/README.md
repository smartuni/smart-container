Changes:
    boards --> nrf52840dk --> include --> board.h 

    added following code:
        #define SX127X_PARAM_SPI (SPI_DEV(0))
        #define SX127X_PARAM_SPI_NSS GPIO_PIN(1,12) /* D10 */
        #define SX127X_PARAM_RESET GPIO_PIN(0,3) /* A0 */
        #define SX127X_PARAM_DIO0 GPIO_PIN(1,3) /* D2 */
        #define SX127X_PARAM_DIO1 GPIO_PIN(1,4) /* D3 */
        #define SX127X_PARAM_DIO2 GPIO_PIN(1,5) /* D4 */
        #define SX127X_PARAM_DIO3 GPIO_PIN(1,6) /* D5 */
    
    Makefile:
    
    added drivers for LoRaWAN board:
        USEMODULE += sx1272


 
