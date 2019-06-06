//
// Created by MingKing on 2019-06-01.
//

#ifndef SNOWFLAKE_RPC_SNOWFLAKE_H
#define SNOWFLAKE_RPC_SNOWFLAKE_H

#define TS_LENGTH 41
#define DS_LENGTH 5
#define MC_LENGTH 5
#define SQ_LENGTH 12
#define SNOWFLAKE_LENGTH 64

#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

class SnowFlake {
private:
    static SnowFlake *m_instance;
    long timestamp;
    long sequenceId;
    long dataCenterId;
    long machineId;


    void int2BinaryString(unsigned long num, char *s, int len);

    void initCharArray(char *string, int len);

    void clearCharArray(char *string, int len);

    long generateId();

private:
    SnowFlake();

    ~SnowFlake();

    SnowFlake(const SnowFlake &);

    SnowFlake &operator=(const SnowFlake &);

private:
    class Deletor {
    public:
        ~Deletor() {
            if (SnowFlake::m_instance != nullptr)
                delete SnowFlake::m_instance;
        }
    };

    static Deletor deletor;

public:
    static SnowFlake *getInstance() {
        if (m_instance == nullptr)
            m_instance = new SnowFlake();
        return m_instance;

    }

    long getCurrentTime();

    long Next();
};


#endif //SNOWFLAKE_RPC_SNOWFLAKE_H
