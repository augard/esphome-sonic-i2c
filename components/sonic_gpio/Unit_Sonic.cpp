#include "Unit_Sonic.h"

/*! @brief Initialize the Sonic. */
void SONIC_IO::begin(uint8_t trig, uint8_t echo) {
    _trig = trig;
    _echo = echo;
    pinMode(_trig,
            OUTPUT);  // Sets the trigPin as an Output. 将 TrigPin 设置为输出
    pinMode(_echo,
            INPUT);  // Sets the echoPin as an Input. 将 echoPin 设置为输入
}

float SONIC_IO::getDuration() {
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds.
    // 将TrigPin设定为高电平状态，持续10微秒。

    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    //读取echoPin，返回以微秒为单位的声波移动时间
    float duration = pulseIn(_echo, HIGH);

    return duration;
}

/*! @brief Get distance data. */
float SONIC_IO::getDistance() {
    // Calculating the distance
    float Distance = getDuration() * 0.34 / 2;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
}