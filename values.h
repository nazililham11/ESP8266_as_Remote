/** Speeds */
int move_speed_multiple = 0;
int spot_turn_speed = 0;
int leg_move_speed = 0;
int body_move_speed = 0;
int stand_seat_speed = 0;


/** Leg Coordinates*/
float front_left_x = 0.0;
float front_left_y = 0.0;
float front_left_z = 0.0;

float front_right_x = 0.0;
float front_right_y = 0.0;
float front_right_z = 0.0;

float rear_left_x = 0.0;
float rear_left_y = 0.0;
float rear_left_z = 0.0;

float rear_right_x = 0.0;
float rear_right_y = 0.0;
float rear_right_z = 0.0;


/** Ultrasonic Distance */
float us_front       = 0.0;
float us_front_left  = 0.0;
float us_front_right = 0.0;
float us_left        = 0.0;
float us_right       = 0.0;


/** Infrared Distance */
float ir_dist_front = 0.0;
float ir_dist_left  = 0.0;
float ir_dist_right = 0.0;


/** Infrared Line */
float ir_line_1 = 0.0;
float ir_line_2 = 0.0;
float ir_line_3 = 0.0;

/** Thermal Image */
float pixels[64] = { 0, 0, 0, 0, 24, 0, 0, 12, 0, 56, 0, 0, 132, 0, 0, 189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        255, 255, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0, 200, 0, 50, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 210, 0, 0, 10, 25, 0 };

