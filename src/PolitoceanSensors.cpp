/**
 * @author pettinz
 */

#include "MqttClient.h"
#include "Sensor.h"
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"
#include "PolitoceanUtils.hpp"

#include "logger.h"
#include "mqttLogger.h"

#include "json.hpp"

#include <Reflectables/Vector.hpp>

/***************************************************
 * Listener class for subscriber
 **************************************************/

using namespace Politocean;
using namespace Politocean::Constants;

class Listener
{
    Types::Vector<Sensor<float>> sensors_;

    bool sensorsUpdated_;

public:
    Listener() : sensorsUpdated_(false)
    {
        for (auto sensor_type : sensor_t())
            sensors_.emplace_back(Sensor<float>(sensor_type, 0));
    }

    std::string action();

    Types::Vector<Sensor<float>> &sensors();

    void listenForSensor(Types::Vector<Sensor<float>> sensors);

    bool isSensorsUpdated();
};

void Listener::listenForSensor(Types::Vector<Sensor<float>> sensors)
{
    sensors_ = sensors;

    sensorsUpdated_ = true;
}

Types::Vector<Sensor<float>> &Listener::sensors()
{
    sensorsUpdated_ = false;

    return sensors_;
}

bool Listener::isSensorsUpdated()
{
    return sensorsUpdated_;
}

/***************************************************
 * Talker class for sensors
 **************************************************/

class Talker
{
    bool isTalking_;
    Types::Vector<Sensor<float>> sensors;

public:
    Talker() : isTalking_(false) {}

    void startTalking(Listener &listener);
    void stopTalking();

    bool isTalking();
};

void Talker::startTalking(Listener &listener)
{
    while (1)
        if (listener.isSensorsUpdated())
        {
            sensors = listener.sensors();
            std::cout << "READ" << std::endl;
        }
}

void Talker::stopTalking()
{
}

bool Talker::isTalking()
{
    return isTalking_;
}

/***************************************************
 * Main section
 **************************************************/

int main(int argc, const char *argv[])
{
    logger::enableLevel(logger::DEBUG);

    MqttClient &subscriber = MqttClient::getInstance("PIPPO", Hmi::IP_ADDRESS);

    Listener listener;

    subscriber.subscribeTo(Topics::SENSORS, &Listener::listenForSensor, &listener);

    Talker talker;

    talker.startTalking(listener);

    subscriber.wait();

    talker.stopTalking();

    return 0;
}
