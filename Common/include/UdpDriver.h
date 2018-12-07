/**
  *****************************************************************************
  * @file    UdpDriver.h
  * @author  Robert Fairley
  * @brief   Management of simple UDP rx/tx operations.
  *
  * @defgroup Header
  * @ingroup  udp_driver
  * @{
  *****************************************************************************
  */

#ifndef UDP_DRIVER_H
#define UDP_DRIVER_H

#include "UdpInterface.h"
#include "OsInterface.h"

namespace udp_driver {

constexpr TickType_t SEMAPHORE_WAIT_NUM_MS = 10;
constexpr TickType_t SEMAPHORE_WAIT_NUM_TICKS = pdMS_TO_TICKS(SEMAPHORE_WAIT_NUM_MS);

class UdpDriver {
public:
    UdpDriver();
    UdpDriver(const ip_addr_t ipaddrIn,
              const ip_addr_t ipaddrPcIn,
              const u16_t portIn,
              const u16_t portPcIn,
              const udp_interface::UdpInterface *udpInterfaceIn,
              const os::OsInterface *osInterfaceIn);
    ~UdpDriver();

    bool initialize();
    bool setupReceive(udp_recv_fn recvCallback);
    void unSetupReceive();
    bool receive(uint8_t *rxArrayOut, const size_t numBytes);
    bool transmit(const uint8_t *txArrayIn, const size_t numBytes);
    bool bytesToPacket(const uint8_t *byteArrayIn, const size_t numBytes, struct pbuf *pPbuf) const;
    u16_t packetToBytes(uint8_t *byteArrayOut, const size_t numBytes, struct pbuf *pPbuf) const;
    void signalReceiveCplt();
    void waitReceiveCplt();

    struct pbuf*    getRecvPbuf() const;
    void            setRecvPbuf(struct pbuf *pPbuf);
    void            forgetRecvPbuf();

    const ip_addr_t                     getIpaddr() const;
    const ip_addr_t                     getIpaddrPc() const;
    const u16_t                         getPort() const;
    const u16_t                         getPortPc() const;
    const udp_interface::UdpInterface*  getUdpInterface() const;
    const os::OsInterface*              getOsInterface() const;
    struct udp_pcb*                     getPcb() const;

private:
    /* UdpDriver configuration. */
    const ip_addr_t ipaddr      = {0x0};
    const ip_addr_t ipaddrPc    = {0x0};
    const u16_t port            = 0;
    const u16_t portPc          = 0;

    /* External interfaces. */
    const udp_interface::UdpInterface *udpInterface     = nullptr;
    const os::OsInterface *osInterface                  = nullptr;

    /* Data modified internally by the Raw API. */
    /* TODO: decide whether NULL or nullptr, since lwIP API will use NULL when setting these. */
    struct udp_pcb *pcb     = nullptr;
    struct pbuf *recvPbuf   = nullptr;

    /* Synchronization. */
    mutable osSemaphoreId recvSemaphore; /* TODO: replace with binary semaphore-style task notification. */
    mutable osStaticSemaphoreDef_t recvSemaphoreControlBlock;
    mutable osMutexId recvPbufMutex;
    mutable osStaticMutexDef_t recvPbufMutexControlBlock;
};

} // end namespace udp_driver

/**
 * @}
 */
/* end - Header */

#endif /* UDP_DRIVER_H */
