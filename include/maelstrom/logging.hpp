#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

//inclusions
#include "api.h"
#include <fstream>

namespace maelstrom {
    namespace logging {
        //declarations of namespace functions
        typedef enum {
            E_YEAR,
            E_MONTH,
            E_DAY,
            E_DATE,
            E_TIME,
            E_DATE_TIME,
            E_DATE_TIME_FILE_PATH_FORMAT,
            E_NONE
        } date_time_format;

        typedef enum {
            E_ERROR_LOG,
            E_DATA_LOG
        } log_file;

        extern std::vector<std::vector<bool>> faults;
        bool* init(bool run_error_log, bool run_data_log, std::vector<int> left_motor_ports, std::vector<int> right_motor_ports, int battery_threshold);
        bool battery(int battery_threshold);
        std::string get_current_date_time();
        void robot_faults_log();
        bool motor_connected(int port);
        void motor_fault_log (int port_index, uint32_t motor_fault);
        void robot_coords_log(void);
        void set_robot_coords(double x, double y, double theta);
        void set_timezone (const char* timezone_string);
        void task_complete(std::string task_name, bool completion);
        void write_to_file(std::string message, log_file file);
    }
}  

#endif