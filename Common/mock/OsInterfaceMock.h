/**
  *****************************************************************************
  * @file
  * @author  Izaak Niksan
  * @author  Tyler Gamvrelis
  *
  * @defgroup OsInterfaceMock
  * @ingroup Mocks
  * @{
  *****************************************************************************
  */




#ifndef OS_INTERFACE_MOCK_H
#define OS_INTERFACE_MOCK_H




/********************************* Includes **********************************/
#include "OsInterface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using cmsis::OsInterface;




/****************************** OsInterfaceMock ******************************/
namespace cmsis {
namespace gmock {
// Classes and structs
// ----------------------------------------------------------------------------
/**
 * @class OsInterfaceMock Implements OsInterface for unit testing
 *        purposes
 */
class OsInterfaceMock : public OsInterface {
public:
    MOCK_CONST_METHOD4(
        OS_xTaskNotifyWait,
        BaseType_t(
            uint32_t,
            uint32_t,
            uint32_t*,
            TickType_t
        )
    );

    MOCK_CONST_METHOD3(
        OS_xQueueReceive,
        BaseType_t(
            QueueHandle_t,
            void*,
            TickType_t
        )
    );

    MOCK_CONST_METHOD3(
        OS_xQueueSend,
        BaseType_t(
            QueueHandle_t,
            const void *,
            TickType_t
        )
    );

    MOCK_CONST_METHOD2(
        OS_xSemaphoreTake,
        BaseType_t(
            SemaphoreHandle_t,
            TickType_t
        )
    );

    MOCK_CONST_METHOD1(
        OS_xSemaphoreGive,
        BaseType_t(
            SemaphoreHandle_t
        )
    );

    MOCK_CONST_METHOD2(
        OS_vTaskDelayUntil,
        void(
            TickType_t* const,
            const TickType_t
        )
    );

    MOCK_CONST_METHOD1(
        OS_osDelay,
        osStatus(
            uint32_t millisec
        )
    );

    MOCK_CONST_METHOD1(
        OS_osMutexCreate,
        osMutexId(
            const osMutexDef_t *
        )
    );

    MOCK_CONST_METHOD2(
        OS_osSemaphoreCreate,
        osSemaphoreId(
            const osSemaphoreDef_t *,
            int32_t
        )
    );

    MOCK_CONST_METHOD2(
        OS_osMutexWait,
        osStatus(
            osMutexId,
            uint32_t
        )
    );

    MOCK_CONST_METHOD1(
        OS_osMutexRelease,
        osStatus(
            osMutexId
        )
    );

    MOCK_CONST_METHOD2(
        OS_osSemaphoreWait,
        int32_t(
            osSemaphoreId,
            uint32_t
        )
    );

    MOCK_CONST_METHOD1(
        OS_osSemaphoreRelease,
        osStatus(
            osSemaphoreId
        )
    );

    MOCK_CONST_METHOD2(
        OS_osSignalWait,
        osEvent(
            int32_t signals,
            uint32_t millisec
        )
    );

    MOCK_CONST_METHOD2(
        OS_osSignalSet,
        int32_t(
            osThreadId thread_id,
            int32_t signals
        )
    );
};

} // end namespace gmock
} // end namespace cmsis




/**
 * @}
 */
/* end - OsInterfaceMock */

#endif /* OS_INTERFACE_MOCK_H */
