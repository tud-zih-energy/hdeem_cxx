#include "../include/hdeem_cxx.hpp"

#include <cmath>
#include <iostream>

void get_stats(hdeem::connection& con, double begin_unix_s, double end_unix_s)
{
    auto globals = con.get_global();
    
    const auto& status = con.get_status();
    double hdeem_duration = (double)(status.stop_time_blade.tv_sec - status.start_time_blade.tv_sec)
                    + ((double)status.stop_time_blade.tv_nsec - (double)status.start_time_blade.tv_nsec) / 1e9;
    double hdeem_start_unix_s = status.start_time_blade.tv_sec
                                + (double)status.start_time_blade.tv_nsec / 1000000000;
    
    std::cout << "sensor, avg, min, max, energy, total samples, interval samples" << std::endl;
    for (auto sensor : con.sensors()) {
        std::cout << con.sensor_name(sensor) << ", ";
        const auto& data = globals.get_single_sensor_data(sensor);
        
        if (begin_unix_s < hdeem_start_unix_s) {
            throw std::runtime_error("Requested start time is before hdeem_start time.");
        }
        double sample_rate = data.size() / hdeem_duration;
        int64_t begin_index = ceil((begin_unix_s - hdeem_start_unix_s) * sample_rate);
        int64_t end_index = ceil((end_unix_s - hdeem_start_unix_s) * sample_rate);
        if (begin_index < 0) {
            throw std::runtime_error("Strangely the begin index is < 0");
        }
        if (end_index > data.size()) {
            throw std::runtime_error("Requested end time is after hdeem_stop time.");
        }
        double sum = 0;
        float min = std::numeric_limits<float>::max();
        float max = std::numeric_limits<float>::min();
        int64_t count = 0;
        for (auto timeval : data) {
            if (begin_index <= timeval.first && timeval.first <= end_index) {
                auto val = timeval.second;
                sum += val;
                min = std::min(min, val);
                max = std::max(max, val);
                count++;
            }
        }
        auto avg_power = sum / count;
        auto energy = avg_power * (end_unix_s - begin_unix_s);
        std::cout << avg_power << ", " << min << ", " << max << ", " << energy
                  << ", " << data.size() << ", " << count << std::endl;
    }
}


int main(int argc, const char** argv)
{
    // Basically all hdeem functions may throw some runtime error..
    try {
        std::unique_ptr<hdeem::connection> con;
        // currently only inband
        con.reset(new hdeem::connection());
        if (argc != 3)
        {
            std::cerr << "Invalid number of parameters:" << std::endl;
            std::cerr << argv[0] << " start_time end_time" << std::endl;
            std::cerr << "Both timestamps should be unix epoch milliseconds" << std::endl;
            return -1;
        }

        con->stop();
        get_stats(*con, atof(argv[1]), atof(argv[2]));
    }
    catch (std::runtime_error& e) {
        std::cerr << "An exception occured: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
