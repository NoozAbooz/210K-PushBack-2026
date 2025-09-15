#include "main.h"

rd_view_t *homeview = rd_view_create("Home");
rd_view_t *sensorview = rd_view_create("Sensors");
rd::Console console;
rd_view_t *allianceview = rd_view_create("Alliance Colour");
rd_view_t *gifview = rd_view_create("Shikanoko");

// alliance select
lv_style_t style_text_large;
static lv_obj_t *red_btn, *blue_btn, *next_btn;
std::string alliance = "na";

#define BORDER_WIDTH 8
#define HIGHLIGHT_COLOR lv_color_hex(0xFFFF00)

static void highlight_button(lv_obj_t *btn) {
    lv_obj_set_style_border_width(red_btn, (btn == red_btn) ? BORDER_WIDTH : 0, 0);
    lv_obj_set_style_border_width(blue_btn, (btn == blue_btn) ? BORDER_WIDTH : 0, 0);
    lv_obj_set_style_border_color(btn, HIGHLIGHT_COLOR, 0);
}

static void btn_event_cb(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t *btn = lv_event_get_target(e);
        alliance = ((btn == red_btn) ? "red" : "blue");
        highlight_button(btn);
        
        if (!next_btn) {
            next_btn = lv_btn_create(lv_obj_get_parent(btn));
            lv_obj_set_size(next_btn, 100, 60);
            lv_obj_align(next_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
            lv_obj_set_style_bg_color(next_btn, lv_color_hex(0x64ff64), 0);
            lv_obj_add_event_cb(next_btn, [](lv_event_t *e) { gui_selector.focus(); }, LV_EVENT_CLICKED, NULL);
            lv_label_set_text(lv_label_create(next_btn), "Next ->");
        }
        lv_obj_clear_flag(next_btn, LV_OBJ_FLAG_HIDDEN);
        console.printf("Alliance set to: %s\n", alliance.c_str());
    }
}

void render_alliance_view() {
    lv_obj_t *parent = rd_view_obj(allianceview);
    
    red_btn = lv_btn_create(parent);
    blue_btn = lv_btn_create(parent);
    
    for (int i = 0; i < 2; i++) {
        lv_obj_t *btn = (i == 0) ? red_btn : blue_btn;
        lv_obj_set_size(btn, lv_pct(45), lv_pct(80));
        lv_obj_align(btn, i == 0 ? LV_ALIGN_LEFT_MID : LV_ALIGN_RIGHT_MID, i == 0 ? 10 : -10, 0);
        lv_obj_set_style_bg_color(btn, lv_color_hex(i == 0 ? 0xFF0000 : 0x0000FF), 0);
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
        lv_label_set_text(lv_label_create(btn), i == 0 ? "RED" : "BLUE");
    }
    
    next_btn = NULL;
}

void create_marker(lv_obj_t* parent, double row, double col) {
    lv_obj_t* marker = lv_obj_create(parent);
    lv_obj_set_size(marker, 5, 5);
    lv_obj_set_style_bg_color(marker, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(marker, LV_RADIUS_CIRCLE, 0);
    lv_obj_align(marker, LV_ALIGN_CENTER, row, col);
}

void render_home_view() {
    lv_style_init(&style_text_large);
	lv_style_set_text_opa(&style_text_large, LV_OPA_COVER);
	lv_style_set_text_font(&style_text_large, &lv_font_montserrat_24);

    lv_obj_t* parent = rd_view_obj(homeview);

    // Create a container for the left side content
    lv_obj_t* left_container = lv_obj_create(parent);
    lv_obj_set_size(left_container, 240, 240);  // Half the screen width
    lv_obj_align(left_container, LV_ALIGN_LEFT_MID, 0, 0);

    // Add your centered object here (e.g., an image or another UI element)
    lv_obj_t* centered_obj = lv_obj_create(left_container);
    lv_obj_set_size(centered_obj, 200, 240);  // Example size
    lv_obj_center(centered_obj);
    lv_obj_t *sus = lv_img_create(centered_obj);
    Gif* gif = new Gif("/usd/ayo.gif", sus);

    // Create right side content
    lv_obj_t* right_container = lv_obj_create(parent);
    lv_obj_set_size(right_container, 240, 240);  // Half the screen width
    lv_obj_align(right_container, LV_ALIGN_RIGHT_MID, 0, 0);

    // Add "Kawaii Kittens" text
    lv_obj_t* title = lv_label_create(right_container);
    //lv_label_set_text_fmt(title, "Kawaii Kittens - %f%%", pros::battery::get_capacity());  // weird tomfoolery for percentage sign
    lv_label_set_text(title, "Kawaii Kittens");
    lv_obj_set_style_text_color(title, lv_color_hex(0xfa4482), 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_add_style(title, &style_text_large, 0);

    // Add "Console" button
    lv_obj_t* console_btn = lv_btn_create(right_container);
    lv_obj_t* console_btn_label = lv_label_create(console_btn);
    lv_label_set_text(console_btn_label, "Console");
    lv_obj_center(console_btn_label);
    lv_obj_align(console_btn, LV_ALIGN_BOTTOM_MID, 0, -100);  // Positioned above the Setup button
    lv_obj_add_event_cb(console_btn, [](lv_event_t* e) {
        if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
            console.focus();
        }
    }, LV_EVENT_CLICKED, NULL);

    lv_obj_t* gif_btn = lv_btn_create(right_container);
    lv_obj_t* gif_btn_label = lv_label_create(gif_btn);
    lv_label_set_text(gif_btn_label, "Shikanoko");
    lv_obj_center(gif_btn_label);
    lv_obj_align(gif_btn, LV_ALIGN_BOTTOM_MID, 0, -50);  // Positioned above the Setup button
    lv_obj_add_event_cb(gif_btn, [](lv_event_t* e) {
        if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
            Gif* gif = new Gif("/usd/nokotan.gif", rd_view_obj(gifview));
		    rd_view_focus(gifview);
            rd_view_alert(gifview, "Shika noko tokotoko arawaru nokonoko");
		    console.println("Running gif...");
        }
    }, LV_EVENT_CLICKED, NULL);

    // Add "Setup" button
    lv_obj_t* setup_btn = lv_btn_create(right_container);
    lv_obj_t* btn_label = lv_label_create(setup_btn);
    lv_label_set_text(btn_label, "Setup Auton");
    lv_obj_center(btn_label);
    lv_obj_align(setup_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(setup_btn, [](lv_event_t* e) {
        if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
            rd_view_focus(allianceview);
        }
    }, LV_EVENT_CLICKED, NULL);
}

