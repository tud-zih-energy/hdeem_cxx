#include <hdeem_cxx.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>

void test_global(hdeem::connection& con)
{
    auto all_sensor_data = con.get_global();
    for (auto sensor : con.sensors())
    {
        std::cout << "Getting values for " << con.sensor_name(sensor) << std::endl;
        auto sensor_data = all_sensor_data.get_single_sensor_data(sensor);
        double sum = 0.0;
        for (auto elem : sensor_data)
        {
            auto index = elem.first;
            auto value = elem.second;
            if (index < 10 || (sensor_data.size() - index) < 10 || (index % 1000) == 0)
            {
                std::cout << index << ": " << value << std::endl;
            }
            sum += value;
        }
        std::cout << " average of " << sensor_data.size() << " values: " << (sum / sensor_data.size()) << " W"
                  << std::endl;
    }
}

int main(int argc, const char* argv[])
{
    // Basically all hdeem functions may throw some runtime error..
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

        test_global(*con);
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "An exception occured: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
