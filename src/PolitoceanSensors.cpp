/**
 * @author pettinz
 */

#include <string>

#include <vector>

#include "MqttClient.h"
#include "Sensor.h"
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"
#include "PolitoceanUtils.hpp"

#include "logger.h"
#include "mqttLogger.h"

#include "json.hpp"

#include <Reflectables/Vector.hpp>

#include <fstream>
#include <csignal>

using namespace Politocean;
using namespace Politocean::Constants;

std::ofstream file;

void signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;

    if (file.is_open())
        file.close();
}

/***************************************************
 * Listener class for subscriber
 **************************************************/

class Listener
{
public:
    std::string action();

    void listenForSensor(Types::Vector<Sensor<float>> sensors);
};

void Listener::listenForSensor(Types::Vector<Sensor<float>> sensors)
{
    file << sensors.stringify() << std::endl;
}

/***************************************************
 * Main section
 **************************************************/

int main(int argc, const char *argv[])
{
    signal(SIGINT, signalHandler);

    if (argc < 2)
    {
        std::cout << "No file found." << std::endl;
        exit(EXIT_FAILURE);
    }

    file.open(std::string(argv[1]));

    MqttClient &subscriber = MqttClient::getInstance("PIPPO", Hmi::IP_ADDRESS);

    Listener listener;

    subscriber.subscribeTo(Topics::SENSORS, &Listener::listenForSensor, &listener);
    subscriber.wait();

    return 0;
}
