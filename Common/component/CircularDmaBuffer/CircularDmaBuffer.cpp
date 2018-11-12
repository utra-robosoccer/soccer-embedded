/**
  *****************************************************************************
  * @file   CircularDmaBuffer.cpp
  * @author Robert
  *
  * @defgroup circular_dma_buffer
  * @ingroup circular_dma_buffer
  * @brief Manages a circular buffer communicating using UART in circular DMA mode.
  * @{
  *****************************************************************************
  */




/********************************* Includes **********************************/
#include "CircularDmaBuffer.h"




/******************************** File-local *********************************/
namespace{
// Constants
// ----------------------------------------------------------------------------




// Types & enums
// ----------------------------------------------------------------------------




// Classes and structs
// ----------------------------------------------------------------------------




// Variables
// ----------------------------------------------------------------------------




// Functions
// ----------------------------------------------------------------------------




} // end anonymous namespace




namespace uart{
// Constants
// ----------------------------------------------------------------------------




/************************** insert class name here ***************************/
// Public
// ----------------------------------------------------------------------------

CircularDmaBuffer::CircularDmaBuffer(
    UART_HandleTypeDef *uart_handle_in,
    const UartInterface* hw_if_in,
    uint16_t transmission_size_in,
    size_t buff_size_in,
    uint8_t *buff_p_in
) :
    m_uart_handle(uart_handle_in),
    m_hw_if(hw_if_in),
    m_transmission_size(transmission_size_in),
    m_buff_size(buff_size_in),
    m_buff_p(buff_p_in) {

}

/**
 * @brief Checks for failing conditions that make the buffer inoperable.
 * @return true if no failing conditions detected, false if one or more failing conditions are detected.
 *
 */
bool CircularDmaBuffer::selfCheck() const {
    bool ok = false;

    if (m_transmission_size > m_buff_size) {
        goto out;
    }

    ok = true;
  out:
    return ok;
}

/**
 * @brief Checks if m_buff_tail has been overrun m_buff_head. Overruns cause loss of data that has not been read.
 * @return true if at least 1 overrun has occurred, false if no overruns have occurred.
 */
bool CircularDmaBuffer::overrunCheck() const {
    // TODO: implement me once support for a buffer of variable length independent of the transmission size is added
    return false;
}

/**
 * @brief Updates m_buff_head to point to 1 past the last entry written to m_buffer_p by the DMA transfer.
 * @return The index that m_buff_head is at after updating.
 */
size_t CircularDmaBuffer::updateHead() {
    return (m_buff_head = m_buff_size - m_uart_handle->hdmarx->Instance->NDTR);
}

/**
 * @brief Sets m_buff_tail equal to m_buff_head, discarding any unread received bytes in m_buff_p.
 * @return the number of unread received bytes discarded.
 *
 */
size_t CircularDmaBuffer::catchupTail() {
    return (m_buff_tail = m_buff_head);
}

/**
 * @brief Checks if new received data is available to read in m_buff_p.
 * @return true if new data is available, no if not.
 */
bool CircularDmaBuffer::dataAvail() const {
    return m_buff_head != m_buff_tail;
}

/**
 * @brief Reads new data in m_buff_p into out_buff, without updating m_buff_tail.
 * @return number of bytes read from m_buff_p into out_buff.
 */
size_t CircularDmaBuffer::peekBuff(uint8_t *out_buff) const {
    const uint8_t BUFF_SIZE = m_buff_size;
    const uint8_t* BUFF_PTR = m_buff_p;
    const uint8_t HEAD_IDX = m_buff_head;
    uint8_t tailIdx = m_buff_tail;
    size_t numReceived = 0;

    if (tailIdx > HEAD_IDX) {
        while (tailIdx < BUFF_SIZE) {
            out_buff[numReceived++] = BUFF_PTR[tailIdx++];
        }
    }

    tailIdx %= BUFF_SIZE;

    while (tailIdx < HEAD_IDX) {
        out_buff[numReceived++] = BUFF_PTR[tailIdx++];
    }

    return numReceived;
}

/**
 * @brief Reads new data in m_buff_p into out_buff, updating the m_buff_tail.
 * @return number of bytes read from m_buff_p into out_buff.
 */
size_t CircularDmaBuffer::readBuff(uint8_t *out_buff) {
    const uint8_t BUFF_SIZE = m_buff_size;
    const uint8_t* BUFF_PTR = m_buff_p;
    const uint8_t HEAD_IDX = m_buff_head;
    uint8_t tailIdx = m_buff_tail;
    size_t numReceived = 0;

    if (tailIdx > HEAD_IDX) {
        while (tailIdx < BUFF_SIZE) {
            out_buff[numReceived++] = BUFF_PTR[tailIdx++];
        }
    }

    tailIdx %= BUFF_SIZE;

    while (tailIdx < HEAD_IDX) {
        out_buff[numReceived++] = BUFF_PTR[tailIdx++];
    }

    m_buff_tail = tailIdx;
    return numReceived;
}

void CircularDmaBuffer::initiate() {
    m_hw_if->receiveDMA(m_uart_handle, m_buff_p, m_buff_size);
}

void CircularDmaBuffer::restartIfError() {
    if(m_uart_handle->ErrorCode != HAL_UART_ERROR_NONE){
        m_hw_if->abortReceive(m_uart_handle);
        m_hw_if->receiveDMA(m_uart_handle, m_buff_p, m_buff_size);
    }
}
// Protected
// ----------------------------------------------------------------------------




// Private
// ----------------------------------------------------------------------------


} // end namespace uart

// TODO: run atop of UartInterface, add unit tests


/**
 * @}
 */
/* end - circular_dma_buffer */