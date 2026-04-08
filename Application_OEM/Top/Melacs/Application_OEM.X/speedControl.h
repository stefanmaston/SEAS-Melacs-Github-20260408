/*
 * File:   speedControl.h
 * Author: Bala
 *
 * Created on November 9, 2015, 1:59 PM
 */

#ifndef SPEEDCONTROL_H
#define	SPEEDCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

void set_jp7(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay);
void set_jp8(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay);
void set_jp9(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay);
void set_jp10(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay);

#ifdef	__cplusplus
}
#endif

#endif	/* SPEEDCONTROL_H */

