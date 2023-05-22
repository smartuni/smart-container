#include "gps.h"

// Prototypes for functions used for parsing GPS infos from received UART string

/**
 * Parses a NMEA Output Sentence - GGA (Time, position and fix type data)
 * Example: $GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65
*/
int parse_gga(const char *_gga);

/**
 * Parses a NMEA Output Sentence - GSA (GPS receiver operating mode, active satellites used in the position solution and DOP values)
 * Example: $GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00
*/
int parse_gsa(const char *_gsa);

/**
 * Parses a NMEA Output Sentence - GSV (The number of GPS satellites in view satellite ID numbers, elevation, azimuth, and SNR values)
 * Examples:
 * - $GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D
 * - $GPGSV,3,2,09,18,26,314,40,09,57,170,44,06,20,229,37,10,26,084,37*77
 * - $GPGSV,3,3,09,07,,,26*73
*/
int parse_gsv(const char *_gsv);

/**
 * Parses a NMEA Output Sentence - RMC (Time, date, position, course and speed data. Recommended Minimum Navigation Information)
 * Example: $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C
*/
int parse_rmc(const char *_rmc);

/**
 * Parses a NMEA Output Sentence - VTG (Course and speed information relative to the ground)
 * Example: $GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37
*/
int parse_vtg(const char *_vtg);

int parse_gga(const char *_gga) {
    struct minmea_sentence_gga frame;
    bool res = minmea_parse_gga(&frame, _gga);
    if(!res) {
        return EXIT_FAILURE;
    }

    print_str("\n=== GGA RESULT ===\n");
    print_str("- Coordinates: lat=");
    print_float(minmea_tocoord(&frame.latitude), 6);
    print_str(" lon=");
    print_float(minmea_tocoord(&frame.longitude), 6);
    print_str("\n");
    return EXIT_SUCCESS;
}

int parse_gsa(const char *_gsa) {
    struct minmea_sentence_gsa frame;
    bool res = minmea_parse_gsa(&frame, _gsa);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    print_str("\n=== GSA RESULT ===\n");
    printf("...\n");
    return EXIT_SUCCESS;
}

int parse_gsv(const char *_gsv) {
    struct minmea_sentence_gsv frame;
    bool res = minmea_parse_gsv(&frame, _gsv);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    print_str("\n=== GSV RESULT ===\n");
    printf("Total satellites: %d\n", frame.total_sats);
    return EXIT_SUCCESS;
}

int parse_rmc(const char *_rmc) {
    struct minmea_sentence_rmc frame;
    bool res = minmea_parse_rmc(&frame, _rmc);
    if(!res) {
        return EXIT_FAILURE;
    }

    print_str("\n=== RMC RESULT ===\n");
    printf("- valid: %s\n", frame.valid ? "true" : "false");
    printf("- Coordinates: lat=%f, lon=%f\n", minmea_tocoord(&frame.latitude), minmea_tocoord(&frame.longitude));
    printf("- Speed: %f\n", minmea_tofloat(&frame.speed));
    printf("- Date: %02d.%02d.20%02d\n", frame.date.day, frame.date.month, frame.date.year);

    return EXIT_SUCCESS;
}

int parse_vtg(const char *_vtg) {
    struct minmea_sentence_vtg frame;
    bool res = minmea_parse_vtg(&frame, _vtg);
    if(!res) {
        return EXIT_FAILURE;
    }
    
    print_str("\n=== VTG RESULT ===\n");
    printf("- FAA mode: %d\n- mag. degrees: %f\n- true degrees: %f\n", frame.faa_mode, minmea_tofloat(&frame.magnetic_track_degrees), minmea_tofloat(&frame.true_track_degrees));
    return EXIT_SUCCESS;
}

mutex_t mutex_gps;

int parse_gps_string(const char *_str) {

/*     
    enum minmea_sentence_id sentence = minmea_sentence_id(_str, false);
    printf("%s -> minmea sentence %d\n", _str, sentence);

    int res;
    switch (sentence) {
        case MINMEA_SENTENCE_GGA: {
            res = parse_gga(_str);
        } break;
        case MINMEA_SENTENCE_GSA: {
            res = parse_gsa(_str);
        } break;
        case MINMEA_SENTENCE_GSV: {
            res = parse_gsv(_str);
        } break;
        case MINMEA_SENTENCE_RMC: {
            res = parse_rmc(_str);
        } break;
        case MINMEA_SENTENCE_VTG: {
            res = parse_vtg(_str);
        } break;
        default: {
            //print_str("FAILURE: error parsing GPS sentence\n");
            res = EXIT_FAILURE;
        }
    }

    return res; */

    const char* prefix_gga = "$GPGGA"; // Global Positioning System Fixed Data. Time, Position and fix related data
    const char* prefix_gsa = "$GPGSA"; // GNSS DOP and Active Satellites
    const char* prefix_gsv = "$GPGSV"; // GNSS Satellites in View
    const char* prefix_rmc = "$GPRMC"; // Recommended Minimum Navigation Information
    const char* prefix_vtg = "$GPVTG"; // Course and speed information relative to the ground
    int cmp_result;

    cmp_result = strncmp(_str, prefix_gga, strlen(prefix_gga));
    if(cmp_result == 0) {
        return parse_gga(_str);
    }

    cmp_result = strncmp(_str, prefix_gsa, strlen(prefix_gsa));
    if(cmp_result == 0) {
        return parse_gsa(_str);
    }

    cmp_result = strncmp(_str, prefix_gsv, strlen(prefix_gsv));
    if(cmp_result == 0) {
        return parse_gsv(_str);
    }

    cmp_result = strncmp(_str, prefix_rmc, strlen(prefix_rmc));
    if(cmp_result == 0) {
        return parse_rmc(_str);
    }

    cmp_result = strncmp(_str, prefix_vtg, strlen(prefix_vtg));
    if(cmp_result == 0) {
        return parse_vtg(_str);
    }

    print_str("FAILURE: error parsing GPS sentence\n");

    return EXIT_FAILURE;
}