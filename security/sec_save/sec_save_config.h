#ifndef SEC_SAVE_CONFIG_H
#define SEC_SAVE_CONFIG_H

// Configuration for debugging

#define DEBUG

#ifdef DEBUG
#define PRINT_FILE stdout
#else
#define PRINT_FILE stderr
#endif

// EEPROM Memory Address
#define SEC_SAVE_EEPROM_ADDRESS 0x16 #TODO

#endif /* SEC_SAVE_CONFIG_H */
/** @} */
