//
// Created by MingKing on 2019-06-01.
//

#include "SnowFlake.h"

using namespace std;

SnowFlake::SnowFlake() {
    this->timestamp = this->getCurrentTime();
    this->sequenceId = 0;
    this->dataCenterId = 12;
    this->machineId = 12;
}

SnowFlake::~SnowFlake() {

}


long SnowFlake::getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void SnowFlake::int2BinaryString(unsigned long num, char *s, int len) {
    len++;
    if (len < 2) {
    } else if (0 == num) {
    } else {
        *(s + --len) = '\0';
        while (num != 0) {
            int bit = num & 1;
            num = num >> 1;
            *(s + --len) = (char) ('0' + bit);
        }
//        for (; len > 0; len--) {
//            *(s + len) = (char) ('0' + (num % 2));
//            num /= 2;
//        }
    }
}

void SnowFlake::initCharArray(char *string, int len) {
    int i = 0;
    for (; i < len; ++i) {
        string[i] = '0';
    }
    string[len] = '\0';
}

void SnowFlake::clearCharArray(char *string, int len) {
    int i = 0;
    for (; i < len; ++i) {
        string[i] = '\0';
    }
    string[len] = '\0';
}

long SnowFlake::Next() {
    long newTimestamp = this->getCurrentTime();
    if (newTimestamp > timestamp) {
        sequenceId = 0;
        timestamp = newTimestamp;
    }
    this->sequenceId++;
    return generateId();

}

long SnowFlake::generateId() {
    char strSnowFlake[SNOWFLAKE_LENGTH + 1];
    clearCharArray(strSnowFlake, SNOWFLAKE_LENGTH);
    strSnowFlake[0] = '0';

    char strTimestamp[TS_LENGTH + 1];
    initCharArray(strTimestamp, TS_LENGTH);
    int2BinaryString((unsigned long) timestamp, strTimestamp, TS_LENGTH);
    strcat(strSnowFlake, strTimestamp);

    char strDataCenterId[DS_LENGTH + 1];
    initCharArray(strDataCenterId, DS_LENGTH);
    int2BinaryString((unsigned long) dataCenterId, strDataCenterId, DS_LENGTH);
    strcat(strSnowFlake, strDataCenterId);

    char strMachineId[MC_LENGTH + 1];
    initCharArray(strMachineId, MC_LENGTH);
    int2BinaryString((unsigned long) machineId, strMachineId, MC_LENGTH);
    strcat(strSnowFlake, strMachineId);

    char strSequenceId[SQ_LENGTH + 1];
    initCharArray(strSequenceId, SQ_LENGTH);
    int2BinaryString((unsigned long) sequenceId, strSequenceId, SQ_LENGTH);
    strcat(strSnowFlake, strSequenceId);

    long snowflakeNumber = strtol(strSnowFlake, nullptr, 2);
    return snowflakeNumber;
}

SnowFlake *SnowFlake::m_instance = nullptr;
