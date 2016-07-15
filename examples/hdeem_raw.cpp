#include <hdeem_cxx.hpp>

extern "C" {
#include <hdeem.h>
}

#include <iostream>

void test_global(hdeem_bmc_data& bmc)
{
    hdeem_global_reading_t readings;
    auto ret = hdeem_get_global(&bmc, &readings);
    if (ret) {
        std::cerr << "hdeem_get_global failed with rc: " << ret << std::endl;
        return;
    }
    for (bool is_blade : { true, false })
    {
        int count = is_blade ? bmc.nb_blade_sensors : bmc.nb_vr_sensors;
        for (int sensor_id = 0; sensor_id < count; sensor_id++)
        {
            std::string sensor_name =
                    is_blade ? bmc.name_blade_sensors[sensor_id] : bmc.name_vr_sensors[sensor_id];
            std::cout << "Getting values for " << sensor_name << std::endl;
            double sum = 0.0;
            size_t sz = is_blade ? readings.nb_blade_values : readings.nb_vr_values;
            for (size_t index = 0; index < sz; index++)
            {
                double value;
                if (is_blade)
                {
                    value = readings.blade_power[index].value[sensor_id];
                }
                else
                {
                    value = readings.vr_power[index].value[sensor_id];
                }
                if (index < 10 || (sz - index) < 10 || (index % 1000) == 0)
                {
                    std::cout << index << ": " << value << std::endl;
                }
                sum += value;
            }
            std::cout << " average of " << sz << " values: " << (sum / sz) << " W" << std::endl;
        }
    }
    hdeem_data_free(&readings);
}
int main(int argc, const char* argv[])
{
    // I leave it as an exercise to convert all the initialization back to raw C hdeem stuff...
    try
    {
        std::unique_ptr<hdeem::connection> con;
        if (argc == 5)
        {
            std::string host(argv[2]);
            std::string user(argv[3]);
            std::string pass(argv[4]);
            con.reset(new hdeem::connection(host, user, pass));
        }
        else if (argc == 2)
        {
            con.reset(new hdeem::connection());
        }
        else
        {
            std::cerr << "Invalid number of parameters, use either of the following:" << std::endl;
            std::cerr << argv[0] << " sleep_time_s" << std::endl;
            std::cerr << argv[0] << " sleep_time_s bmc-host bmc-user bmc-pass" << std::endl;
            return -1;
        }
        auto sleep_time = std::chrono::seconds(atoi(argv[1]));

        con->start();
        std::this_thread::sleep_for(sleep_time);
        con->stop();

        test_global(con->bmc());
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "An exception occured: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
