#ifndef APP_HEARTBEAT_H
#define APP_HEARTBEAT_H

/**
 * @file app_heartbeat.h
 * @author Otso Jousimaa <otso@ojousima.net>
 * @data 2020-06-12
 * @copyright Ruuvi Innovations Ltd, License BSD-3-Clause.
 *
 * Read and transmit latest sensor data via any means possible,
 * such as BLE advertisements, BLE Gatt, NFC.
 *
 */

#include "ruuvi_driver_error.h"
#include "ruuvi_driver_sensor.h"

/**
 * @brief Initializes timers for reading and sending heartbeat transmissions.
 *
 * The heartbeat interval should be at most as logging rate to make sure
 * that application will log fresh data.
 *
 * The heartbeat data is passed on to logging module which then decides
 * if sample should be logged.
 *
 * @retval RD_SUCCESS on success
 * @retval RD_ERROR_INVALID_STATE if timers or scheduler is not initialized.
 * @retval RD_ERROR_RESOURCES if a timer cannot be allocated.
 */
rd_status_t app_heartbeat_init (void);

/**
 * @brief (Re)starts app heartbeats.
 *
 * Calling this while heartbeats are ongoing has no effect.
 *
 * @retval RD_SUCCESS on success
 * @retval RD_ERROR_INVALID_STATE if heartbeat is not initialized.
 */
rd_status_t app_heartbeat_start (void);

/**
 * @brief Stops app heartbeats.
 *
 * This should be called to reduce the number of interrupts during heavier processing,
 * e.g. stop while replaying sensor logs to attached device.
 * Calling this has no effect if heartbeats are already stopped.
 *
 * @note Remember to restart the heartbeat, othewise app watchdog will trigger.
 *
 * @retval RD_SUCCESS on success.
 * @retval RD_ERROR_INVALID_STATE if heartbeat is not initialized.
 */
rd_status_t app_heartbeat_stop (void);

#ifdef CEEDLING
#include "ruuvi_interface_timer.h"
ri_timer_id_t * get_heart_timer (void);
void schedule_heartbeat_isr (void * const p_context);
void heartbeat (void * p_event, uint16_t event_size);
#endif

#endif // APP_HEARTBEAT_H
