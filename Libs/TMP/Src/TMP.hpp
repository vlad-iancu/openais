#ifndef OPENAIS_LIBS_TMP_TMPID_H
#define OPENAIS_LIBS_TMP_TMPID_H

namespace openais
{
    namespace TMP
    {
        enum TMPID
        {
            STOP = 0,
            PAUSE = 1,
            RESUME = 2,
            REQUEST_NAME = 3,
            RESPONSE_NAME = 4,
            REQUEST_STATUS = 5,
            RESPONSE_STATUS = 6
        };

        enum TMPStatus
        {
            EXITED = 0x010,
            PAUSED = 0x100,
            RUNNING = 0x110,
        };
    }
}

#endif
