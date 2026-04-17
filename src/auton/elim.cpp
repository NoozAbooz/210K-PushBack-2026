#include "abstractGlobals.hpp"
#include "deviceGlobals.hpp"
#include "libKW/drivetrain/chassis.hpp"
#include "libKW/drivetrain/movements.hpp"
#include "main.h"
#include "libKW/api.hpp"
#include "pros/motors.h"

void right_elim() {
      pros::Task([] {
        intakeMacro("L1");
        pros::delay(390);
        loaderPiston.set_value(true);
       // blockerPiston.set_value(true);
        pros::delay(300);
        loaderPiston.set_value(false);
        pros::delay(1100);
        loaderPiston.set_value(true);
    });
    kw::moveToPoint(6, 21.67, 1000, true, 127, false); // Group of 3
    kw::boomerang(30.7, 39.00, 90, 0.4, 1300, true, 75); // Under Bar
    pros::delay(80);
    kw::moveToPoint(18, 21.67, 1000, false, 127, false); // Backing Out
    kw::boomerang(38, 6, 180, 0.5, 2000, false, 90); // moving to long goal
    // pros::Task([]{
    //     pros::delay(450);
    //         intakeMacro("R1");
    //         pros::delay(1500);
    //         intakeMacro("L1");

    // });
    // kw::moveToPoint(38.4, 19, 1000, false);  //at long goal
    // kw::move_raw(-7000, -7000);
    // loaderPiston.set_value(true);
    // pros::delay(700);
    kw::moveToPoint(38, -14, 700, true, 70, false); // drive to loader
    kw::move_raw(6000, 6000);
    pros::delay(250);
         pros::Task([]{
        pros::delay(650);
            intakeMacro("R1");
            pros::delay(850);
            intakeMacro("stop");
    });
    kw::moveToPoint(38.4, 19, 1000, false);  //at long goal
    kw::move_raw(-7000, -7000);
    pros::delay(1100);
    kw::turnToAngle(315, 1000);
    loaderPiston.set_value(false);
    kw::boomerang(2.3, 38.5, 315, 0.3, 2000 , true, 80);  // mid goal
    intakeMacro("L2");
    intakeMain.move_voltage(-5000);
    intakeSub.move_voltage(-5000);
   // kw::move_raw(1000, 1000); 
    // pros::delay(300);
    // pros::Task([]{
    //     pros::delay(400);
    //     intakeMacro("stop");
    //     pros::delay(1300);
    //     intakeMacro("L2");
    //     intakeMain.move_voltage(-7000);
    //     pros::delay(4000);
    //     intakeMacro("stop");
    //     intake.move_voltage(0);
    // });
    // kw::moveToPoint(38, 1, 1000, false, 127, false);
    // loaderPiston.set_value(false);
    // kw::turnToAngle(315, 700);
    // kw::moveToPoint(2, 37.5, 2000); // mid goal
    // pros::delay(2000);
    // kw::moveToPoint(29, 15, 1000, false); // move to Wing
    // kw::turnToAngle(0, 700);
    // kw::moveToPoint(29, 40, 8000, true, 100); // WIng

    // //kw::boomerang(-1.5, 34 , 315, 0.3, 2000 , false, 127);  // mid goal
}

void left_elim() {
    pros::Task([] {
        intakeMacro("L1");
        pros::delay(390);
        loaderPiston.set_value(true);
       // blockerPiston.set_value(true);
        pros::delay(300);
        loaderPiston.set_value(false);
        pros::delay(1100);
        loaderPiston.set_value(true);
    });
    kw::moveToPoint(-6, 21.67, 1000, true, 127, false); // Group of 3
    kw::boomerang(-27, 40.50, 270, 0.3, 2500, true, 60); // Under Bar
    pros::delay(200);
    kw::moveToPoint(-13, 21.67, 1000, false, 127, false); // Backing Out
    loaderPiston.set_value(false);
    kw::boomerang(-38, 9, 180, 0.5, 2000, false, 70); // moving to long goal
    pros::Task([]{
        pros::delay(450);
            intakeMacro("R1");
            pros::delay(1500);
            intakeMacro("L1");

    });
    kw::moveToPoint(-38.4, 19, 1000, false);  //at long goal
    kw::move_raw(-7000, -7000);
    loaderPiston.set_value(true);
    pros::delay(700);
    kw::moveToPoint(-38.5, -14, 1000, true, 70, false); // drive to loader
    kw::move_raw(6000, 6000);
    pros::delay(300);
    pros::Task([]{
        pros::delay(2000);
        intakeMacro("R2");
        pros::delay(1500);
        intakeMacro("L1");
        intake.move_voltage(0);
    });
    kw::boomerang(-1.5, 34 , 215, 0.3, 2000 , false, 127);  // mid goal
    kw::move_raw(-4000, -4000);
    pros::delay(800);
    kw::moveToPoint(-25.4, 17, 1000); // move to Wing
    kw::turnToAngle(180, 700);
    kw::moveToPoint(-27, 37, 1000, false); // WIng



}

