/**
  *****************************************************************************
  * @file
  * @author  Robert Fairley
  * @brief   Abstraction over UDP library providing common driver functions.
  *
  * @defgroup HeaderUdpDriver
  * @ingroup  lwip
  * @{
  *****************************************************************************
  */




#ifndef UDP_DRIVER_H
#define UDP_DRIVER_H




/********************************* Includes **********************************/
#include "UdpRawInterface.h"
#include "OsInterface.h"

using cmsis::OsInterface;
using lwip::UdpRawInterface;

namespace udp {

// Constants
// ----------------------------------------------------------------------------
constexpr TickType_t SEMAPHORE_WAIT_NUM_MS = 10;
constexpr TickType_t SEMAPHORE_WAIT_NUM_TICKS = pdMS_TO_TICKS(SEMAPHORE_WAIT_NUM_MS);

// Classes and structs
// ----------------------------------------------------------------------------
class UdpDriver {
public:
    UdpDriver();
    UdpDriver(const ip_addr_t m_ip_addr_src,
              const ip_addr_t m_ip_addr_dest,
              const u16_t m_port_src,
              const u16_t m_port_dest,
              const UdpRawInterface *m_udp_if,
              const OsInterface *m_os_if,
              const uint32_t m_recv_signal,
              const osThreadId m_recv_signal_task);
    ~UdpDriver();

    /* User-facing - typically call directly. */
    bool initialize();
    bool setupReceive(udp_recv_fn recv_callback);
    u16_t receive(uint8_t *rx_array_out, const size_t num_bytes);
    bool transmit(const uint8_t *tx_array_in, const size_t num_bytes);

    /* Utility - public but typically no need to call directly. */
    bool bytesToPacket(
            const uint8_t *byte_array_in,
            const size_t num_bytes,
            struct pbuf *p_pbuf
    ) const;
    u16_t packetToBytes(
            uint8_t *byte_array_out,
            const size_t num_bytes,
            struct pbuf *p_pbuf
    ) const;
    bool signalReceiveCplt();
    bool waitReceiveCplt();
    bool forgetPcb();
    bool forgetRecvPbuf();

    /* Accessors - public but typically no need to call directly. */
    void setIsInitialized(const bool is_initialized);
    bool setRecvPbuf(const struct pbuf *p_pbuf);

    bool getIsInitialized() const;
    const ip_addr_t getIpAddrSrc() const;
    const ip_addr_t getIpAddrDest() const;
    const u16_t getPortSrc() const;
    const u16_t getPortDest() const;
    const UdpRawInterface* getUdpIf() const;
    const OsInterface* getOsIf() const;
    struct udp_pcb* getPcb() const;
    struct pbuf* getRecvPbuf() const;

private:
    /* State indicator. */
    bool m_is_initialized = false;

    /* UdpDriver configuration. */
    ip_addr_t m_ip_addr_src = {0x0};
    ip_addr_t m_ip_addr_dest = {0x0};
    const u16_t m_port_src = 0;
    const u16_t m_port_dest = 0;

    /* External interfaces. */
    const UdpRawInterface *m_udp_if = nullptr;
    const OsInterface *m_os_if = nullptr;

    /* Data modified internally by the Raw API. */
    struct udp_pcb *m_pcb = nullptr;
    struct pbuf *m_recv_pbuf = nullptr;

    /* Synchronization. */
    const uint32_t m_recv_signal = 0; // Set when a packet is received
    const osThreadId m_recv_signal_task = reinterpret_cast<osThreadId>(0); // Task where receive() is called from
    mutable osMutexId m_recv_pbuf_mutex; // Control access to the recv pbuf
    mutable osStaticMutexDef_t m_recv_pbuf_mutex_control_block;
};

} // end namespace lwip

/**
 * @}
 */
/* end - HeaderUdpDriver */

#endif /* UDP_DRIVER_H */