void render_sensor_view() {
    lv_obj_t* parent = rd_view_obj(sensorview);
    
    lv_obj_t* debug_line_1 = lv_label_create(parent);
    lv_obj_align(debug_line_1, LV_ALIGN_TOP_LEFT, 30, 50);
    lv_label_set_text(debug_line_1, "Debug Line 1: ");

    lv_obj_t* debug_line_2 = lv_label_create(parent);
    lv_obj_align(debug_line_2, LV_ALIGN_TOP_LEFT, 30, 67);
    lv_label_set_text(debug_line_2, "Debug Line 2: ");

    lv_obj_t* debug_line_3 = lv_label_create(parent);
    lv_obj_align(debug_line_3, LV_ALIGN_TOP_LEFT, 30, 84);
    lv_label_set_text(debug_line_3, "Debug Line 3: ");

    lv_obj_t* debug_line_4 = lv_label_create(parent);
    lv_obj_align(debug_line_4, LV_ALIGN_TOP_LEFT, 30, 101);
    lv_label_set_text(debug_line_4, "Debug Line 4: ");

    lv_obj_t* debug_line_5 = lv_label_create(parent);
    lv_obj_align(debug_line_5, LV_ALIGN_TOP_LEFT, 30, 118);
    lv_label_set_text(debug_line_5, "Debug Line 5: ");

    lv_obj_t* debug_line_6 = lv_label_create(parent);
    lv_obj_align(debug_line_6, LV_ALIGN_TOP_LEFT, 30, 135);
    lv_label_set_text(debug_line_6, "Debug Line 6: ");

    lv_obj_t* debug_line_7 = lv_label_create(parent);
    lv_obj_align(debug_line_7, LV_ALIGN_TOP_LEFT, 30, 152);
    lv_label_set_text(debug_line_7, "Debug Line 7: ");

    lv_obj_t* debug_line_8 = lv_label_create(parent);
    lv_obj_align(debug_line_8, LV_ALIGN_TOP_LEFT, 30, 169);
    lv_label_set_text(debug_line_8, "Debug Line 8: ");

    lv_obj_t* debug_line_9 = lv_label_create(parent);
    lv_obj_align(debug_line_9, LV_ALIGN_TOP_LEFT, 30, 186);
    lv_label_set_text(debug_line_9, "Debug Line 9: ");

    while (true) {
        char buffer[300];

        sprintf(buffer, "X: %.2f | Y: %.2f | HEADING: %.3f°", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
        lv_label_set_text(debug_line_1, buffer);

        sprintf(buffer, "TEMPERATURE  L:%.2f°C | R:%.2f°C | Batt:%.2f°C", leftDrive.get_temperature(), rightDrive.get_temperature(), pros::battery::get_temperature());
        lv_label_set_text(debug_line_2, buffer);

        sprintf(buffer, "INTAKE  TOP:%.2f°C | MID:%.2f°C | BOTTOM:%.2f°C", intakeTop.get_temperature(), intakeMiddleUpper.get_temperature(), intakeMiddleLower.get_temperature(), intakeBottom.get_temperature());
        lv_label_set_text(debug_line_3, buffer);

        // auto auton = gui_selector.get_auton();
        // const char* auton_name = auton->name.c_str();
        sprintf(buffer, "ALLIANCE: %s", alliance.c_str());
        lv_label_set_text(debug_line_4, buffer);

        int total_seconds = pros::millis() / 1000;
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;
        sprintf(buffer, "Time Elapsed (min:sec): %d:%02d", minutes, seconds);
        lv_label_set_text(debug_line_5, buffer);
    
        sprintf(buffer, "Radio Status: %s", controller.is_connected() ? "Connected" : "Disconnected");
        lv_label_set_text(debug_line_6, buffer);

        const char* competition_status_str = (pros::competition::get_status() == 7) ? "Disabled" : (pros::competition::get_status() == 6) ? "Autonomous" : (pros::competition::get_status() == 4) ? "Driver Control" : "Not Connected";
        sprintf(buffer, "Competition Status: %s", competition_status_str);
        lv_label_set_text(debug_line_7, buffer);

        sprintf(buffer, "Distance Sensors  Fwd: %.2fin | Right: %.2fin", (float)(fwdDistance.get_distance() / 25.4), (float)(rightDistance.get_distance() / 25.4));
        lv_label_set_text(debug_line_8, buffer);

        pros::delay(200); // Update every 200 milliseconds
    }
}

void rdconfig_init() {
    render_home_view();
	render_alliance_view();
    pros::Task([] {
	    render_sensor_view();
    });
	rd_view_focus(homeview);
}