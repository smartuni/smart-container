#include "gps.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "coap.h"
#include "math.h"

// Prototypes for functions used for parsing GPS infos from received UART string

/**
 * Parses a NMEA Output Sentence - GGA (Time, position and fix type data)
 * Example: $GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65
*/
int handle_gga_msg(const char *_gga);

/**
 * Parses a NMEA Output Sentence - GSA (GPS receiver operating mode, active satellites used in the position solution and DOP values)
 * Example: $GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00
*/
int handle_gsa_msg(const char *_gsa);

/**
 * Parses a NMEA Output Sentence - GSV (The number of GPS satellites in view satellite ID numbers, elevation, azimuth, and SNR values)
 * Examples:
 * - $GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D
 * - $GPGSV,3,2,09,18,26,314,40,09,57,170,44,06,20,229,37,10,26,084,37*77
 * - $GPGSV,3,3,09,07,,,26*73
*/
int handle_gsv_msg(const char *_gsv);

/**
 * Parses a NMEA Output Sentence - RMC (Time, date, position, course and speed data. Recommended Minimum Navigation Information)
 * Example: $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C
*/
int handle_rmc_msg(const char *_rmc);

/**
 * Parses a NMEA Output Sentence - VTG (Course and speed information relative to the ground)
 * Example: $GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37
*/
int handle_vtg_msg(const char *_vtg);

static bool string_starts_with(const char* str, const char* prefix) {
    int cmp_result = strncmp(str, prefix, strlen(prefix));
    return cmp_result == 0;
}

/**
 * Convert a raw coordinate to a floating point DD.DDD... value.
 * This function is a wrapper around the function minmea_tocoord,
 * but instead of returning NaN it will return 0.0 if the value is "unknown".
*/
static float minmea_tocoord_or_0(struct minmea_float* coord) {
    float result = minmea_tocoord(coord);
    if(isnan(result)) {
        return 0.0;
    } else {
        return result;
    }
}

bool gpsDataValid = false;

int handle_gga_msg(const char *_gga) {
    struct minmea_sentence_gga frame;
    bool res = minmea_parse_gga(&frame, _gga);
    if(!res) {
        return EXIT_FAILURE;
    }

    char sensor_data[80];

    float latitude = minmea_tocoord_or_0(&frame.latitude);
    float longitude = minmea_tocoord_or_0(&frame.longitude);

    char buf_latitude[9];
    char buf_longitude[9];
    fmt_float(buf_latitude, latitude, 6);
    fmt_float(buf_longitude, longitude, 6);
    sprintf(sensor_data, "%s,%s,%d,%d", buf_latitude, buf_longitude, frame.fix_quality, frame.satellites_tracked);
    printf("[GPGGA] lat=%s, long=%s, quality=%d, sats_tracked=%d\n", buf_latitude, buf_longitude, frame.fix_quality, frame.satellites_tracked);

    return EXIT_SUCCESS;
}

int handle_gsa_msg(const char *_gsa) {
    struct minmea_sentence_gsa frame;
    bool res = minmea_parse_gsa(&frame, _gsa);
    if(!res) {
        return EXIT_FAILURE;
    }
    printf("[GPGSA] sats=%d; mode=%c; fix_type=%d\n", *frame.sats, frame.mode, frame.fix_type);
    return EXIT_SUCCESS;
}

int handle_gsv_msg(const char *_gsv) {
    struct minmea_sentence_gsv frame;
    bool res = minmea_parse_gsv(&frame, _gsv);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    printf("[GPGSV] total_sats=%d; total_msgs=%d; msg_nr=%d\n", frame.total_sats, frame.total_msgs, frame.msg_nr);
    return EXIT_SUCCESS;
}