void left_7() {

   pros::Task([] {
        intakeMacro("L1");
        pros::delay(650);
        loaderPiston.set_value(true);
        //blockerPiston.set_value(true);
    });
    kw::moveToPoint(-5.8, 21.67, 1000, true, 80, false); // group of three
    kw::turnToAngle(233, 700);
    kw::moveToPoint(-31.59, 1.93, 2000, true, 127);  //drive to loader
    kw::turnToAngle(180, 700);
    kw::moveToPoint(-32.95, -10.5, 900, true, 65); //loader
    kw::move_raw(7000, 7000);
    pros::delay(210);
    pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(400);
		intakeMacro("R1");
	});
    kw::moveToPoint(-34.09, 24.45, 1000, false, 127); //long goal
    kw::move_raw(-5000, -5000);
    pros::delay(1600);
    kw::moveToPoint(-22.3, 16.94, 1000, true, 127); //align for wing
    kw::turnToAngle(180, 700);
    //intake_velocity.set_target(0);
    loaderPiston.set_value(false);
    kw::moveToPoint(-23.803, 34.84, 8000, false, 80); //wing
    // kw::turnToAngle(180, 700);
    //kw::driveTo(-1, 1000, 70);
    stopIntake();
    kw::boomerang(-25, 31, 226, 0.3, 1000, true, 100); //turn into post
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);

    
   // **old Stuff below**
   
    //  toggleColourSort = true;
    //  intakeMacro("L1");
    //  pros::Task([] {
    //     pros::delay(750);
    //     loaderPiston.set_value(true);
    // });
    // kw::driveTo(28.5, 2000, 60);
    // kw::turnToAngle(236, 1000);
    // kw::moveToPoint(-30, 17, 2000);
    // kw::turnToAngle(200, 1000);    
    // kw::moveToPoint(-34.37, 2.7, 1000, true, 70);
    // kw::move_raw(3000, 3000);
    // pros::delay(70);
    // //pros::delay(50);
    // //kw::driveTo(-33, 1000);
    // kw::moveToPoint(-25.2, 33.3, 1000, false);
    // kw::move_raw(-10000, -10000);
    // //stopIntake();
    // pros::delay(200);
    // //toggleColourSort = true;
    // intakeMacro("R1");
    // loaderPiston.set_value(false);
    // pros::delay(2300);
    // stopIntake();
    // kw::moveToPoint(-20.7, 10, 1000);
    // kw::turnToAngle(204, 1000);
    // kw::moveToPoint(-8.7, 48, 8000, false, 60);
    //     kw::turnToAngle(204, 1000);
    // //kw::driveTo(-7, 1000);

}

void right_7() {
pros::Task([] {
        intakeMacro("L1");
        pros::delay(680);
        loaderPiston.set_value(true);
        //blockerPiston.set_value(true);
    });
    kw::moveToPoint(6, 21.67, 1000, true, 70, false); // Loader #1
    kw::turnToAngle(127, 700);
    kw::moveToPoint(32.59, 1.93, 2000, true, 127); 
    kw::turnToAngle(180, 700);
    kw::moveToPoint(34.95, -10.5, 700, true, 70); // Long Goal #1
    //kw::driveTo(3, 1000, 70);
    kw::move_raw(7000, 7000);
    pros::delay(180);
    pros::Task([] {
		pros::delay(300);
		stopIntake();
		pros::delay(400);
		intakeMacro("R1");
        loaderPiston.set_value(false);
	});
    kw::moveToPoint(34.89, 24.45, 1000, false, 127);
    kw::move_raw(-5000, -5000);
    pros::delay(1600);
    kw::moveToPoint(47, 12.94, 1000, true, 127);
    kw::turnToAngle(180, 700);
    //intake_velocity.set_target(0);
    kw::moveToPoint(46, 32, 8000, false, 100);
    kw::boomerang(44, 32, 226, 0.3, 1000, true, 100);
    kw::stop_chassis(pros::E_MOTOR_BRAKE_HOLD);
    //old stuff below

//     toggleColourSort = false;
//      intakeMacro("L1");
//     kw::driveTo(28.5, 2000, 60);
//     kw::turnToAngle(124, 1000);
//     kw::moveToPoint(30, 17, 2000);
//     loaderPiston.set_value(true);
//     kw::turnToAngle(160, 1000);    
//     kw::moveToPoint(34.87, 2.7, 1500, true, 70);
//     kw::move_raw(7000, 7000);
//     pros::delay(50);
//     //kw::driveTo(-33, 1000);
//     kw::moveToPoint(25.0, 33.3, 1000, false);
//     kw::move_raw(-8000, -8000);
//     //stopIntake();
//     pros::delay(200);
//     toggleColourSort = true;
//     intakeMacro("R1");
//     loaderPiston.set_value(false);
//     pros::delay(2200);
//     stopIntake();
//     kw::moveToPoint(+38.1, 23.53, 1000);
//     kw::turnToAngle(164, 1000);
//     kw::moveToPoint(+30.0, 51, 8000, false, 70);
//     kw::driveTo(-7, 1000);
//     kw::turnToAngle(164, 1000);
}