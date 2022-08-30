/**
 * usbselfserial by lotuspar (https://github.com/lotuspar)
 *
 * Inspired / based on:
 *     the usb-serial-for-android project made in Java,
 *         * which is copyright 2011-2013 Google Inc., 2013 Mike Wakerly
 *         * https://github.com/mik3y/usb-serial-for-android
 *     the Linux serial port drivers,
 *         * https://github.com/torvalds/linux/tree/master/drivers/usb/serial
 *     and the FreeBSD serial port drivers
 *         * https://github.com/freebsd/freebsd-src/tree/main/sys/dev/usb/serial
 * Some parts rewritten in C++ for usbselfserial!
 *     * (by the time you read this it could have a different name!)
 * - 2022
 */
#include "common.hpp"
#include <libusb-1.0/libusb.h>

namespace usbselfserial {
namespace driver {

class BaseDriver {
protected:
    virtual void Configure() = 0;
    virtual void UpdateControlLines() = 0;
    u32_t baud_rate;
    DataBits data_bits;
    StopBits stop_bits;
    Parity parity;
    bool rts;
    bool dtr;

public:
    /**
     * Set new baud rate and reconfigure device
     * @param new_baud_rate New device baud rate
     */
    void SetBaudRate(int new_baud_rate) {
        baud_rate = new_baud_rate;
        Configure();
    }
    /**
     * Set new data bits value and reconfigure device
     * @param new_data_bits New device data bits value
     */
    void SetDataBits(DataBits new_data_bits) {
        data_bits = new_data_bits;
        Configure();
    }
    /**
     * Set new stop bits value and reconfigure device
     * @param new_stop_bits New device stop bits value
     */
    void SetStopBits(StopBits new_stop_bits) {
        stop_bits = new_stop_bits;
        Configure();
    }
    /**
     * Set new parity value and reconfigure device
     * @param new_stop_bits New device parity value
     */
    void SetParity(Parity new_parity) {
        parity = new_parity;
        Configure();
    }
    /**
     * Set new DTR (Data Terminal Ready)
     * @param value New DTR value
     */
    void SetDTR(bool value) {
        dtr = value;
        UpdateControlLines();
    }
    /**
     * Set new RTS (Request To Send)
     * @param value New RTS value
     */
    void SetRTS(bool value) {
        rts = value;
        UpdateControlLines();
    }
};

} // namespace driver
} // namespace usbselfserial