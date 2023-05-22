#include "gps.h"

// Prototypes for functions used for parsing GPS infos from received UART string
void parse_gga(const char *_gga);       // $GPGGA
void parse_gsa(const char *_gsa);       // $GPGSA
void parse_gsv(const char *_gsv);       // $GPGSV
void parse_rmc(const char *_rmc);       // $GPRMC
void parse_vtg(const char *_vtg);       // $GPVTG

void parse_gga(const char *_gga) {
    struct minmea_sentence_gga frame;
    bool res = minmea_parse_gga(&frame, _gga);
    if(!res) {
        print_str("FAILURE: error parsing GPS sentence\n");
    } else {
        print_str("GGA -> parsed coordinates: lat=");
        print_float(minmea_tocoord(&frame.latitude), 6);
        print_str(" lon=");
        print_float(minmea_tocoord(&frame.longitude), 6);
        print_str("\n");
    }
}

void parse_gsa(const char *_gsa) {
    printf("parse_gsa: %s\n", _gsa);
}

void parse_gsv(const char *_gsv) {
    printf("parse_gsv: %s\n", _gsv);
}

/* GPRMC: RMC—Recommended Minimum Navigation Information
    Example: $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C
    - UTC TIME: 064951.000
    - Status: A (valid)
    - Latitude: 2307.1256
    - N/S Indicator: N (north)
    - Longitude: 12016.4438
    - E/W Indicator: E (east)
    - Speed over ground: 0.03 knots
    - Course over ground: 165.48 degrees
    - Date: 260406 (ddmmyy)
    - Magnetic Variation: 3.05 degrees, W (west)
    - Mode: A (autonomous)
    - Checksum: *2C
*/
void parse_rmc(const char *_rmc) {
    struct minmea_sentence_rmc frame;
    bool res = minmea_parse_rmc(&frame, _rmc);
    if(!res) {
        print_str("FAILURE: error parsing GPS sentence\n");
        if(!frame.valid){
            print_str("WARNING: RMC data not valid\n");
        }
    } else {
        print_str("=== RMC RESULT ===\n");
        printf("- valid: %s\n", frame.valid ? "true" : "false");
        printf("- Coordinates: lat=%f, lon=%f\n", minmea_tocoord(&frame.latitude), minmea_tocoord(&frame.longitude));
        printf("- Speed: %f\n", minmea_tofloat(&frame.speed));
        printf("- Date: %02d.%02d.20%02d\n", frame.date.day, frame.date.month, frame.date.year);
        //print_str("\n");
    }
}

void parse_vtg(const char *_vtg) {
    printf("parse_vtg: %s\n", _vtg);
}

int parse_gps_string(const char *_str) {
    //printf("parse_gps_string: %s\n", _str);
    //const char *_gll = "$GNGLL,5229.0178,N,01326.7605,E,114350.000,A,A*45";
    const char* prefix_gga = "$GPGGA"; // Global Positioning System Fixed Data. Time, Position and fix related data
    const char* prefix_gsa = "$GPGSA"; // GNSS DOP and Active Satellites
    const char* prefix_gsv = "$GPGSV"; // GNSS Satellites in View
    const char* prefix_rmc = "$GPRMC"; // Recommended Minimum Navigation Information
    const char* prefix_vtg = "$GPVTG"; // Course and speed information relative to the ground
    int cmp_result;

    enum minmea_sentence_id sentence = minmea_sentence_id(_str, false);
    if(sentence != -1) {
        printf("minmea sentence: %d\n", sentence);
    }

    switch (sentence) {
        case MINMEA_SENTENCE_GGA: {
            parse_gga(_str);
            return EXIT_SUCCESS;
        } break;
        case MINMEA_SENTENCE_GSA: {
            parse_gsa(_str);
            return EXIT_SUCCESS;
        } break;
        case MINMEA_SENTENCE_GSV: {
            parse_gsv(_str);
            return EXIT_SUCCESS;
        } break;
        case MINMEA_SENTENCE_RMC: {
            parse_rmc(_str);
            return EXIT_SUCCESS;
        } break;
        case MINMEA_SENTENCE_VTG: {
            parse_vtg(_str);
            return EXIT_SUCCESS;
        } break;
        default: {
            //print_str("FAILURE: error parsing GPS sentence\n");
            return EXIT_FAILURE;
        }
    }

    cmp_result = strncmp(_str, prefix_gga, strlen(prefix_gga));
    if(cmp_result == 0) {
        parse_gga(_str);
        return EXIT_SUCCESS;
    }

    cmp_result = strncmp(_str, prefix_gsa, strlen(prefix_gsa));
    if(cmp_result == 0) {
        parse_gsa(_str);
        return EXIT_SUCCESS;
    }

    cmp_result = strncmp(_str, prefix_gsv, strlen(prefix_gsv));
    if(cmp_result == 0) {
        parse_gsv(_str);
        return EXIT_SUCCESS;
    }

    cmp_result = strncmp(_str, prefix_rmc, strlen(prefix_rmc));
    if(cmp_result == 0) {
        parse_rmc(_str);
        return EXIT_SUCCESS;
    }

    cmp_result = strncmp(_str, prefix_vtg, strlen(prefix_vtg));
    if(cmp_result == 0) {
        parse_vtg(_str);
        return EXIT_SUCCESS;
    }

    print_str("FAILURE: error parsing GPS sentence\n");
    return EXIT_FAILURE;
}