int handle_rmc_msg(const char *_rmc) {
    struct minmea_sentence_rmc frame;
    bool res = minmea_parse_rmc(&frame, _rmc);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    char sensor_data[80];

    printf("[GPRMC] Date & Time: %02d.%02d.20%02d %02d:%02d:%02d\n", 
        frame.date.day, frame.date.month, frame.date.year, frame.time.hours, frame.time.minutes, frame.time.seconds);

    if(frame.valid) {
        gpsDataValid = true;
        float latitude = minmea_tocoord_or_0(&frame.latitude);
        float longitude = minmea_tocoord_or_0(&frame.longitude);
        float speed = minmea_tocoord_or_0(&frame.speed);
        float course = minmea_tocoord_or_0(&frame.course);
        char buf_latitude[9];
        char buf_longitude[9];
        char buf_speed[4];
        char buf_course[4];
        fmt_float(buf_latitude, latitude, 6);
        fmt_float(buf_longitude, longitude, 6);
        fmt_float(buf_speed, speed, 2);
        fmt_float(buf_course, course, 2);
        printf("[GPRMC] latitude=%s, longitude=%s, course=%s, speed=%s, valid=%s\n", buf_latitude, buf_longitude, buf_course, buf_speed, frame.valid ? "true" : "false");

        // Send data to concentrator: [latitude],[longitude],[date],[time]
        sprintf(sensor_data, "%s,%s,%02d.%02d.20%02d,%02d:%02d", buf_latitude, buf_longitude, frame.date.day, frame.date.month, frame.date.year, frame.time.hours, frame.time.minutes);
        printf("sent -> %s\n", sensor_data);
        send_to_concentrator(sensor_data);
        printf("Current GPS coordinates, date and time were sent to concentrator\n");
    } else {
        gpsDataValid = false;
        printf("[GPRMC] Data not valid yet...\n");
        sprintf(sensor_data, "0.0,0.0");
    }

    return EXIT_SUCCESS;
}

int handle_vtg_msg(const char *_vtg) {
    struct minmea_sentence_vtg frame;
    bool res = minmea_parse_vtg(&frame, _vtg);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    float mag_deg = minmea_tocoord_or_0(&frame.magnetic_track_degrees);
    float true_deg = minmea_tocoord_or_0(&frame.true_track_degrees);

    printf("[GPVTG] faa_mode=%d; magnetic_track_degrees=%f; true_track_degrees=%f\n", 
        frame.faa_mode, mag_deg, true_deg);

    return EXIT_SUCCESS;
}

/* static char* split_string(char* str, char c) {
    int index = -1;
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == c) {
            index = i;
            break;
        }
    }

    char sub[length];
    if(index != -1) {
        strncpy(sub, str, index);
        return sub;
    } else {
        strncpy(sub, str, length);
        return str;
    }
} */

void handle_gps_msg(char *_str) {
    int handle_result = 0;

    if(string_starts_with(_str, "$PMTK705")) {
        printf("Received FW Info: %s", _str);
        handle_result = EXIT_SUCCESS;
    } else if(string_starts_with(_str, "$PMTK001")) {
        printf("Received ACK: %s", _str);
        handle_result = EXIT_SUCCESS;
    } else if(string_starts_with(_str, "$GPGGA")) {
        // Global Positioning System Fixed Data. Time, Position and fix related data
        handle_result = handle_gga_msg(_str);
    } else if(string_starts_with(_str, "$GPGSA")) {
        // GNSS DOP and Active Satellites
        handle_result = handle_gsa_msg(_str);
    } else if(string_starts_with(_str, "$GPGSV")) {
        // GNSS Satellites in View
        handle_result = handle_gsv_msg(_str);
    } else if(string_starts_with(_str, "$GPRMC")) {
        // Recommended Minimum Navigation Information
        handle_result = handle_rmc_msg(_str);
    } else if(string_starts_with(_str, "$GPVTG")) {
        // Course and speed information relative to the ground
        handle_result = handle_vtg_msg(_str);
    }

    if(handle_result == EXIT_FAILURE) {
        print_str("FAILURE: error parsing GPS sentence\n");
    }
}
