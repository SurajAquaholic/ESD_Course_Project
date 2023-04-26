/*
 * test.h
 *
 *  Created on: Apr 25, 2023
 *      Author: suraj
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_


#include "stdint.h"

void TestLines (uint8_t color);

void TestRectangles (uint8_t color);

void TestFilledRectangles (uint8_t color);

void TestFilledCircles(uint8_t radius, uint16_t color);

void TestCircles(uint8_t radius, uint16_t color);

void TestTriangles(uint8_t color);

#endif /* INC_TEST_H_ */
